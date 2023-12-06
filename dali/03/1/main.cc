#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

inline bool HasSymbolCloseBy(const vector<vector<char>>& schematic, const int row, const int column) {
    if ((!isdigit(schematic[row    ][column + 1]) && schematic[row    ][column + 1] != '.') ||
        (!isdigit(schematic[row + 1][column + 1]) && schematic[row + 1][column + 1] != '.') ||
        (!isdigit(schematic[row + 1][column    ]) && schematic[row + 1][column    ] != '.') ||
        (!isdigit(schematic[row + 1][column - 1]) && schematic[row + 1][column - 1] != '.') ||
        (!isdigit(schematic[row    ][column - 1]) && schematic[row    ][column - 1] != '.') ||
        (!isdigit(schematic[row - 1][column - 1]) && schematic[row - 1][column - 1] != '.') ||
        (!isdigit(schematic[row - 1][column    ]) && schematic[row - 1][column    ] != '.') ||
        (!isdigit(schematic[row - 1][column + 1]) && schematic[row - 1][column + 1] != '.')) {
        return true;
    }
    return false;
}

int main(int argc, char* argv[]) {
    fstream input("input.txt");
    string line;
    
    // Copy schematic to memory, shouldn't be too bad ~20kB for large input
    vector<vector<char>> schematic;
    while (getline(input, line)) {
        schematic.push_back({});
        for (auto letter : line) {
            schematic.back().push_back(letter);
        }
    }

    // Add buffer at the edges to avoid constant boundary checking
    schematic.insert(schematic.begin(), vector<char>(schematic.at(0).size(), '.'));
    schematic.emplace_back(schematic.at(0).size(), '.');
    for (int i = 0; i < schematic.size(); ++i) {
        schematic.at(i).insert(schematic.at(i).begin(), '.');
        schematic.at(i).push_back('.');
    }
    
    int total = 0;
    bool in_number = false;
    bool has_symbol = false;
    string number;
    for (int y = 1; y < schematic.size() - 1; ++y) {
        for (int x = 1; x < schematic.at(y).size() - 1; ++x) {
            if (in_number) {
                if (!isdigit(schematic[y][x])) {
                    // At end of number. Parse number. Reset has_symbol. Reset in_number.
                    if (has_symbol) {
                        total += atoi(number.c_str());
                    }
                    number.clear();
                    in_number = false;
                    has_symbol = false;
                    continue;
                }
                has_symbol |= HasSymbolCloseBy(schematic, y, x);
                number.push_back(schematic[y][x]);
            } else {
                if (isdigit(schematic[y][x])) {
                    has_symbol |= HasSymbolCloseBy(schematic, y, x);
                    in_number = true;
                    number.push_back(schematic[y][x]);
                }
            }
        }
    }

    cout << "Total is " << total << endl;
    return 0;
}
