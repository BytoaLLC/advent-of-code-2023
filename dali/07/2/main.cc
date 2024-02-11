#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include <map>
#include <array>

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

inline int MapCardCharToInt(const char card) {
    switch (card) {
    case 'J': return -1;
    case '2': return 0;
    case '3': return 1;
    case '4': return 2;
    case '5': return 3;
    case '6': return 4;
    case '7': return 5;
    case '8': return 6;
    case '9': return 7;
    case 'T': return 8;
    case 'Q': return 10;
    case 'K': return 11;
    case 'A': return 12;
    default: throw runtime_error("Can't map " + card);
    }
}

inline bool CardIsLessThan(const char lhs, const char rhs) {
    return MapCardCharToInt(lhs) < MapCardCharToInt(rhs);
}

struct Hand {
    string hand;
    int bid;

    // Make compliant with sort() in an iterable container
    bool operator < (const Hand& rhs) const {
        auto lhs_card = hand.begin();
        auto rhs_card = rhs.hand.begin();
        while (lhs_card != hand.end() && rhs_card != rhs.hand.end() && *lhs_card == *rhs_card) {
            lhs_card++;
            rhs_card++;
        }
        if (lhs_card == hand.end() || rhs_card == rhs.hand.end()) {
            cerr << "WARNING: Hands are the same or too short" << endl;
            return false;
        }
        return CardIsLessThan(*lhs_card, *rhs_card);
    }
};

vector<Hand> ParseFile(const string& path) {
    string line;
    ifstream input(path);
    vector<Hand> hands;
    while (getline(input, line)) {
        vector<string> parts = SplitString(line, " ");
        hands.emplace_back(parts.at(0), atoi(parts.at(1).c_str()));
    }
    return hands;
}

enum HandType {
    HIGH_CARD = 0,
    ONE_PAIR = 1,
    TWO_PAIR = 2,
    THREE_OF_A_KIND = 3,
    FULL_HOUSE = 4,
    FOUR_OF_A_KIND = 5,
    FIVE_OF_A_KIND = 6,
    MAX_HAND_TYPES = 7
};

constexpr int kMaxHandTypes = (int)MAX_HAND_TYPES;

ostream& operator<<(ostream& out, const HandType& hand_type) {
    switch (hand_type) {
    case (HIGH_CARD): out << "HIGH_CARD"; break;
    case (ONE_PAIR): out << "ONE_PAIR"; break;
    case (TWO_PAIR): out << "TWO_PAIR"; break;
    case (THREE_OF_A_KIND): out << "THREE_OF_A_KIND"; break;
    case (FULL_HOUSE): out << "FULL_HOUSE"; break;
    case (FOUR_OF_A_KIND): out << "FOUR_OF_A_KIND"; break;
    case (FIVE_OF_A_KIND): out << "FIVE_OF_A_KIND"; break;
    default: break;
    }
    return out;
}

HandType GetBestHandType(const map<char, int>& counts) {
    if (counts.size() == 1) {
        return FIVE_OF_A_KIND;
    }

    HandType best_hand_type = HIGH_CARD;
    if (counts.find('J') != counts.end()) {
        for (auto& iter : counts) {
            if (iter.first == 'J') {
                continue;
            }

            map<char, int> new_counts = counts;
            new_counts['J']--;
            if (new_counts['J'] == 0) {
                new_counts.erase('J');
            }
            new_counts[iter.first]++;
            HandType new_hand_type = GetBestHandType(new_counts);
            if ((int)new_hand_type > (int)best_hand_type) {
                best_hand_type = new_hand_type;
            }
        }
        return best_hand_type;
    }

    if (counts.size() == 2) {
        for (auto iter : counts) {
            if (iter.second == 4) {
                return FOUR_OF_A_KIND;
            }
        }
        return FULL_HOUSE;
    }

    if ((counts.size() == 4) || (counts.size() == 3)) {
        int num_pairs = 0;
        for (auto iter : counts) {
            if (iter.second == 3) {
                return THREE_OF_A_KIND;
            }
            if (iter.second == 2) {
                num_pairs++;
            }
        }
        if (num_pairs == 2) {
            return TWO_PAIR;
        }
        return ONE_PAIR;
    }

    return HIGH_CARD;
}

HandType GetBestHandType(const Hand& hand) {
    map<char, int> counts;
    for (auto card : hand.hand) {
        counts[card]++;
    }
    return GetBestHandType(counts);
}

vector<Hand> SortHands(const vector<Hand>& hands) {
    // Sort hands by type
    array<vector<Hand>, kMaxHandTypes> sorted_by_hand_type;
    for (auto& hand : hands) {
        HandType hand_type = GetBestHandType(hand);
        sorted_by_hand_type.at(hand_type).push_back(hand);
    }

    // Sort hands of a certain type then add to result
    vector<Hand> all_sorted;
    for (auto& hands_of_a_type : sorted_by_hand_type) {
        sort(hands_of_a_type.begin(), hands_of_a_type.end());
        for (auto& hand : hands_of_a_type) {
            all_sorted.push_back(hand);
        }
    }

    return all_sorted;
}

int main(int argc, char* argv[]) {
    vector<Hand> hands = ParseFile("input.txt");
    hands = SortHands(hands);

    int total_winnings = 0;
    int rank = 1;
    cout << "Sorted: " << endl;
    for (auto hand : hands) {
        cout << "  " << hand.hand << " " << hand.bid << " " << GetBestHandType(hand) << endl;
        total_winnings += (rank * hand.bid);
        rank++;
    }
    cout << "Total winnings: " << total_winnings << endl;
    return 0;
}
