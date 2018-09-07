#include <iostream>
#include <vector>
#include <list>
#include "Encodings.h"

namespace Encodings {
    std::string EncodeBase64(std::vector<char> input) {
        std::string base64Output;

        for (int i = 0; i < input.size() - input.size() % 3; i += 3) {
            int current3Bytes = input[i] * 65536 + input[i + 1] * 256 + input[i + 2];

            base64Output += NumberToBase64(static_cast<char>(current3Bytes >> 18 & 63));
            base64Output += NumberToBase64(static_cast<char>(current3Bytes >> 12 & 63));
            base64Output += NumberToBase64(static_cast<char>(current3Bytes >> 6 & 63));
            base64Output += NumberToBase64(static_cast<char>(current3Bytes & 63));
        }

        if (input.size() % 3 == 1) {
            int current3Bytes = input.back() * 65536;
            base64Output += NumberToBase64(static_cast<char>(current3Bytes >> 18 & 63));
            base64Output += NumberToBase64(static_cast<char>(current3Bytes >> 12 & 63));
            base64Output += "==";
        }

        if (input.size() % 3 == 2) {
            int current3Bytes = input[input.size() - 2] * 65536 + input.back() * 256;
            base64Output += NumberToBase64(static_cast<char>(current3Bytes >> 18 & 63));
            base64Output += NumberToBase64(static_cast<char>(current3Bytes >> 12 & 63));
            base64Output += NumberToBase64(static_cast<char>(current3Bytes >> 6 & 63));
            base64Output += "=";
        }

        return base64Output;
    }

    std::vector<char> DecodeBase64(std::string input) {
        int padding = 0;
        if (input[input.length()-1] == '=') padding++;
        if (input[input.length()-2] == '=') padding++;

        for (char &i : input) i = Base64ToNumber(i);

        std::list<char> bytes;
        for (int i = 0; i < input.size(); i += 4) {
            bytes.push_back((input[i] << 2) + (input[i + 1] >> 4));
            bytes.push_back(static_cast<char>(((input[i + 1] & 0b001111) << 4)) + (input[i + 2] >> 2));
            bytes.push_back(static_cast<char>(((input[i + 2] & 0b000011) << 6)) + input[i + 3]);
        }

        if (padding > 0) bytes.pop_back();
        if (padding > 1) bytes.pop_back();

        return std::vector<char>{std::make_move_iterator(std::begin(bytes)), std::make_move_iterator(std::end(bytes))};
    }

    std::string NumberToBase64(char number) {
        std::string s;
        if (number < 26) s.push_back(static_cast<char>(number + 65));
        if (number >= 26 && number < 52) s.push_back(static_cast<char>(number + 71));
        if (number >= 52 && number < 62) s.push_back(static_cast<char>(number - 4));
        if (number == 62) s.push_back(static_cast<char>(number - 19));
        if (number == 63) s.push_back(static_cast<char>(number - 16));
        return s;
    }

    char Base64ToNumber(char input) {
        if (input <= 90 && input >= 65) return static_cast<char>(input - 65);
        if (input >= 97 && input <= 122) return static_cast<char>(input - 71);
        if (input >= 40 && input <= 57) return static_cast<char>(input + 4);
        if (input == 43) return static_cast<char>(input + 19);
        if (input == 47) return static_cast<char>(input + 16);

        return 0;
    }

    std::vector<char> HexStringToByteArray(std::string hexString) {
        if (hexString.length() % 2 != 0) throw BrokenByteException();

        std::vector<char> inputAsBytes(hexString.length() / 2);

        for (int i = 0; i < inputAsBytes.size(); i++) {
            std::string currentByte = hexString.substr(i * 2, 2);
            inputAsBytes[i] = static_cast<char>(strtol(currentByte.c_str(), nullptr, 16));
        }

        return inputAsBytes;
    }
}