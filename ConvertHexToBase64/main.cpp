#include <iostream>
#include <chrono>
#include <ctime>
#include <vector>

using namespace std;

string numberToBase64(char number);

void hexToBase64();

void hexStringToByteArray(string *hexString, vector<char> *byteArray);

struct BrokenByteException : public exception {
    const char *what() const noexcept override {
        return "String contains half a Byte";
    }
};

int main(int argc, char const *argv[]) {
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();

    hexToBase64();

    end = std::chrono::system_clock::now();
    long elapsed_millis = static_cast<long>(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());
    std::cout << "Elapsed Milliseconds: " << elapsed_millis << std::endl;

    return 0;
}

void hexToBase64() {
    string input = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6da2";

    vector<char> inputAsBytes;

    hexStringToByteArray(&input, &inputAsBytes);

    string base64Output;

    for (int i = 0; i < inputAsBytes.size() - inputAsBytes.size() % 3; i += 3) {
        int current3Bytes = inputAsBytes[i] * 65536 + inputAsBytes[i + 1] * 256 + inputAsBytes[i + 2];

        base64Output+= numberToBase64(current3Bytes >> 18 & 63);
        base64Output+= numberToBase64(current3Bytes >> 12 & 63);
        base64Output+= numberToBase64(current3Bytes >> 6 & 63);
        base64Output+= numberToBase64(current3Bytes & 63);
    }

    if(inputAsBytes.size() % 3 == 1){
        int current3Bytes = inputAsBytes.back() * 65536;
        base64Output+= numberToBase64(current3Bytes >> 18 & 63);
        base64Output+= numberToBase64(current3Bytes >> 12 & 63);
        base64Output+="==";
    }

    if(inputAsBytes.size() % 3 == 2){
        int current3Bytes = inputAsBytes[inputAsBytes.size()-2] * 65536 + inputAsBytes.back() * 256;
        base64Output+= numberToBase64(current3Bytes >> 18 & 63);
        base64Output+= numberToBase64(current3Bytes >> 12 & 63);
        base64Output+= numberToBase64(current3Bytes >> 6 & 63);
        base64Output+="=";
    }

    cout << base64Output << endl;
}

string numberToBase64(char number) {
    string s;
    if (number < 26) s.push_back(number + 65);
    if (number >= 26 && number < 52) s.push_back(number + 71);
    if (number >= 52 && number < 62) s.push_back(number - 4);
    if (number == 62) s.push_back(number - 19);
    if (number == 63) s.push_back(number - 16);
    return s;
}

void hexStringToByteArray(string *hexString, vector<char> *byteArray) {
    if (hexString->length() % 2 != 0) throw BrokenByteException();

    vector<char> inputAsBytes(hexString->length() / 2);

    for (int i = 0; i < inputAsBytes.size(); i++) {
        string currentByte = hexString->substr(i * 2, 2);
        inputAsBytes[i] = (char) strtol(currentByte.c_str(), NULL, 16);
    }

    *byteArray = inputAsBytes;
}