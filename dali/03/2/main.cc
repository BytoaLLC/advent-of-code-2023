#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <set>

using namespace std;

struct Point {
    int x = 0;
    int y = 0;
};

inline bool HasGearSymbolCloseBy(const vector<vector<char>>& schematic, const int row, const int column, vector<Point>& gears) {
    bool has_gear = false;
    if ((!isdigit(schematic[row    ][column + 1]) && schematic[row    ][column + 1] == '*')) {
        gears.emplace_back(column + 1, row);
        has_gear = true;
    }
    if ((!isdigit(schematic[row + 1][column + 1]) && schematic[row + 1][column + 1] == '*')) {
        gears.emplace_back(column + 1, row + 1);
        has_gear = true;
    }
    if ((!isdigit(schematic[row + 1][column    ]) && schematic[row + 1][column    ] == '*')) {
        gears.emplace_back(column, row + 1);
        has_gear = true;
    }
    if ((!isdigit(schematic[row + 1][column - 1]) && schematic[row + 1][column - 1] == '*')) {
        gears.emplace_back(column - 1, row + 1);
        has_gear = true;
    }
    if ((!isdigit(schematic[row    ][column - 1]) && schematic[row    ][column - 1] == '*')) {
        gears.emplace_back(column - 1, row);
        has_gear = true;
    }
    if ((!isdigit(schematic[row - 1][column - 1]) && schematic[row - 1][column - 1] == '*')) {
        gears.emplace_back(column - 1, row - 1);
        has_gear = true;
    }
    if ((!isdigit(schematic[row - 1][column    ]) && schematic[row - 1][column    ] == '*')) {
        gears.emplace_back(column, row - 1);
        has_gear = true;
    }
    if ((!isdigit(schematic[row - 1][column + 1]) && schematic[row - 1][column + 1] == '*')) {
        gears.emplace_back(column + 1, row - 1);
        has_gear = true;
    }
    return has_gear;
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
    
    bool in_number = false;
    string number;
    map<int, map<int, vector<int>>> gears;
    vector<Point> current_gears;
    bool number_added = false;
    for (int y = 1; y < schematic.size() - 1; ++y) {
        for (int x = 1; x < schematic.at(y).size() - 1; ++x) {
            if (in_number) {
                if (!isdigit(schematic[y][x])) {
                    for (auto current_gear : current_gears) {
                        gears[current_gear.y][current_gear.x].push_back(atoi(number.c_str()));
                    }
                    number.clear();
                    current_gears.clear();
                    in_number = false;
                    number_added = false;
                    continue;
                }
                if (!number_added) {
                    number_added |= HasGearSymbolCloseBy(schematic, y, x, current_gears);
                }
                number.push_back(schematic[y][x]);
            } else {
                if (isdigit(schematic[y][x])) {
                    number_added |= HasGearSymbolCloseBy(schematic, y, x, current_gears);
                    in_number = true;
                    number.push_back(schematic[y][x]);
                }
            }
        }
    }

    int total = 0;
    for (auto gear_y : gears) {
        for (auto gear_x : gear_y.second) {
            if (gear_x.second.size() == 2) {
                total += gear_x.second.at(0) * gear_x.second.at(1);
            }
        }
    }

    cout << "Total is " << total << endl;

    return 0;
}
