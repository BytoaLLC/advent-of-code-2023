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

vector<int> ParseLine(const string& line) {
    vector<string> tokens = SplitString(line, " ");
    vector<int> int_tokens;
    for (size_t i = 1; i < tokens.size(); ++i) {
        int_tokens.push_back(atoi(tokens.at(i).c_str()));
    }
    return int_tokens;
}

int main(int argc, char* argv[]) {
    fstream input("input.txt");
    string line;
    getline(input, line);
    vector<int> times = ParseLine(line);
    getline(input, line);
    vector<int> distance = ParseLine(line);

    // for (size_t i = 0; i < times.size(); ++i) {
    //     cout << times.at(i) << " " << distance.at(i) << endl;
    // }

    // y = f(x)
    // y = time * velocity
    // y = (max_time - button_hold) * velocity
    // y = (max_time - button_hold) * (button_hold)
    //
    // If button_hold = x and max_distance = y
    //
    // button_hold = (0.5) * (max_time - √(max_time^2 - 4 * distance_travelled))
    // button_hold = (0.5) * (√(max_time^2 - 4 * distance_travelled) + max_time

    long long total = 1;
    for (size_t i = 0; i < times.size(); ++i) {
        double max_time = times.at(i);
        double distance_travelled = distance.at(i);
        double first = 0.5 * (max_time - sqrt(powf64(max_time, 2.0) - 4.0 * distance_travelled));
        double second = 0.5 * (sqrt(powf64(max_time, 2.0) - 4.0 * distance_travelled) + max_time);
        // cout << first << " " << second << endl;

        double higher = floor(max(first,second));
        double lower = floor(min(first, second));

        while (((times.at(i) - lower) * lower) <= distance.at(i)) {
        // cout << "distance of " << lower << " is " << (times.at(i) - lower) * lower << endl;
            lower += 1.0;
        }

        while (((times.at(i) - higher) * higher) <= distance.at(i)) {
        //  cout << "distance of " << higher << " is " << (times.at(i) - higher) * higher << endl;
            higher -= 1.0;
        }

        //  cout << "distance of " << higher << " is " << (times.at(i) - higher) * higher << endl;
        // cout << "distance of " << lower << " is " << (times.at(i) - lower) * lower << endl;
        cout << higher - lower + 1 << endl;
        total *= (higher - lower + 1);
    }

    cout << "total: " << total << endl;

    return 0;
}
