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

bool MapSingle(const Mapping& mapping, const Range& range, vector<Range>& unmapped, Range& mapped) {
    if ((range.end <= mapping.source.start) || (range.start >= mapping.source.end)) {
        unmapped.push_back(range);
        return false;
    }

    if (range.start < mapping.source.start) {
        unmapped.emplace_back(range.start, mapping.source.start);
    }

    const long long diff = (mapping.dest.start - mapping.source.start);
    mapped.start = max(mapping.source.start, range.start) + diff;
    mapped.end = min(mapping.source.end, range.end) + diff;

    if (range.end > mapping.source.end) {
        unmapped.emplace_back(mapping.source.end, range.end);
    }

    return true;
}

struct MapQuery {
    Range range;
    int level = 0;
};

vector<Range> Map(const vector<vector<Mapping>>& mappings, Range start) {
    vector<MapQuery> map_queries;
    map_queries.emplace_back(start, 0);

    vector<Range> results;
    while (!map_queries.empty()) {
        MapQuery map_query = map_queries.back();
        map_queries.pop_back();

        if (map_query.level == 7) {
            results.emplace_back(map_query.range);
            continue;
        }

        bool mapping_found = false;
        for (const Mapping& mapping : mappings.at(map_query.level)) {
            vector<Range> unmapped;
            Range mapped;
            mapping_found = MapSingle(mapping, map_query.range, unmapped, mapped);
            if (mapping_found) {
                for (const Range& range : unmapped) {
                    map_queries.emplace_back(range, map_query.level);
                }
                map_queries.emplace_back(mapped, map_query.level + 1);
                break;
            } else {
                continue;
            }
        }

        if (!mapping_found) {
            map_queries.emplace_back(map_query.range, map_query.level + 1);
        }
    }

    return results;
}

int main(int argc, char* argv[]) {
    fstream input("input.txt");
    string line;
    getline(input, line);
    vector<Range> seeds = ParseSeeds(line);
    getline(input, line);  // newline

    const int kMappings = 7;
    vector<vector<Mapping>> mappings;
    for (int i = 0; i < kMappings; ++i) {
        mappings.emplace_back(ParseRanges(input));
    }

    long long lowest = numeric_limits<long long>::max();
    for (const Range& seed : seeds) {
        vector<Range> mapped = Map(mappings, seed);
        for (const Range& final : mapped) {
            if (final.start < lowest) {
                lowest = final.start;
            }
        }
    }

    cout << "Lowest: " << lowest << endl;
    return 0;
}
