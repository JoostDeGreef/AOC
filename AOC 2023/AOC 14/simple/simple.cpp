#include "AOC.h"

using namespace std;

template<typename T>
void CoutLines(vector<T>& lines)
{
    for (auto& l : lines)
    {
        cout << l << endl;
    }
    cout << "------" << endl;
}


string ShiftLine(string s)
{
    bool changed = true;
    while (changed)
    {
        changed = false;
        for (int i = 0; i < s.size() - 1; ++i)
        {
            if (s[i] == '.' && s[i + 1] == 'O')
            {
                swap(s[i], s[i + 1]);
                changed = true;
            }
        }
    }
    return s;
}

I CountLine(const string& s)
{
    I res = 0;
    size_t j = s.size();
    for (size_t i = 0; i < s.size(); ++i, --j)
    {
        if (s[i] == 'O') res += j;
    }
    return res;
}

int main()
{
    TextFile f("../../AOC 14/data/simple.txt");
    CharacterMatrix m(f);

    CoutLines(m.GetLines());

    auto transposed = m.Transposed();
    auto& lines = transposed.GetLines();
    lines = AOC::ForAll(lines, ShiftLine);

    m = transposed.Transposed();
    CoutLines(m.GetLines());

    auto counts = AOC::ForAll(lines, CountLine);
    auto count = AOC::Sum(counts);

    cout << count << endl;

    return 0;
}

