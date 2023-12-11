#include "AOC.h"

using namespace std;
using namespace AOC;

void DuplicateEmptyLines(const CharacterMatrix& m, std::vector<Pos> & ps,int64_t dist)
{
    for (int i = m.Height() - 1; i >= 0; --i)
    {
        const string& s = m.GetLine(i);
        size_t l = s.find_first_not_of(". ", 0);
        if (l == std::string::npos)
        {
            for (auto& p : ps)
            {
                if (p.y > i) p.y += dist-1;
            }
        }
    }
}

std::vector<Pos> FindGalaxies(CharacterMatrix& m)
{
    std::vector<Pos> res;

    for (int h = 0; h < m.Height(); ++h)
    {
        for (int w = 0; w < m.Width(); ++w)
        {
            if (m(w, h) != '.') res.emplace_back(w, h);
        }
    }

    return res;
}

void TransposePositions(std::vector<Pos>& ps)
{
    for (auto& p : ps)
    {
        swap(p.x,p.y);
    }
}

int main()
{
    //TextFile f("../../AOC 11/data/test.txt");
    TextFile f("../../AOC 11/data/simple.txt");
    CharacterMatrix m(f);

    auto galaxies = FindGalaxies(m);
    auto galaxies0 = galaxies;

    DuplicateEmptyLines(m,galaxies, 1000000);
    m = m.Transposed();
    TransposePositions(galaxies);
    DuplicateEmptyLines(m,galaxies, 1000000);
    TransposePositions(galaxies);

    int64_t sum = 0;
    int count = 0;

    auto BlockDistance = [](const Pos& p0, const Pos& p1)
    {
        int64_t res = abs(p1.x - p0.x) + abs(p1.y - p0.y);
        return res;
    };

    for (size_t i = 0; i < galaxies.size(); ++i)
    {
        for (size_t j = i + 1; j < galaxies.size(); ++j)
        {
            count++;
            sum += BlockDistance(galaxies[i], galaxies[j]);
        }
    }

    cout << count << endl;
    cout << sum << endl;

    return 0;
}

