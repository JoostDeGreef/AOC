#include "AOC.h"

using namespace std;

int main()
{
    TextFile f("../../AOC 05/data/simple.txt");

    struct Range
    {
        int64_t range;
        int64_t src;
        int64_t dest;
    };
    struct Map
    {
        string name;
        vector<Range> ranges;
    };
    vector<int64_t> seeds;
    vector<Map> maps;
    Map* map = nullptr;
    vector<int64_t> locations;

    int state = 0;
    for (const auto& l : f.GetLines())
    {
        switch (state)
        {
        case 0:
        {
            const auto words = l.GetWords();
            for (size_t i = 1; i < words.size(); ++i)
            {
                seeds.push_back(strtoll(words[i].c_str(), nullptr, 10));
            }
            state++;
        }
        break;
        case 1:
            if (!l.Empty())
            {
                if (!map)
                {
                    auto name = l.GetWords()[0];
                    maps.push_back({ name,{} });
                    map = &maps.back();
                }
                else
                {
                    const auto words = l.GetWords();
                    int64_t dest = strtoll(words[0].c_str(), nullptr, 10);
                    int64_t src = strtoll(words[1].c_str(), nullptr, 10);
                    int64_t range = strtoll(words[2].c_str(), nullptr, 10);
                    map->ranges.push_back({range,src,dest});
                }
            }
            else
            {
                map = nullptr;
            }
            break;
        }
    }

    int64_t best_location = numeric_limits<int64_t>::max();
    for (int64_t seed : seeds)
    {
        int64_t location = seed;
        for (const auto& map : maps)
        {
            for (const auto& range : map.ranges)
            {
                if (location >= range.src && location < range.src + range.range)
                {
                    location += range.dest - range.src;
                    break;
                }
            }
        }
        locations.push_back(location);
        best_location = min(best_location, location);
    }

    cout << best_location << " (answered 1181555926)" << endl;
    return 0;
}

