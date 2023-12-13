#include "AOC.h"

using namespace std;

size_t FindMirror(const CharacterMatrix& m)
{
    for (size_t i = 1; i < m.Height(); ++i)
    {
        int smudges = 0;
        for (size_t j = 0; j < i && i + j < m.Height() && smudges<2; ++j)
        {
            auto& l0 = m.GetLine(i - j - 1);
            auto& l1 = m.GetLine(i + j);
            for (size_t k = 0; k < l0.size() && smudges < 2; ++k)
            {
                if (l0[k] != l1[k]) smudges++;
            }
        }
        if (smudges == 1) return i;
    }
    return 0;
}

int main()
{
    TextFile f("../../AOC 13/data/simple.txt");

    vector<CharacterMatrix> blocks;
    blocks.emplace_back();

    for (const auto line : f.GetLines())
    {
        if (line.Empty())
        {
            if (!blocks.back().Empty()) blocks.emplace_back();
        }
        else
        {
            blocks.back().AddLine(line);
        }
    }

    vector<size_t> vert;
    vector<size_t> horz;

    for (const auto& block : blocks)
    {
        vert.emplace_back(FindMirror(block));
        horz.emplace_back(FindMirror(block.Transposed()));
    }

    size_t res = 0;
    for (size_t i = 0; i < vert.size(); ++i)
    {
        res += 100 * vert[i] + horz[i];
    }

    cout << res << endl;

    return 0;
}

