#include <iostream>
#include <fstream>
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

struct Game {
    int red = 0;
    int blue = 0;
    int green = 0;
};

struct Games {
    int number = 0;
    vector<Game> games;
};

Game ParseGame(const string& line) {
    Game game;
    vector<string> color_splits = SplitString(line, ',');
    for (auto color_split : color_splits) {
        vector<string> count_splits = SplitString(color_split, ' ');
        if (count_splits[2] == "red") {
            game.red += atoi(count_splits[1].c_str());
        } else if (count_splits[2] == "green") {
            game.green += atoi(count_splits[1].c_str());
        } else if (count_splits[2] == "blue") {
            game.blue += atoi(count_splits[1].c_str());
        }
    }

    return game;
}

Games ParseGames(const string& line) {
    // Parse game number
    Games result;
    vector<string> splits = SplitString(line, ':');
    result.number = atoi(splits.at(0).substr(5).c_str());

    vector<string> game_splits = SplitString(splits.at(1), ';');
    for (auto game_split : game_splits) {
        result.games.emplace_back(move(ParseGame(game_split)));
    }

    return result;
}

int main(int argc, char* argv[]) {
    fstream input("input.txt");
    string line;
    const int kMaxRed = 12;
    const int kMaxGreen = 13;
    const int kMaxBlue = 14;
    int total = 0;
    while (getline(input, line)) {
        const Games games = ParseGames(line);
        bool game_possible = true;
        for (const Game& game : games.games) {
            if (game.red > kMaxRed || game.green > kMaxGreen || game.blue > kMaxBlue) {
                game_possible = false;
                break;
            }
        }

        if (game_possible) {
            total += games.number;
        }
    }

    cout << "The total is " << total << endl;
    return 0;
}
