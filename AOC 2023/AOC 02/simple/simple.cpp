#include "AOC.h"

using namespace std;

struct RGB
{
    int r;
    int g;
    int b;

    bool operator > (const RGB& o)
    {
        return r > o.r || b > o.b || g > o.g;
    }
};

int main()
{
    TextFile f("../../AOC 02/data/simple.txt");

    auto GetGame = [](vector<string>& line)
    {
        line.erase(line.begin());
    };
    auto GetId = [](vector<string>& line)
    {
        int id = strtol(line.front().c_str(), nullptr, 10);
        line.erase(line.begin());
        return id;
    };
    auto GetRGB = [](vector<string>& line)
    {
        RGB rgb{ 0,0,0 };
        while (!line.empty())
        {
            int count = strtol(line.front().c_str(), nullptr, 10);
            line.erase(line.begin());
            auto color = line.front();
            line.erase(line.begin());
            if (color.rfind("green", 0) == 0)
            {
                rgb.g = count;
            }
            else if (color.rfind("red", 0) == 0)
            {
                rgb.r = count;
            }
            else if (color.rfind("blue", 0) == 0)
            {
                rgb.b = count;
            }
            else
            {
                cout << "color not recognised: " << color << endl;
            }
            if (color.back() == ';')
            {
                break;
            }
        }
        return rgb;
    };

    std::vector<int> possible;
    for (const auto l : f.GetLines())
    {
        auto words = l.GetWords();
        if (!words.empty())
        {
            GetGame(words);
            int id = GetId(words);
            while (!words.empty())
            {
                auto rgb = GetRGB(words);
                if (rgb > RGB{ 12,13,14 })
                {
                    id = -1;
                    break;
                }
            }
            if (id >= 0) possible.push_back(id);
        }
    }
    int sum = AOC::Sum(possible);
    cout << sum << " (answered 2617)" << endl;
    return 0;
}

