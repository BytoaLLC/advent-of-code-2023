#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <utility>

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

struct Point {
    int x = 0;
    int y = 0;
};

ostream& operator<<(ostream& out, const Point& point) {
    out << "{ " << point.x << ", " << point.y << " }";
    return out;
}

bool operator ==(const Point& left, const Point& right) {
    return (left.x == right.x) && (left.y == right.y);
}

bool operator !=(const Point& left, const Point& right) {
    return !(left == right);
}

enum Dir {
    UNKNOWN,
    NORTH,
    SOUTH,
    EAST,
    WEST
};

ostream& operator<<(ostream& out, const Dir& dir) {
    switch (dir) {
    case NORTH: out << "NORTH"; break;
    case SOUTH: out << "SOUTH"; break;
    case EAST: out << "EAST"; break;
    case WEST: out << "WEST"; break;
    case UNKNOWN:
    default: out << "UNKNOWN"; break;
    }
    return out;
}

bool PathPossible(const vector<string>& nodes, const Point from, const Dir to) {
    // Get source point
    char from_type = nodes.at(from.y).at(from.x);
    char to_type = 'x';
    switch (to) {
    case NORTH: {
        bool from_ok = (
            from_type == 'S' ||
            from_type == '|' ||
            from_type == 'L' ||
            from_type == 'J'
        );

        to_type = nodes.at(from.y - 1).at(from.x);
        bool to_ok = (
            to_type == 'S' ||
            to_type == '|' ||
            to_type == '7' ||
            to_type == 'F'
        );
        return from_ok && to_ok;
    }
    case SOUTH: {
        bool from_ok = (
            from_type == 'S' ||
            from_type == '|' ||
            from_type == '7' ||
            from_type == 'F'
        );

        to_type = nodes.at(from.y + 1).at(from.x);
        bool to_ok = (
            to_type == 'S' ||
            to_type == '|' ||
            to_type == 'L' ||
            to_type == 'J'
        );
        return from_ok && to_ok;
    }
    case EAST: {
        bool from_ok = (
            from_type == 'S' ||
            from_type == '-' ||
            from_type == 'L' ||
            from_type == 'F'
        );

        to_type = nodes.at(from.y).at(from.x + 1);
        bool to_ok = (
            to_type == 'S' ||
            to_type == '-' ||
            to_type == '7' ||
            to_type == 'J'
        );
        return from_ok && to_ok;
    }
    case WEST: {
        bool from_ok = (
            from_type == 'S' ||
            from_type == '-' ||
            from_type == '7' ||
            from_type == 'J'
        );

        to_type = nodes.at(from.y).at(from.x - 1);
        bool to_ok = (
            to_type == 'S' ||
            to_type == '-' ||
            to_type == 'L' ||
            to_type == 'F'
        );
        return from_ok && to_ok;
    }
    default: return false;
    }
}

int main(int argc, char* argv[]) {
    string line;
    fstream input("input.txt");
    vector<string> nodes;
    Point start;
    while (getline(input, line)) {
        // Add boundary characters
        line = "x" + line + "x";

        // Add first row boundary
        if (nodes.empty()) {
            nodes.push_back(string(line.size(), 'x'));
            cout << "line: " << nodes.front() << endl;
        }

        // Look for start
        size_t pos = line.find('S');
        if (pos != string::npos) {
            start.x = pos;
            start.y = nodes.size();
        }

        // Add boundaries with the 'x's
        nodes.push_back(line);
        cout << "line: " << nodes.back() << endl;
    }

    // Add boundary for the end
    nodes.push_back(string(nodes.back().size(), 'x'));
    cout << "line: " << nodes.back() << endl;
    cout << "Start: " << start << endl;

    Point current = start;
    Dir from = UNKNOWN;
    vector<Point> path;
    int path_length = 0;
    do {
        if (from != NORTH && PathPossible(nodes, current, NORTH)) {
            cout << "North viable" << endl;
            current = {current.x, current.y - 1};
            from = SOUTH;
        }
        else if (from != SOUTH && PathPossible(nodes, current, SOUTH)) {
            cout << "South viable" << endl;
            current = {current.x, current.y + 1};
            from = NORTH;
        }
        else if (from != EAST && PathPossible(nodes, current, EAST)) {
            cout << "East viable" << endl;
            current = {current.x + 1, current.y};
            from = WEST;
        }
        else if (from != WEST && PathPossible(nodes, current, WEST)) {
            cout << "West viable" << endl;
            current = {current.x - 1, current.y};
            from = EAST;
        }
        path_length++;
    } while (current != start);
    cout << "Found the start" << endl;
    cout << "Took a total of " << path_length << " steps" << endl;
    cout << "Furthest point is " << path_length / 2 << " steps" << endl;
    return 0;
}
