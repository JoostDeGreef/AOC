#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <regex>

namespace AOC
{
    template<typename T> T Reverse(T t)
    {
        return { t.rbegin(),t.rend() };
    }

    template<typename T> T Sort(T t)
    {
        std::sort(t.begin(), t.end());
        return t;
    }

    inline std::vector<std::string> CaseInsensitiveSort(std::vector<std::string> v)
    {
        std::sort(v.begin(), v.end(), [](const std::string& str1, const std::string& str2)
            {
                return lexicographical_compare(
                    begin(str1), end(str1),
                    begin(str2), end(str2),
                    [](const char& char1, const char& char2)
                    {
                        return tolower(char1) < tolower(char2);
                    });
            });
        return v;
    }
}

class Line
{
public:
    friend std::istream& operator>>(std::istream& is, Line& line);
    friend std::ostream& operator<<(std::ostream& os, const Line& line);

    operator std::string() const { return line; }

    const std::vector<std::string> GetWords() const;
private:
    std::string line;
};

class TextFile
{
public:
    TextFile(const std::string & filename);

    friend std::ostream& operator << (std::ostream& os, const TextFile& file);

    const size_t Count() const;
    const std::vector<Line> & GetLines() const;
private: 
    std::vector<Line> lines;
};

class CharacterMatrix
{
public:
    CharacterMatrix(const TextFile& file, const int startLine, const int lineCount);

    friend std::ostream& operator << (std::ostream& os, const CharacterMatrix& cm);

    const char GetChar(const int x, const int y) const;
private:
    std::vector<std::string> lines;
};

