#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <sstream>

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

set<int> ParseCard(const string& line, set<int>& draws) {
    vector<string> label_split = SplitString(line, ':');
    vector<string> winner_split = SplitString(label_split[1], '|');
    vector<string> draw_split = SplitString(winner_split[1], ' ');
    for (auto draw : draw_split) {
        if (draw.empty()) {
            continue;
        }
        draws.insert(atoi(draw.c_str()));
    }
    vector<string> num_split = SplitString(winner_split[0], ' ');
    set<int> result;
    for (auto num : num_split) {
        if (num.empty()) {
            continue;
        }
        result.insert(atoi(num.c_str()));
    }
    return result;
}

int main(int argc, char* argv[]) {
    fstream input("input.txt");
    string line;
    int total = 0;
    while (getline(input, line)) {
        int card_total = 0;
        set<int> draws;
        set<int> winners = ParseCard(line, draws);
        for (auto draw : draws) {
            if (winners.contains(draw)) {
                if (card_total == 0) {
                    card_total = 1;
                } else {
                    card_total *= 2;
                }
            }
        }
        total += card_total;
    }

    cout << "The total is " << total << endl;

    return 0;
}
