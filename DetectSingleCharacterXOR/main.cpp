#include <iostream>
#include <fstream>
#include <sstream>
#include <cfloat>
#include <vector>
#include "../HelperFunctions/Encodings.h"
#include "../HelperFunctions/Algorithms.h"

int main() {
    std::ifstream infile("../test.txt");
    std::string line;

    double result_error = DBL_MAX;
    std::vector<char> result;

    while(std::getline(infile, line)){
        line = Algorithms::RepeatingSingleByteXorDecryption(Encodings::HexStringToByteArray(line));
        std::vector<char> data(line.begin(), line.end());

        double current_error = Algorithms::EvaluateLetterFrequencyError(data);

        if (current_error < result_error) {
            result_error = current_error;
            result = data;
        }
    }
    infile.close();

    std::cout << std::string(result.begin(), result.end()) << std::endl;
    return 0;
}