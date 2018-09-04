#include <iostream>
#include "Algorithms.h"
#include "Encodings.h"
#include <fstream>
#include <sstream>

int main() {
    std::ifstream infile("thefile.txt");
    std::string line;
    while (std::getline(infile, line))
    {
        std::istringstream iss(line);
        int a, b;
        if (!(iss >> a >> b)) { break; } // error

        // process pair (a,b)
    }

    std::cout << Algorithms::RepeatingKeyXorDecryption(Encodings::HexStringToByteArray("1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736"));
    return 0;
}