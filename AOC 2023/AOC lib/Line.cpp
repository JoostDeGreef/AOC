
#include "AOC.h"

using namespace std;

istream& operator>>(istream& is, Line& line)
{
    return getline(is, line.line);
}

ostream& operator<<(ostream& os, const Line& line)
{
    return os << line.line;
}

const vector<string> Line::GetWords(const char separator) const
{
    istringstream ss(line);

    string word;
    std::vector<std::string> words;

    while (std::getline(ss, word, separator)) 
    {
        if (!word.empty())
        {
            words.push_back(word);
        }
    }

    return words;
}

Line Line::Replaced(const string& key, const string& value) const
{
    return AOC::Replace(line, key, value);
}
Line & Line::Replace(const string& key, const string& value)
{
    line = AOC::Replace(line, key, value);
    return *this;
}
