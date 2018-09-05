#include <iostream>
#include "../HelperFunctions/Algorithms.h"

int main() {
    std::string text = "Burning 'em, if you ain't quick and nimble\n"
                       "I go crazy when I hear a cymbal";
    std::string key = "ICE";

    std::vector<char> result = Algorithms::RepeatingKeyXor(std::vector<char>(text.begin(),text.end()),std::vector<char>(key.begin(),key.end()));

    for(char j : result){
        std::cout << std::hex << static_cast<int>(j);
    }
    return 0;
}