
#include "AOC.h"

using namespace std;

CharacterMatrix::CharacterMatrix(const TextFile& file, const int startLine, const int lineCount)
{
    auto l = file.GetLines();
    lines = { l.begin() + startLine,l.begin() + startLine + lineCount };
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
    return lines.at(y).at(x);
}

