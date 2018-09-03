//
// Created by D064693 on 03.09.2018.
//

#ifndef CONVERTHEXTOBASE64_ENCODINGS_H
#define CONVERTHEXTOBASE64_ENCODINGS_H

#endif //CONVERTHEXTOBASE64_ENCODINGS_H

#include <vector>
#include <iostream>
namespace Crypto {

    class Encodings {

    private:
        static std::string numberToBase64(char number);
        static void hexStringToByteArray(std::string *hexString, std::vector<char> *byteArray);

        struct BrokenByteException : public std::exception {
            const char *what() const noexcept override {
                return "String contains half a Byte";
            }
        };

    public:
        static std::string hexToBase64(std::string input);
    };
}