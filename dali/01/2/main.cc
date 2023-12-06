#include <iostream>
#include <fstream>

using namespace std;

int ParseDigit(const string& line, const size_t pos) {
    if (isdigit(line.at(pos))) {
        return line.at(pos) - '0';
    }

    if ((pos + 3) <= line.size()) {
        const string substr = line.substr(pos, 3);
        if (substr == "one") {
            return 1;
        }
        if (substr == "two") {
            return 2;
        }
        if (substr == "six") {
            return 6;
        }
    }

    if ((pos + 4) <= line.size()) {
        const string substr = line.substr(pos, 4);
        if (substr == "four") {
            return 4;
        }
        if (substr == "five") {
            return 5;
        }
        if (substr == "nine") {
            return 9;
        }
    }

    if (pos + 5 <= line.size()) {
        const string substr = line.substr(pos, 5);
        if (substr == "three") {
            return 3;
        }
        if (substr == "seven") {
            return 7;
        }
        if (substr == "eight") {
            return 8;
        }
    }

    return -1;
}

int FindFirstDigit(const string& line) {
    for (int i = 0; i < line.size(); ++i) {
        const int digit = ParseDigit(line, i);
        if (digit >= 0) {
            return digit;
        }
    }

    throw runtime_error("Could not find first digit");
}

int FindLastDigit(const string& line) {
    for (int i = line.size() - 1; i >= 0; i--) {
        const int digit = ParseDigit(line, i);
        if (digit >= 0) {
            return digit;
        }
    }

    throw runtime_error("Could not find last digit");
}

int main(int argc, char* argv[]) {
    fstream input("input.txt");
    string line;
    int total = 0;
    while (getline(input, line)) {
        total += FindFirstDigit(line) * 10 + FindLastDigit(line);
    }
    cout << "The total is " << total << endl;
    return 0;
}
