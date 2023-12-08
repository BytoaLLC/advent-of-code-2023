#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <limits>

using namespace std;

vector<string> SplitString(const string &s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

vector<long long> ParseSeeds(const string& line) {
    vector<string> colon_split = SplitString(line, ':');
    vector<string> num_split = SplitString(colon_split[1], ' ');
    vector<long long> seeds;
    for (auto num : num_split) {
        if (num.empty()) {
            continue;
        }
        seeds.push_back(atoll(num.c_str()));
    }
    return seeds;
}

struct Mapping {
    long long dest = 0;
    long long src = 0;
    long long size = 0;

    bool Map(const long long input, long long& output) {
        if (input >= src  && input < (src + size)) {
            const long long diff = dest - src;
            output = input + diff;
            return true;
        } else {
            output = input;
            return false;
        }
    }
};

Mapping ParseRange(const string& line) {
    vector<string> splits = SplitString(line, ' ');
    Mapping mapping;
    mapping.dest = atoll(splits[0].c_str());
    mapping.src = atoll(splits[1].c_str());
    mapping.size = atoll(splits[2].c_str());
    return mapping;
}

vector<Mapping> ParseRanges(istream& input) {
    string line;
    getline(input, line);  // title

    vector<Mapping> mappings;
    getline(input, line);  // first row
    while (!line.empty()) {
        mappings.emplace_back(move(ParseRange(line)));
        if (!getline(input, line)) {
            break;
        }
    }
    return mappings;
}

int main(int argc, char* argv[]) {
    fstream input("input.txt");
    string line;
    getline(input, line);
    vector<long long> seeds = ParseSeeds(line);
    getline(input, line);  // newline

    constexpr int kMappings = 7;
    vector<Mapping> mappings[kMappings];
    for (int i = 0; i < kMappings; ++i) {
        mappings[i] = ParseRanges(input);
    }

    long long lowest_result = numeric_limits<long long>::max();
    for (auto seed : seeds) {
        long long current = seed;
        for (int i = 0; i < kMappings; ++i) {
            for (auto mapping : mappings[i]) {
                if (mapping.Map(current, current)) {
                    break;
                }
            }
        }
        cout << "Seed " << seed << " maps to " << current << endl;
        if (current < lowest_result) {
            lowest_result = current;
        }
    }

    cout << "Lowest result: " << lowest_result << endl;
    return 0;
}
