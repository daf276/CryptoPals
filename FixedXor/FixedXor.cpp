#include "FixedXor.h"
#include "../ConvertHexToBase64/Encodings.h"

namespace Crypto {
    std::vector<char> FixedXor::Xor2Buffers(std::vector<char> bytearray1, std::vector<char> bytearray2) {
        std::vector<char> result(bytearray1.size());

        for (int i = 0; i < result.size(); ++i) {
            result[i] = bytearray1[i] ^ bytearray2[i];
        }

        return result;
    }
}
