#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <set>

using namespace std;

set<size_t> FindEmptyRows(const vector<string>& galaxy_map) {
    set<size_t> empty_rows;
    for (size_t i = 0; i < galaxy_map.size(); ++i) {
        if (galaxy_map.at(i).find('#') == string::npos) {
            empty_rows.insert(i);
        }
    }

    cout << "Empty rows: ";
    for (auto iter : empty_rows) {
        cout << iter << " ";
    }
    cout << endl;

    return empty_rows;
}

set<size_t> FindEmptyColumns(const vector<string>& galaxy_map) {
    set<size_t> empty_columns;
    for (size_t i = 0; i < galaxy_map.begin()->size(); ++i) {
        bool has_galaxy = false;
        for (size_t j = 0; j < galaxy_map.size(); ++j) {
            if (galaxy_map.at(j).at(i) == '#') {
                has_galaxy = true;
                break;
            }
        }
        if (!has_galaxy) {
            empty_columns.insert(i);
        }
    }

    cout << "Empty columns: ";
    for (auto iter : empty_columns) {
        cout << iter << " ";
    }
    cout << endl;

    return empty_columns;
}

struct Galaxy {
    int x, y;

};

ostream& operator<<(ostream& out, const Galaxy& galaxy) {
    out << "{" << galaxy.x << "," << galaxy.y << "}";
    return out;
}

vector<Galaxy> FindGalaxies(const vector<string>& galaxy_map) {
    vector<Galaxy> galaxies;
    for (size_t i = 0; i < galaxy_map.size(); ++i) {
        for (size_t j = 0; j < galaxy_map.at(i).size(); ++j) {
            if (galaxy_map.at(i).at(j) == '#') {
                galaxies.emplace_back(j, i);
            }
        }
    }

    cout << "Galaxies:" << endl;
    for (auto iter : galaxies) {
        cout << iter << endl;
    }

    return galaxies;
}

size_t CalculateDistance(const long long start, const long long end, const set<size_t>& jumps) {
    size_t distance = abs(end - start);
    size_t lower = (end < start ? end : start) + 1;  // Add one because we won't ever have a jump on the first one
    const size_t higher = end >= start ? end : start;
    while (lower < higher) {
        if (jumps.find(lower) != jumps.end()) {
            distance += 999999;
        }
        lower++;
    }
    return distance;
}

size_t SumShortestDistancesInExpandedUniverse(const vector<Galaxy>& galaxies, const set<size_t>& empty_rows, const set<size_t>& empty_columns) {
    size_t sum = 0;

    for (auto iter = galaxies.begin(); iter != galaxies.end(); iter++) {
        for (auto other = iter + 1; other != galaxies.end(); other++) {
            sum += CalculateDistance(iter->x, other->x, empty_columns);
            sum += CalculateDistance(iter->y, other->y, empty_rows);     
        }
    }

    return sum;
}

int main(int argc, char* argv[]) {
    string line;
    fstream input("input.txt");
    vector<string> galaxy_map;
    while (getline(input, line)) {
        galaxy_map.push_back(line);
    }

    set<size_t> empty_rows = FindEmptyRows(galaxy_map);
    set<size_t> empty_columns = FindEmptyColumns(galaxy_map);
    vector<Galaxy> galaxies = FindGalaxies(galaxy_map);
    size_t sum = SumShortestDistancesInExpandedUniverse(galaxies, empty_rows, empty_columns);
    cout << "Sum of all shortest distances in expanded universe: " << sum << endl;

    return 0;
}
