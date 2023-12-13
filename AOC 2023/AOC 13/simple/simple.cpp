#include "AOC.h"

using namespace std;

size_t FindMirror(const CharacterMatrix& m)
{
    for (size_t i = 1; i < m.Height(); ++i)
    {
        bool mirror = true;
        for (size_t j = 0; j < i && i + j < m.Height() && mirror; ++j)
        {
            if (m.GetLine(i - j - 1) != m.GetLine(i + j)) mirror = false;
        }
        if (mirror) return i;
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

