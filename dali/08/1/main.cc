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

int main(int argc, char* argv[]) {
    string instructions;
    map<string, Node> nodes;
    ParseFile("input.txt", instructions, nodes);
    bool z_found = false;
    int count = 0;
    string current = "AAA";
    while (!z_found) {
        for (auto iter : instructions) {
            count++;
            if (iter =='R') {
                current = nodes.at(current).right;
            } else {
                current = nodes.at(current).left;
            }
            if (current == "ZZZ") {
                z_found = true;
                break;
            }
        }
    }
    cout << "Count: " << count << endl;
    return 0;
}
