#include <iostream>
#include "../HelperFunctions/Encodings.h"
#include "../HelperFunctions/Algorithms.h"

int main() {
    std::cout << Algorithms::GetHammingDistance("this is a test", "wokka wokka!!!") << std::endl;
    return 0;
}