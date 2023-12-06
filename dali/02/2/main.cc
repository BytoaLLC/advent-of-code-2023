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
    int total = 0;
    while (getline(input, line)) {
        const Games games = ParseGames(line);
        Game max_game;
        for (const Game& game : games.games) {
            if (game.red > max_game.red) {
                max_game.red = game.red;
            }
            if (game.blue > max_game.blue) {
                max_game.blue = game.blue;
            }
            if (game.green > max_game.green) {
                max_game.green = game.green;
            }
        }
        total += max_game.red * max_game.blue * max_game.green;
    }

    cout << "The sum total of all powers is " << total << endl;

    return 0;
}
