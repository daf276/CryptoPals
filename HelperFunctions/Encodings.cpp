#include <iostream>
#include <vector>
#include "Encodings.h"

namespace Encodings {
    std::string HexToBase64(std::string input) {
        input = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6da2";

        std::vector<char> inputAsBytes = HexStringToByteArray(input);

        std::string base64Output;

        for (int i = 0; i < inputAsBytes.size() - inputAsBytes.size() % 3; i += 3) {
            int current3Bytes = inputAsBytes[i] * 65536 + inputAsBytes[i + 1] * 256 + inputAsBytes[i + 2];

            base64Output += NumberToBase64(static_cast<char>(current3Bytes >> 18 & 63));
            base64Output += NumberToBase64(static_cast<char>(current3Bytes >> 12 & 63));
            base64Output += NumberToBase64(static_cast<char>(current3Bytes >> 6 & 63));
            base64Output += NumberToBase64(static_cast<char>(current3Bytes & 63));
        }

        if (inputAsBytes.size() % 3 == 1) {
            int current3Bytes = inputAsBytes.back() * 65536;
            base64Output += NumberToBase64(static_cast<char>(current3Bytes >> 18 & 63));
            base64Output += NumberToBase64(static_cast<char>(current3Bytes >> 12 & 63));
            base64Output += "==";
        }

        if (inputAsBytes.size() % 3 == 2) {
            int current3Bytes = inputAsBytes[inputAsBytes.size() - 2] * 65536 + inputAsBytes.back() * 256;
            base64Output += NumberToBase64(static_cast<char>(current3Bytes >> 18 & 63));
            base64Output += NumberToBase64(static_cast<char>(current3Bytes >> 12 & 63));
            base64Output += NumberToBase64(static_cast<char>(current3Bytes >> 6 & 63));
            base64Output += "=";
        }

        return base64Output;
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