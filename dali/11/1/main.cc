#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

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

vector<string> Transpose(const vector<string>& galaxies) {
    // Number of transposed rows == original number of columns
    vector<string> transposed(galaxies.begin()->size());
    for (const auto& row : galaxies) {
        for (size_t i = 0; i < row.size(); ++i) {
            transposed.at(i).push_back(row.at(i));
        }
    }
    return transposed;
}

inline void DuplicateEmptyRows(vector<string>& galaxies) {
    for (auto iter = galaxies.begin(); iter != galaxies.end(); iter++) {
        if (iter->find_first_not_of('.') == string::npos) {
            iter = galaxies.insert(iter, *iter);
            iter++;
        }
    }
}

vector<string> ExpandUniverse(const vector<string>& galaxies) {
    // Expand rows
    vector<string> rows_expanded = galaxies;
    DuplicateEmptyRows(rows_expanded);

    cout << "After row expansion" << endl;
    for (auto iter : rows_expanded) {
        cout << iter << endl;
    }

    // Transpose the galaxy map
    vector<string> transposed = Transpose(rows_expanded);
    cout << "After transpose" << endl;
    for (auto iter : transposed) {
        cout << iter << endl;
    }

    DuplicateEmptyRows(transposed);

    cout << "After column expansion, still transposed" << endl;
    for (auto iter : transposed) {
        cout << iter << endl;
    }

    return Transpose(transposed);
}

struct Galaxy {
    int x, y;
};

vector<Galaxy> FindGalaxies(const vector<string>& galaxy_map) {
    vector<Galaxy> galaxies;
    for (int i = 0; i < galaxy_map.size(); i++) {
        for (int j = 0; j < galaxy_map.at(i).size(); j++) {
            if (galaxy_map.at(i).at(j) == '#') {
                galaxies.emplace_back(j, i);
            }
        }
    }
    return galaxies;
}

ostream& operator<<(ostream& out, const Galaxy& galaxy) {
    out << "{" << galaxy.x << ", " << galaxy.y << "}";
    return out;
}

int SumShortestPathOfAllPairs(const vector<Galaxy>& galaxies) {
    int sum = 0;

    int pairs_found = 0;
    for (auto iter = galaxies.begin(); iter != galaxies.end(); iter++) {
        for (auto other = iter + 1; other != galaxies.end(); other++) {
            cout << "Pair found: " << *iter << " and " << *other << endl;
            pairs_found++;
            sum += abs(iter->x - other->x) + abs(iter->y - other->y);
        }
    }

    cout << pairs_found << " pairs found" << endl;

    return sum;
}

int main(int argc, char* argv[]) {
    string line;
    fstream input("input.txt");
    vector<string> galaxy_map;
    while (getline(input, line)) {
        galaxy_map.push_back(line);
    }

    cout << "Before expansion" << endl;
    for (auto row : galaxy_map) {
        cout << row << endl;
    }

    galaxy_map = ExpandUniverse(galaxy_map);

    cout << "After expansion" << endl;
    for (auto row : galaxy_map) {
        cout << row << endl;
    }

    vector<Galaxy> galaxies = FindGalaxies(galaxy_map);
    cout << "Identified galaxies" << endl;
    for (auto iter : galaxies) {
        cout << iter << endl;
    }

    int sum = SumShortestPathOfAllPairs(galaxies);
    cout << "Sum of all shortest paths: " << sum << endl;

    return 0;
}
