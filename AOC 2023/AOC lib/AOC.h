#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

namespace AOC
{
    template<typename SEQUENCE>
    SEQUENCE Reverse(const SEQUENCE& sequence)
    {
        SEQUENCE res = { sequence.rbegin(),sequence.rend() };
        return res;
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

