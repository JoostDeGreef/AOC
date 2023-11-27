
#include "AOC.h"

using namespace std;

TextFile::TextFile(const string& filename)
{
    ifstream file(filename);

    if (!file.good())
    {
        throw runtime_error("Could not open \"" + filename + "\"");
    }
    else
    {
        lines = {istream_iterator<Line>(file), istream_iterator<Line>() };
    }
}

ostream& operator<<(ostream& os, const TextFile& file)
{
    for (const auto& line : file.lines)
    {
        os << line << endl;
    }
    return os;
}

const vector<Line>& TextFile::GetLines() const
{
    return lines;
}

const size_t TextFile::Count() const
{
    return lines.size();
}

