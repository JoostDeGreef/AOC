#include "AOC.h"

using namespace std;

int main()
{
    TextFile f("../../AOC 05/data/test.txt");

    vector<int> seeds;
    unordered_map<std::string, unordered_map<int, int>> maps;
    vector<string> names;
    unordered_map<int, int>* map = nullptr;
    vector<int> locations;

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
                    seeds.push_back(strtol(words[i].c_str(), nullptr, 10));
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
                    map = &maps[name];
                    names.push_back(name);
                }
                else
                {
                    const auto words = l.GetWords();
                    int dest = strtol(words[0].c_str(), nullptr, 10);
                    int src = strtol(words[1].c_str(), nullptr, 10);
                    int range = strtol(words[2].c_str(), nullptr, 10);
                    for (int i = 0; i < range; ++i)
                    {
                        (*map)[src + i] = dest + i;
                    }
                }
            }
            else
            {
                map = nullptr;
            }
            break;
        }
    }

    int best_location = 1000000;
    for (int seed : seeds)
    {
        int location = seed;
        for (const auto & name : names)
        {
            auto i1 = maps.find(name);
            if (i1 == maps.end())
            {
                cout << name << " not found!\n";
                return 1;
            }
            auto& m = i1->second;
            auto i2 = m.find(location);
            if (i2 != m.end())
            {
                location = i2->second;
            }
        }
        locations.push_back(location);
        best_location = min(best_location, location);
    }

    cout << best_location << " (should be 35)" << endl;
    return 0;
}

