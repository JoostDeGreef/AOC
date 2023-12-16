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

void CoutGrid(Grid<char>& g)
{
    for (int i = 0; i < g.Height(); ++i)
    {
        for (int j = 0; j < g.Width(); ++j)
        {
            cout << g(j, i);
        }
        cout << endl;
    }
    cout << "------" << endl;
}

string ShiftLine(string s)
{
    bool changed = true;
    while (changed)
    {
        changed = false;
        for (size_t i = 0; i < s.size() - 1; ++i)
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

void Job1()
{
    TextFile f("../../AOC 14/data/test.txt");
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
}

class Data
{
public:
    Data(Grid<char> * g, I i)
        : g(g)
        , i(i)
    {}

    Grid<char> * g;
    I i;
};

int ShiftNorth(const Data &data)
{
    bool changed = true;
    Grid<char> & g = *data.g;
    while (changed)
    {
        changed = false;

        for (I j = 1; j < g.Height(); ++j)
        {
            auto& c0 = g(data.i, j - 1);
            auto& c1 = g(data.i, j);
            if (c0 == '.' && c1 == 'O')
            {
                swap(c0, c1);
                changed = true;
            }
        }
    }
    return 0;
}
int ShiftSouth(const Data& data)
{
    bool changed = true;
    Grid<char>& g = *data.g;
    I h = g.Height();
    while (changed)
    {
        changed = false;

        for (I j = 1; j < h; ++j)
        {
            auto& c0 = g(data.i, h - j);
            auto& c1 = g(data.i, h - j - 1);
            if (c0 == '.' && c1 == 'O')
            {
                swap(c0, c1);
                changed = true;
            }
        }
    }
    return 0;
}
int ShiftWest(const Data& data)
{
    bool changed = true;
    Grid<char>& g = *data.g;
    while (changed)
    {
        changed = false;

        for (I j = 1; j < g.Width(); ++j)
        {
            auto& c0 = g(j - 1, data.i);
            auto& c1 = g(j, data.i);
            if (c0 == '.' && c1 == 'O')
            {
                swap(c0, c1);
                changed = true;
            }
        }
    }
    return 0;
}
int ShiftEast(const Data& data)
{
    bool changed = true;
    Grid<char>& g = *data.g;
    I w = g.Width();
    while (changed)
    {
        changed = false;

        for (I j = 1; j < w; ++j)
        {
            auto& c0 = g(w - j, data.i);
            auto& c1 = g(w - j - 1, data.i);
            if (c0 == '.' && c1 == 'O')
            {
                swap(c0, c1);
                changed = true;
            }
        }
    }
    return 0;
}

I CountColumn(const Data& data)
{
    I res = 0;
    Grid<char>& g = *data.g;
    I j = g.Height();
    for (I i = 0; i < g.Height(); ++i, --j)
    {
        auto& c = g(data.i, i);
        if (c == 'O') res += j;
    }
    return res;
}

void Job2()
{
    //TextFile f("../../AOC 14/data/test.txt");
    TextFile f("../../AOC 14/data/simple.txt");
    Grid<char> g('.');
    const auto& lines = f.GetLines();
    for (size_t y = 0; y < lines.size(); ++y)
    {
        const string line = lines[y];
        for (size_t x = 0; x < line.size(); ++x)
        {
            g(x, y) = line[x];
        }
    }
    vector<Data> columns;
    vector<Data> rows;
    for (int i = 0; i < g.Width(); ++i)
    {
        columns.emplace_back(&g, i);
    }
    for (int i = 0; i < g.Height(); ++i)
    {
        rows.emplace_back(&g, i);
    }

    CoutGrid(g);

    ThreadPool p;
    vector<I> counts;
    for (I i = 0; i < 500; ++i)
    {
        p.ForAll(columns, ShiftNorth);
        p.ForAll(rows, ShiftWest);
        p.ForAll(columns, ShiftSouth);
        p.ForAll(rows, ShiftEast);
        auto count = AOC::Sum(p.ForAll(columns, CountColumn));
        cout << i << " : " << count << endl;
        counts.push_back(count);
    }
    I repeat = -1;
    for (I i = 200; i < 400 && repeat < 0; ++i)
    {
        repeat = i-199;
        for (I j = 0; j < 50; ++j)
        {
            if (counts[199+j]!=counts[i+j])
            {
                repeat = -1;
                break;
            }
        }
    }
    cout << "repeats every " << repeat << " cycles" << endl;
    I index = (1000000000 - 500) % repeat;

    cout << (counts[counts.size()-1-2*repeat+index]) << endl;

}

int main()
{
    //Job1();
    Job2();

    return 0;
}

