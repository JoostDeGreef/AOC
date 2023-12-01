#include "AOC.h"

using namespace std;

int main()
{
    auto replace = [](const std::string s, std::string s1, std::string s2)
    {
        return std::regex_replace(s, std::regex(s1), s2);
    };

    TextFile f("../../AOC 01/data/hard.txt");
    std::vector<std::vector<int>> values;
    for (const auto l : f.GetLines())
    {
        values.push_back({});
        std::string s = l;

        s = replace(s, "one", "o1e");
        s = replace(s, "two", "t2o");
        s = replace(s, "three", "th3ee");
        s = replace(s, "four", "f4ur");
        s = replace(s, "five", "f5ve");
        s = replace(s, "six", "s6x");
        s = replace(s, "seven", "se7en");
        s = replace(s, "eight", "ei8ht");
        s = replace(s, "nine", "n9ne");

        for (const auto c : s)
        {
            if (isdigit(c))
            {
                values.back().push_back(c - '0');
                cout << c;
            }
        }
        cout << endl;
    }
    int sum = 0;
    for (const auto v : values)
    {
        if (!v.empty())
        {
            int i = v.front() * 10 + v.back();
            sum += i;
        }
    }
    cout << "sum = " << sum << endl;
    return 0;
}

