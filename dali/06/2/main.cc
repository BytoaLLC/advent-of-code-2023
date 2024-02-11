    #include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <cstring>
#include <cmath>

using namespace std;

std::vector<std::string> SplitString(const std::string& str, const std::string& delimiter) {
    std::vector<std::string> tokens;
    char* ptr = strtok(const_cast<char*>(str.data()), delimiter.c_str());

    while (ptr != nullptr) {
        tokens.push_back(ptr);
        ptr = strtok(nullptr, delimiter.c_str());
    }

    return tokens;
}

vector<unsigned long long> ParseLine(const string& line) {
    vector<string> tokens = SplitString(line, " ");
    vector<unsigned long long> int_tokens;
    for (size_t i = 1; i < tokens.size(); ++i) {
        int_tokens.push_back(atoll(tokens.at(i).c_str()));
    }
    return int_tokens;
}

int main(int argc, char* argv[]) {
    fstream input("input.txt");
    string line;
    getline(input, line);
    vector<unsigned long long> times = ParseLine(line);
    getline(input, line);
    vector<unsigned long long> distance = ParseLine(line);

    // y = f(x)
    // y = time * velocity
    // y = (max_time - button_hold) * velocity
    // y = (max_time - button_hold) * (button_hold)
    //
    // If button_hold = x and max_distance = y
    //
    // button_hold = (0.5) * (max_time - √(max_time^2 - 4 * distance_travelled))
    // button_hold = (0.5) * (√(max_time^2 - 4 * distance_travelled) + max_time

    unsigned long long total = 0;
    for (size_t i = 0; i < times.size(); ++i) {
        unsigned long long max_time = times.at(i);
        unsigned long long distance_travelled = distance.at(i);
        unsigned long long first = 0.5 * (max_time - sqrtf64(powf64(max_time, 2.0) - 4.0 * distance_travelled));
        unsigned long long second = 0.5 * (sqrtf64(powf64(max_time, 2.0) - 4.0 * distance_travelled) + max_time);
        unsigned long long higher = floor(max(first,second));
        unsigned long long lower = floor(min(first, second));

        while (((times.at(i) - lower) * lower) <= distance.at(i)) {
            lower += 1.0;
        }
        while (((times.at(i) - higher) * higher) <= distance.at(i)) {
            higher -= 1.0;
        }
        total += (higher - lower + 1);
    }

    cout << "total: " << total << endl;

    return 0;
}
