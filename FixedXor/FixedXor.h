#ifndef FIXEDXOR_FIXEDXOR_H
#define FIXEDXOR_FIXEDXOR_H

#include <string>

namespace Crypto {
    class FixedXor {
    private:
        struct StringsNotEqualLengthException: public std::exception {
            const char *what() const noexcept override {
                return "Strings are not of equal length, cant do XOR";
            }
        };
    public:
        static std::string Xor2Buffers(std::string xor_string_1, std::string xor_string_2);
    };
}

#endif //FIXEDXOR_FIXEDXOR_H
