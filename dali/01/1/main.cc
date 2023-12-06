#include <iostream>
#include <fstream>

using namespace std;

int FindFirstDigit(const string& line) {
    for (auto iter : line) {
        if (isdigit(iter)) {
            return iter - '0';
        }
    }

    throw runtime_error("Could not find first digit");
}

int FindLastDigit(const string& line) {
    for (auto iter = line.rbegin(); iter != line.rend(); iter++) {
        if (isdigit(*iter)) {
            return *iter - '0';
        }
    }

    throw runtime_error("Could not find last digit");
}

int main(int argc, char* argv[]) {
    fstream input("input.txt");
    string line;
    int total = 0;
    while (getline(input, line)) {
        const int value = FindFirstDigit(line) * 10 + FindLastDigit(line);
        total += value;
    }

    cout << "The total is " << total << endl;

    return 0;
}
