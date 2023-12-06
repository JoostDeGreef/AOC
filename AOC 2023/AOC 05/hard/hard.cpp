#include "AOC.h"

using namespace std;

struct Seed
{
    int64_t src;
    int64_t range;
};
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
vector<Seed> seeds;
vector<Map> maps;

int64_t loc(int m, int64_t ss, int64_t se)
{
    cout << m << "," << ss << "," << se << endl;
    if (m >= maps.size())
    {
        return ss;
    }
    else
    {
        const auto& map = maps[m];
        for (const auto& range : map.ranges)
        {
            auto rs = range.src;
            auto re = range.src + range.range - 1;

            if (rs > ss && rs < se)
            {
                return min(loc(m, ss, rs - 1), loc(m, rs, se));
            }
            else if (re > ss && re < se)
            {
                return min(loc(m, ss, re - 1), loc(m, re, se));
            }
            else if (ss >= rs && se <= re)
            {
                int64_t shift = range.dest-range.src;
                return loc(m + 1, ss + shift, se + shift);
            }
        }

        return loc(m + 1, ss, se);
    }
};

int main()
{
    TextFile f("../../AOC 05/data/hard.txt");
    //TextFile f("../../AOC 05/data/test.txt");

    Map* map = nullptr;

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
                seeds.push_back({ strtoll(words[i].c_str(), nullptr, 10), strtoll(words[++i].c_str(), nullptr, 10) });
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
                    map->ranges.push_back({ range,src,dest });
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
    for (Seed& seed : seeds)
    {
        auto ss = seed.src;
        auto se = seed.src + seed.range - 1;
        best_location = min(best_location, loc(0,ss,se));
    }

    cout << best_location << " (answered 37806486)" << endl;
    return 0;
}

