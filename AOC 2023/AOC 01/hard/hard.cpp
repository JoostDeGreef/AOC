#include "AOC.h"

using namespace std;

int main()
{
    TextFile f("../../AOC 01/data/hard.txt");
    std::vector<std::vector<int>> values;
    for (auto l : f.GetLines())
    {
        values.push_back({});
        l.Replace("one", "o1e")
         .Replace("two", "t2o")
         .Replace("three", "th3ee")
         .Replace("four", "f4ur")
         .Replace("five", "f5ve")
         .Replace("six", "s6x")
         .Replace("seven", "se7en")
         .Replace("eight", "ei8ht")
         .Replace("nine", "n9ne");

        for (const auto c : l)
        {
            if (isdigit(c))
            {
                values.back().push_back(c - '0');
            }
        }
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
    cout << "sum = " << sum << " (answered 54845)" << endl;
    return 0;
}

