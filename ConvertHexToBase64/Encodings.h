#ifndef CONVERTHEXTOBASE64_ENCODINGS_H
#define CONVERTHEXTOBASE64_ENCODINGS_H

#include <vector>
#include <iostream>
namespace Crypto {

    class Encodings {

    private:
        static std::string numberToBase64(char number);

        struct BrokenByteException : public std::exception {
            const char *what() const noexcept override {
                return "String contains half a Byte";
            }
        };

    public:
        static std::string hexToBase64(std::string input);
        static std::vector<char> HexStringToByteArray(std::string hexString);
        static std::string ByteArrayToHexString( std::vector<char> byteArray);
    };
}

#endif //CONVERTHEXTOBASE64_ENCODINGS_H