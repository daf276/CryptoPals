#ifndef FIXEDXOR_FIXEDXOR_H
#define FIXEDXOR_FIXEDXOR_H

#include <string>
#include <vector>

namespace Algorithms {
        std::vector<char> RepeatingKeyXor(std::vector<char> bytearray1, std::vector<char> bytearray2);
        std::string RepeatingSingleByteXorDecryption(std::vector<char> input);
        double EvaluateLetterFrequencyError(std::vector<char> input);
}

#endif //FIXEDXOR_FIXEDXOR_H
