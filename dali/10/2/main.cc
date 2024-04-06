#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <utility>
#include <set>
#include <sstream>

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

static vector<string> nodes;

struct Point;
ostream& operator <<(ostream& out, const Point& point);

struct Point {
    int x = 0;
    int y = 0;

    char Get() const {
        return nodes.at(y).at(x);
    }

    Point North() const {
        return {x, y - 1};
    }

    void GoNorth() {
        *this = North();
    }

    Point South() const {
        return {x, y + 1};
    }

    void GoSouth() {
        *this = South();
    }

    Point East() const {
        return {x + 1, y};
    }

    void GoEast() {
        *this = East();
    }

    Point West() const {
        return {x - 1, y};
    }

    void GoWest() {
        *this = West();
    }

    bool operator <(const Point& other) const {
        stringstream this_strm;
        this_strm << *this;
        stringstream other_strm;
        other_strm << other;
        return (strcmp(this_strm.str().c_str(), other_strm.str().c_str()) < 0);
    }
};

ostream& operator <<(ostream& out, const Point& point) {
    out << "{ " << point.x << ", " << point.y << " }";
    return out;
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

void FindDots(const Point& start, set<Point>& dots, set<Point>& visited) {
    if (start.Get() == 'x') {
        return;
    }

    if (visited.find(start) != visited.end()) {
        return;
    }

    dots.insert(start);
    visited.insert(start);

    FindDots(start.North(), dots, visited);
    FindDots(start.East(), dots, visited);
    FindDots(start.South(), dots, visited);
    FindDots(start.West(), dots, visited);
}

struct Compass {
    Point position;
    Dir forward;
    set<Point> a_dots;
    set<Point> b_dots;

    char Get() const {
        return nodes.at(position.y).at(position.x);
    }

    void ProcessDots(set<Point>& visited) {
        switch (forward) {
        case NORTH: {
            switch (Get()) {
                case '|': {
                    FindDots(position.West(), a_dots, visited);
                    FindDots(position.East(), b_dots, visited);
                    break;
                }
                case 'L': {
                    FindDots(position.West(), a_dots, visited);
                    FindDots(position.South(), a_dots, visited);
                    break;
                }
                case 'J': {
                    FindDots(position.East(), b_dots, visited);
                    FindDots(position.South(), b_dots, visited);
                    break;
                }
            }
            break;
        }
        case SOUTH: {
            switch (Get()) {
                case '|': {
                    FindDots(position.East(), a_dots, visited);
                    FindDots(position.West(), b_dots, visited);
                    break;
                }
                case '7': {
                    FindDots(position.North(), a_dots, visited);
                    FindDots(position.East(), a_dots, visited);
                    break;
                }
                case 'F': {
                    FindDots(position.North(), b_dots, visited);
                    FindDots(position.West(), b_dots, visited);
                    break;
                }
            }
            break;
        }
        case EAST: {
            switch (Get()) {
                case '-': {
                    FindDots(position.North(), a_dots, visited);
                    FindDots(position.South(), b_dots, visited);
                    break;
                }
                case 'L': {
                    FindDots(position.West(), b_dots, visited);
                    FindDots(position.South(), b_dots, visited);
                    break;
                }
                case 'F': {
                    FindDots(position.North(), a_dots, visited);
                    FindDots(position.West(), a_dots, visited);
                    break;
                }
            }
            break;
        }
        case WEST: {
            switch (Get()) {
                case '-': {
                    FindDots(position.South(), a_dots, visited);
                    FindDots(position.North(), b_dots, visited);
                    break;
                }
                case '7': {
                    FindDots(position.East(), b_dots, visited);
                    FindDots(position.North(), b_dots, visited);
                    break;
                }
                case 'J': {
                    FindDots(position.East(), a_dots, visited);
                    FindDots(position.South(), a_dots, visited);
                    break;
                }
            }
            break;
        }
        }
    }

    void Orient(const Dir from) {
        switch (from) {
        case NORTH: {
            if (Get() == 'L') {
                forward = EAST;
            } else if (Get() == 'J') {
                forward = WEST;
            }
            break;
        }
        case EAST: {
            if (Get() == 'L') {
                forward = NORTH;
            } else if (Get() == 'F') {
                forward = SOUTH;
            }
            break;
        }
        case SOUTH: {
            if (Get() == '7') {
                forward = WEST;
            } else if (Get() == 'F') {
                forward = EAST;
            }
            break;
        }
        case WEST:{
            if (Get() == '7') {
                forward = SOUTH;
            } else if (Get() == 'J') {
                forward = NORTH;
            }
            break;
        }
        };
    }

    void Move() {
        switch (forward) {
        case NORTH: position.GoNorth(); Orient(SOUTH); break;
        case EAST: position.GoEast(); Orient(WEST); break;
        case SOUTH: position.GoSouth(); Orient(NORTH); break;
        case WEST: position.GoWest(); Orient(EAST); break;
        }
    }
};

int main(int argc, char* argv[]) {
    string line;
    fstream input("input.txt");
    Point start;
    while (getline(input, line)) {
        // Add boundary characters
        line = "x" + line + "x";

        // Add first row boundary
        if (nodes.empty()) {
            nodes.push_back(string(line.size(), 'x'));
        }

        // Look for start
        size_t pos = line.find('S');
        if (pos != string::npos) {
            start.x = pos;
            start.y = nodes.size();
        }

        // Add boundaries with the 'x's
        nodes.push_back(line);
    }

    // Add boundary for the end
    nodes.push_back(string(nodes.back().size(), 'x'));
    cout << "Start: " << start << endl;

    // Determine initial direction from start
    Compass compass;
    compass.position = start;
    Dir start_dir = UNKNOWN;
    if (start.North().Get() == '|' || start.North().Get() == 'F' || start.North().Get() == '7') {
        compass.forward = start_dir = NORTH;
    } else if (start.South().Get() == '|' || start.South().Get() == 'L' || start.South().Get() == 'J') {
        compass.forward = start_dir = SOUTH;
    } else if (start.East().Get() == '-' || start.East().Get() == '7' || start.East().Get() == 'J' ) {
        compass.forward = start_dir = EAST;
    } else if (start.West().Get() == '-' || start.West().Get() == 'F' || start.West().Get() == 'L') {
        compass.forward = start_dir = WEST;
    }

    // First pass to establish on-route nodes
    set<Point> visited{ compass.position };
    do {
        compass.Move();
        visited.insert(compass.position);
    } while (compass.Get() != 'S');

    cout << "First pass done" << endl;

    // Second pass to process non-route nodes
    compass.position = start;
    compass.forward = start_dir;
    compass.ProcessDots(visited);
    do {
        compass.Move();
        compass.ProcessDots(visited);
    } while (compass.Get() != 'S');

    cout << "Second pass done" << endl;
    cout << "Side a: " << compass.a_dots.size() << endl;
    cout << "Side b: " << compass.b_dots.size() << endl;

    return 0;
}
