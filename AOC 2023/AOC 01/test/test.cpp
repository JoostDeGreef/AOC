#include "AOC.h"

using namespace std;

int main()
{
    TextFile f("../../AOC 01/data/test.txt");
    std::vector<std::vector<int>> values;
    for (const auto l : f.GetLines())
    {
        cout << l << endl;
        values.push_back({});
        for (const auto c : (std::string)l)
        {
            if (isdigit(c))
            {
                values.back().push_back(c-'0');
            }
        }
    }
    int sum = 0;
    for (const auto v : values)
    {
        if (!v.empty())
        {
            int i = v.front()*10 + v.back();
            cout << i << endl;
            sum += i;
        }
    }
    cout << "sum = " << sum << "  (should be 142)" << endl;
    return 0;
}

