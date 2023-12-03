#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <regex>
#include <numeric>
#include <unordered_map>

namespace AOC
{
    template<typename T> T Sum(const std::vector<T>& v)
    {
        return accumulate(v.begin(), v.end(), (T)0);
    }

    template<typename T> T Reverse(T t)
    {
        return { t.rbegin(),t.rend() };
    }

    template<typename T> T Sort(T t)
    {
        std::sort(t.begin(), t.end());
        return t;
    }

    inline std::string Replace(const std::string s, std::string s1, std::string s2)
    {
        return std::regex_replace(s, std::regex(s1), s2);
    };

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
    Line() {}
    Line(const std::string& s) { line = s; }

    explicit Line(const Line& l) { line = l.line; }

    friend std::istream& operator>>(std::istream& is, Line& line);
    friend std::ostream& operator<<(std::ostream& os, const Line& line);

    Line operator = (const std::string& s) { line = s; return *this; }
    operator std::string() const { return line; }

    Line Replaced(const std::string& key, const std::string& value) const;
    Line & Replace(const std::string& key, const std::string& value);

    auto begin() { return line.begin(); }
    auto end() { return line.end(); }
    auto cbegin() const { return line.cbegin(); }
    auto cend() const { return line.cend(); }

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
    CharacterMatrix(const TextFile& file, const char def = ' ');
    CharacterMatrix(const TextFile& file, const int startLine, const int lineCount, const char def = ' ');

    friend std::ostream& operator << (std::ostream& os, const CharacterMatrix& cm);

    int Width() const { return width; }
    int Height() const { return height; }

    char operator () (const int x, const int y) const { return GetChar(x, y); }
    const char GetChar(const int x, const int y) const;
private:
    void CalcSize();

    std::vector<std::string> lines;
    int width;
    int height;
    char def;
};

template<typename T>
class Grid
{
public:
    Grid(const T def = T())
        : def(def)
        , width(0)
        , height(0)
    {}

    T & operator () (const int x, const int y)
    { 
        if (x >= width) width = x + 1;
        if (y >= height) height = y + 1;
        auto itery = data.find(y);
        if (itery == data.end())
        {
            itery = data.emplace(y, std::unordered_map<int, T>{}).first;
        }
        auto iterx = itery->second.find(x);
        if (iterx == itery->second.end())
        {
            iterx = itery->second.emplace(x,def).first;
        }
        return iterx->second;
    }

    int Width() const { return width; }
    int Height() const { return height; }
private:
    std::unordered_map<int,std::unordered_map<int,T>> data;
    const T def;
    int width;
    int height;
};
