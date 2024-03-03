#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

using namespace std;

int GetNextInSequence(const vector<int>& sequence) {
    vector<vector<int>> differences;
    differences.push_back(sequence);
    bool all_same = false;
    while (!all_same) {
        differences.push_back({});
        auto lesser = differences.at(differences.size() - 2).begin();
        auto greater = lesser + 1;
        all_same = true;
        while (greater != differences.at(differences.size() - 2).end()) {
            if (all_same && (*greater != *lesser)) {
                all_same = false;
            }

            differences.back().push_back(*greater - *lesser);
            greater++;
            lesser++;
        }
    }

    for (auto outter : differences) {
        for (auto inner : outter) {
            cout << inner << " ";
        }
        cout << endl;
    }

    auto upper = differences.rbegin() + 1;
    auto lower = differences.rbegin();
    int current_diff = 0;
    while (upper != differences.rend()) {
        current_diff = upper->back() + current_diff;
        upper++;
        lower++;
    }

    return current_diff;
}

std::vector<std::string> SplitString(const std::string& str, const std::string& delimiter) {
    std::vector<std::string> tokens;
    char* ptr = strtok(const_cast<char*>(str.data()), delimiter.c_str());

    while (ptr != nullptr) {
        tokens.push_back(ptr);
        ptr = strtok(nullptr, delimiter.c_str());
    }

    return tokens;
}

vector<int> ParseSequence(const string& line) {
    vector<string> split = SplitString(line, " ");
    vector<int> sequence;
    for (auto num : split) {
        sequence.push_back(atoi(num.c_str()));
    }
    return sequence;
}

int main(int argc, char* argv[]) {
    string line;
    fstream input("input.txt");
    int total = 0;
    while (getline(input, line)) {
        vector<int> sequence = ParseSequence(line);
        int next = GetNextInSequence(sequence);
        total += next;
        cout << "Next: " << next << endl;
    }
    cout << "Total: " << total << endl;
    return 0;
}
