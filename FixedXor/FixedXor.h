#ifndef FIXEDXOR_FIXEDXOR_H
#define FIXEDXOR_FIXEDXOR_H

#include <string>
#include <vector>

namespace Crypto {
    class FixedXor {
    private:
        struct StringsNotEqualLengthException: public std::exception {
            const char *what() const noexcept override {
                return "Strings are not of equal length, cant do XOR";
            }
        };
    public:
        static std::vector<char> Xor2Buffers(std::vector<char> bytearray1, std::vector<char> bytearray2);
    };
}

#endif //FIXEDXOR_FIXEDXOR_H
