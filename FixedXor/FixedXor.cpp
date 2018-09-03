#include "FixedXor.h"
#include "../ConvertHexToBase64/Encodings.h"

namespace Crypto {
    std::string FixedXor::Xor2Buffers(std::string xor_string_1, std::string xor_string_2) {
        
        std::vector<char> xor_bytearray_1;
        std::vector<char> xor_bytearray_2;

        Encodings::hexStringToByteArray(&xor_string_1, &xor_bytearray_1);
        Encodings::hexStringToByteArray(&xor_string_2, &xor_bytearray_2);
    }
}
