
#include "AOC.h"

using namespace std;

CharacterMatrix::CharacterMatrix(const TextFile& file, const char def)
    : def(def)
{
    auto l = file.GetLines();
    lines = { l.begin(),l.end() };
    CalcSize();
}
CharacterMatrix::CharacterMatrix(const TextFile& file, const int startLine, const int lineCount, const char def)
    : def(def)
{
    auto l = file.GetLines();
    lines = { l.begin() + startLine,l.begin() + startLine + lineCount };
    CalcSize();
}
void CharacterMatrix::CalcSize()
{
    width = 0;
    height = 0;
    for (const auto& l : lines)
    {
        if (!l.empty())
        {
            width = std::max(width, (int)l.size());
            height++;
        }
    }
}

ostream& operator << (std::ostream& os, const CharacterMatrix& cm)
{
    for (const auto& line : cm.lines)
    {
        os << line << endl;
    }
    return os;
}

const char CharacterMatrix::GetChar(const int x, const int y) const
{
    if (x < 0 || y < 0) return def;
    if (y >= (int)lines.size() || x >= (int)(lines[y].size())) return def;
    return lines.at(y).at(x);
}

