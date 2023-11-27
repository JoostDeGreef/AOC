
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

const vector<string> Line::GetWords() const
{
    istringstream ss(line);

    string word;
    std::vector<std::string> words;

    while (ss >> word)
    {
        words.push_back(word);
    }

    return words;
}

