#ifndef CONVERTHEXTOBASE64_ENCODINGS_H
#define CONVERTHEXTOBASE64_ENCODINGS_H

#include <vector>
#include <iostream>

namespace Encodings {
    struct BrokenByteException : public std::exception {
        const char *what() const noexcept override {
            return "String contains half a Byte";
        }
    };

    std::string NumberToBase64(char number);

    char Base64ToNumber(char input);

    std::string EncodeBase64(std::vector<char> input);

    std::vector<char> DecodeBase64(std::string input);

    std::vector<char> HexStringToByteArray(std::string hexString);
}

#endif //CONVERTHEXTOBASE64_ENCODINGS_H