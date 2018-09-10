#include <map>
#include "Algorithms.h"
#include <cmath>
#include <iostream>

namespace Algorithms {
    std::map<char, double> letter_frequency = {
            {'a', 0.0651738},
            {'b', 0.0124248},
            {'c', 0.0217339},
            {'d', 0.0349835},
            {'e', 0.1041442},
            {'f', 0.0197881},
            {'g', 0.0158610},
            {'h', 0.0492888},
            {'i', 0.0558094},
            {'j', 0.0009033},
            {'k', 0.0050529},
            {'l', 0.0331490},
            {'m', 0.0202124},
            {'n', 0.0564513},
            {'o', 0.0596302},
            {'p', 0.0137645},
            {'q', 0.0008606},
            {'r', 0.0497563},
            {'s', 0.0515760},
            {'t', 0.0729357},
            {'u', 0.0225134},
            {'v', 0.0082903},
            {'w', 0.0171272},
            {'x', 0.0013692},
            {'y', 0.0145984},
            {'z', 0.0007836},
            {' ', 0.1918182}
    };

    std::vector<char> RepeatingKeyXor(std::vector<char> input, std::vector<char> key) {
        std::vector<char> result(input.size());

        for (int i = 0; i < result.size(); ++i) result[i] = input[i] ^ key[i % key.size()];

        return result;
    }

    std::string RepeatingSingleByteXorDecryption(std::vector<char> input) {
        double result_error = input.size();
        std::vector<char> result;

        for (char i = 32; i < 127; ++i) {
            std::vector<char> encryption_key = {i};
            std::vector<char> current_decrypted_text = Algorithms::RepeatingKeyXor(input, encryption_key);

            double current_error = EvaluateLetterFrequencyError(current_decrypted_text);

            if (current_error < result_error) {
                result_error = current_error;
                result = current_decrypted_text;
            }
        }

        return std::string(result.begin(), result.end());
    }

    char GetEncryptionKeyOfRepeatingSingleByteXorDecryption(std::vector<char> input) {
        double result_error = input.size();
        std::vector<char> result;
        char key;
        for (char i = 32; i < 127; ++i) {
            std::vector<char> encryption_key = {i};
            std::vector<char> current_decrypted_text = Algorithms::RepeatingKeyXor(input, encryption_key);

            double current_error = EvaluateLetterFrequencyError(current_decrypted_text);

            if (current_error < result_error) {
                result_error = current_error;
                result = current_decrypted_text;
                key = i;
            }
        }

        return key;
    }

    double EvaluateLetterFrequencyError(std::vector<char> input) {
        std::map<char, int> letter_count = {};
        for (char &j : input) {
            if (letter_count.count(j) > 0)
                letter_count[j]++;
            else
                letter_count.insert(std::pair<char, int>(j, 1));
        }

        double error = 0;

        for (auto const&[key, val] : letter_count) {
            error += std::pow(static_cast<double>(val) / static_cast<double>(input.size()) - letter_frequency[key], 2);
        }

        return error;
    }

    int GetHammingDistance(std::string input, std::string input2){
        std::vector<unsigned long long> bytes1(input.begin(), input.end());
        std::vector<unsigned long long> bytes2(input2.begin(), input2.end());

        int result = 0;

        for (int i = 0; i < bytes1.size(); ++i) {
            result += __builtin_popcountll(bytes1[i] ^ bytes2[i]);
        }

        return result;
    }
}
