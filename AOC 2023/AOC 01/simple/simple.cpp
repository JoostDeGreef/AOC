#include "AOC.h"

using namespace std;

int main()
{
    TextFile f("../../AOC 01/data/simple.txt");
    std::vector<std::vector<int>> values;
    for (const auto l : f.GetLines())
    {
        values.push_back({});
        for (const auto c : (std::string)l)
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
    cout << "sum = " << sum << endl;
    return 0;
}

