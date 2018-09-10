#include <iostream>
#include <fstream>
#include "Encodings.h"
#include "Algorithms.h"
#include <list>
#include <cmath>
#include <map>
#include <algorithm>

int main() {
    std::string all_lines;
    std::vector<char> decoded_base64;
    std::ifstream infile("../../BreakRepeatingKeyXor/6.txt");
    std::string line;

    while (std::getline(infile, line)) {
        all_lines += line;
    }
    infile.close();

    decoded_base64 = Encodings::DecodeBase64(all_lines);

    std::string decoded_base64_string = std::string(decoded_base64.begin(), decoded_base64.end());
    std::list<double> hamming_distances;

    for (int i = 2; i < 41; i++) {
        double current_hamming_distance = 0;

        for (int j = 0; j < i*20; j+=i) {
            current_hamming_distance += Algorithms::GetHammingDistance(decoded_base64_string.substr(j, i), decoded_base64_string.substr(j+i, i));
        }

        current_hamming_distance /= (i*20);

        hamming_distances.push_back(current_hamming_distance);
    }

    std::vector tests = std::vector(hamming_distances.begin(), hamming_distances.end());

    for (int l = 0; l < 40; ++l) {
        int key_size = 0;
        auto mini = *std::min_element(tests.begin(), tests.end());

        for (int j = 0; j < tests.size(); ++j) {
            if(tests[j] == mini){
                key_size = j+2;
                tests[j] = 999999;
            }
        }

        std::vector<std::list<char>> test(key_size);

        for (int i = 0; i < decoded_base64.size(); i++) {
            test[i % key_size].push_back(decoded_base64[i]);
        }

        std::vector<char> key(key_size);

        for (int k = 0; k < test.size(); ++k) {
            key[k] = Algorithms::GetEncryptionKeyOfRepeatingSingleByteXorDecryption(
                    std::vector<char>(test[k].begin(), test[k].end()));
        }

        std::cout << std::string(key.begin(), key.end()) << std::endl;

        std::vector<char> rsult = Algorithms::RepeatingKeyXor(decoded_base64, key);
    }

    //std::cout << std::string(rsult.begin(), rsult.end());
    return 0;
}