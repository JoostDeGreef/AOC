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

    int Power()
    {
        return r * g * b;
    }

    void Saturate(const RGB& o)
    {
        r = max(r, o.r);
        g = max(g, o.g);
        b = max(b, o.b);
    }
};

int main()
{
    TextFile f("../../AOC 02/data/hard.txt");

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

    std::vector<int> powers;
    for (const auto l : f.GetLines())
    {
        auto words = l.GetWords();
        RGB maxRGB{ 0,0,0 };
        if (!words.empty())
        {
            GetGame(words);
            int id = GetId(words);
            while (!words.empty())
            {
                auto rgb = GetRGB(words);
                maxRGB.Saturate(rgb);
            }
            powers.push_back(maxRGB.Power());
        }
    }
    int sum = AOC::Sum(powers);
    cout << sum << " (answered 59795)" << endl;
    return 0;
}

