#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <cstring>

using namespace std;

struct Node {
    string left;
    string right;
};

void ParseFile(const string& path, string& instructions, map<string, Node>& nodes) {
    ifstream input(path);
    string line;
    getline(input, instructions);
    getline(input, line);
    while (getline(input, line)) {
        string source = line.substr(0, 3);
        string left = line.substr(7, 3);
        string right = line.substr(12, 3);
        nodes.emplace(std::piecewise_construct,
            std::forward_as_tuple(source),
            std::forward_as_tuple(left, right));
    }
}

vector<string> FindNodesEndingInA(const map<string, Node>& nodes) {
    vector<string> nodes_ending_in_a;
    for (auto iter : nodes) {
        if (iter.first.back() == 'A') {
            nodes_ending_in_a.push_back(iter.first);
        }
    }
    return nodes_ending_in_a;
}

int main(int argc, char* argv[]) {
    string instructions;
    map<string, Node> nodes;
    ParseFile("input.txt", instructions, nodes);
    bool z_found = false;
    size_t total = 1;
    vector<string> currents = FindNodesEndingInA(nodes);
    for (auto start : currents) {
        string current = start;
        auto current_instruction = instructions.begin();
        size_t count = 0;
        while (current.back() != 'Z') {
            if (*current_instruction == 'L') {
                current = nodes.at(current).left;
            } else {
                current = nodes.at(current).right;
            }
            current_instruction++;
            if (current_instruction == instructions.end()) {
                current_instruction = instructions.begin();
                count++;
            }
        }
        if (current.back() == 'Z') {
            cout << "Count found for start " << start << "->" << current << ": " << count << endl;
        }

        count = 0;
        string mid_start = current;
        do {
            if (*current_instruction == 'L') {
                current = nodes.at(current).left;
            } else {
                current = nodes.at(current).right;
            }
            current_instruction++;
            if (current_instruction == instructions.end()) {
                current_instruction = instructions.begin();
                count++;
            }
        } while (current.back() != 'Z');

        cout << "Count found for cycle of " << mid_start << "->" << current << ": " << count << endl;
        total *= count;
    }
    cout << "Total: " << total * instructions.size() << endl;
    return 0;
}
