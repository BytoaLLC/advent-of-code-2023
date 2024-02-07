#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <limits>
#include <set>

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

struct Range {
    long long start = 0;
    long long end = 0;
};

struct Mapping {
    Range source;
    Range dest;
};

vector<Range> ParseSeeds(const string& line) {
    vector<string> colon_split = SplitString(line, ':');
    vector<string> num_split = SplitString(colon_split[1], ' ');
    vector<Range> seeds;
    int i = 0;
    while (i < num_split.size()) {
        if (num_split.at(i).empty()) {
            i++;
            continue;
        }
        Range range;
        range.start = atoll(num_split.at(i).c_str());
        range.end = range.start + atoll(num_split.at(i+1).c_str());
        seeds.emplace_back(std::move(range));
        i += 2;
    }
    return seeds;
}

Mapping ParseRange(const string& line) {
    vector<string> splits = SplitString(line, ' ');
    Mapping mapping;
    mapping.dest.start = atoll(splits[0].c_str());
    mapping.source.start = atoll(splits[1].c_str());

    const long long size = atoll(splits[2].c_str());
    mapping.dest.end = mapping.dest.start + size;
    mapping.source.end = mapping.source.start + size;
    return mapping;
}

vector<Mapping> ParseRanges(istream& input) {
    string line;
    getline(input, line);  // title

    vector<Mapping> mappings;
    getline(input, line);  // first row
    while (!line.empty()) {
        mappings.emplace_back(move(ParseRange(line)));
        if (!getline(input, line)) {
            break;
        }
    }
    return mappings;
}

// Returns true if a portion was mapped
bool MapSingle(const Range& range, const Mapping& mapping, vector<Range>& unmapped, vector<Range>& mapped) {
    if ((range.end <= mapping.source.start) || (range.start >= mapping.source.end)) {
        return false;
    }

    if (range.start < mapping.source.start) {
        unmapped.emplace_back(range.start, mapping.source.start);
    }

    Range mapped_range;
    const long long diff = (mapping.dest.start - mapping.source.start);
    mapped_range.start = max(mapping.source.start, range.start) + diff;
    mapped_range.end = min(mapping.source.end, range.end) + diff;
    mapped.push_back(mapped_range);

    if (range.end > mapping.source.end) {
        unmapped.emplace_back(mapping.source.end, range.end);
    }

    return true;
}

int main(int argc, char* argv[]) {
    fstream input("input.txt");
    string line;
    getline(input, line);
    vector<Range> seeds = ParseSeeds(line);
    getline(input, line);  // newline

    const int kMappings = 7;
    vector<vector<Mapping>> all_mappings;
    for (int i = 0; i < kMappings; ++i) {
        all_mappings.emplace_back(ParseRanges(input));
    }

    for (auto mappings : all_mappings) {
        cout << "mapping:" << endl;
        for (auto mapping : mappings) {
            cout << mapping.dest.start << "," << mapping.dest.end;
            cout << " <- " << mapping.source.start << "," << mapping.source.end << endl;
        }
    }

    long long lowest = numeric_limits<long long>::max();
    for (auto seed : seeds) {
        vector<Range> ranges_to_map = { seed };
        vector<Range> mapped;
        for (auto mappings : all_mappings) {
            mapped.clear();
            while (!ranges_to_map.empty()) {
                Range range = ranges_to_map.back();
                ranges_to_map.pop_back();
                bool was_mapped = false;
                for (auto mapping : mappings) {
                    if (MapSingle(range, mapping, ranges_to_map, mapped)) {
                        was_mapped = true;
                        break;
                    }
                }
                if (!was_mapped) {
                    mapped.push_back(range);
                }
            }
            ranges_to_map = mapped;
        }

        cout << "seed " << seed.start << "," << seed.end << " mapped to ";
        for (auto mapped_seed : mapped) {
            if (mapped_seed.start < lowest) {
                lowest = mapped_seed.start;
            }
        }
        cout << lowest << endl;
    }

    return 0;
}
