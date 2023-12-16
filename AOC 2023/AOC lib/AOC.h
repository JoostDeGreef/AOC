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
#include <unordered_set>
#include <limits>
#include <map>
#include <set>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <functional>
#include <future>

namespace AOC
{
    template<typename T>
    T Sum(const std::vector<T>& v)
    {
        return accumulate(v.begin(), v.end(), (T)0);
    }

    template<typename T>
    T Max(const std::vector<T>& v)
    {
        T res(0);
        for (const auto& a : v)
        {
            res = std::max(res, a);
        }
        return res;
    }

    template<typename T>
    T Reverse(T t)
    {
        return { t.rbegin(),t.rend() };
    }

    template<typename T>
    T Sort(T t)
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

using I = int_fast64_t;
using U = uint_fast64_t;

struct Pos
{
    Pos(I x, I y)
        : x(x)
        , y(y)
    {}
    Pos()
        : Pos(-1, -1)
    {}
    ~Pos() = default;
    Pos(const Pos& p)
        : Pos(p.x, p.y)
    {}
    Pos& operator=(const Pos& p)
    {
        x = p.x;
        y = p.y;
        return *this;
    }
    Pos(Pos&&p) noexcept
    {
        std::swap(p.x, x);
        std::swap(p.y, y);
    }
    Pos& operator=(Pos&&p) noexcept
    {
        std::swap(p.x, x);
        std::swap(p.y, y);
        return *this;
    }

    I x = -1;
    I y = -1;

    bool operator < (const Pos& p) const
    {
        return y < p.y || (y == p.y && x < p.x);
    }
    bool operator == (const Pos& p) const
    {
        return y == p.y && x == p.x;
    }

    friend std::ostream& operator << (std::ostream& os, const Pos &p);
};

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

    bool Empty() const { return line.empty(); }

    const std::vector<std::string> GetWords(const char separator = ' ') const;
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
    CharacterMatrix(const char def = ' ');
    CharacterMatrix(const TextFile& file, const char def = ' ');
    CharacterMatrix(const TextFile& file, const int startLine, const int lineCount, const char def = ' ');

    friend std::ostream& operator << (std::ostream& os, const CharacterMatrix& cm);

    size_t Width() const { return width; }
    size_t Height() const { return height; }

    char operator () (const int x, const int y) const { return GetChar(x, y); }
    const char GetChar(const int x, const int y) const;

    std::string& GetLine(const size_t y) { return lines.at(y); }
    std::vector<std::string>& GetLines() { return lines; }
    void InsertLine(const size_t y, const std::string& s) { lines.insert(lines.begin() + y, s); height++; width = std::max(width, s.size()); }
    void AddLine(const std::string& s) { lines.push_back(s); height++; width = std::max(width, s.size()); }
    bool Empty() const { return lines.empty(); }

    CharacterMatrix Transposed() const;
private:
    void CalcSize();

    std::vector<std::string> lines;
    size_t width;
    size_t height;
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
    Grid(Grid<T> &g)
        : def(g.def)
        , width(g.width)
        , height(g.height)
        , data(g.data)
    {}

    const T & operator () (const I x, const I y) const
    { 
        Pos p(x, y);
        auto iter = data.find(p);
        if (iter == data.end())
        {
            return def;
        }
        return def;
    }
    T& operator () (const I x, const I y)
    {
        Pos p(x, y);
        return (*this)[p];
    }

    T& operator [] (const Pos & p)
    {
        if (p.x >= width) width = p.x + 1;
        if (p.y >= height) height = p.y + 1;
        auto iter = data.find(p);
        if (iter == data.end())
        {
            iter = data.emplace(p, def).first;
        }
        return iter->second;
    }

    bool Inside(const I x, const I y) const
    {
        return (x >= 0) && (x < width) && (y >= 0) && (y < height);
    }
    I Width() const { return width; }
    I Height() const { return height; }
private:
    struct PosHasher
    {
        std::size_t operator()(const Pos& p) const
        {
            const size_t x = (size_t)p.x;
            const size_t y = (size_t)p.y;
            const size_t m = sizeof(x)*4;
            return ((x >> m) | (x << m)) ^ y;
        }
    };
    std::unordered_map<Pos,T,PosHasher> data;
    T def;
    I width;
    I height;
};

class ThreadPool
{
public:
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool(ThreadPool&&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;
    ThreadPool& operator=(ThreadPool&&) = delete;
    ThreadPool(size_t n = 0)
    {
        auto thread_func = [this]()
        {
            std::function<void()> task;
            while (true)
            {
                std::unique_lock<std::mutex> lock(mtx);
                cv.wait(lock, [&]() { return terminate || !tasks.empty(); });
                if (lock.owns_lock())
                {
                    if (terminate)
                    {
                        return;
                    }
                    task = std::move(tasks.front());
                    tasks.pop();
                    lock.unlock();
                    task();
                }
            }
        };
        if (n <= 0) n = std::max(std::thread::hardware_concurrency(), (unsigned int)1);
        if (n > 1)
        {
            for (std::size_t i = 0; i < n; ++i)
            {
                threads.emplace_back(thread_func);
            }
        }
    }
    ~ThreadPool()
    {
        std::unique_lock<std::mutex> lock(mtx);
        terminate = true;
        lock.unlock();
        if (!threads.empty())
        {
            cv.notify_all();
            for (auto& t : threads)
            {
                t.join();
            }
        }
    }

    template<typename TInput, typename Func, typename... CommonArgs>
    auto ForAll(const std::vector<TInput>& inputs, Func f, CommonArgs &... args)
    {
        using return_type = std::result_of_t<Func(TInput,CommonArgs &...)>;

        std::vector<return_type> results;
        results.reserve(inputs.size());

        if (threads.empty())
        {
            for (const auto& input : inputs)
            {
                results.emplace_back(f(input,args...));
            }
        }
        else
        {
            std::vector<std::future<return_type>> futures;
            futures.reserve(inputs.size());

            for (const auto& input : inputs)
            {
                auto task = std::make_shared<std::packaged_task<return_type()>>(std::bind(f, input, args...));

                std::future<return_type> res = task->get_future();
                {
                    std::unique_lock<std::mutex> lock(mtx);

                    if (terminate)
                    {
                        throw std::runtime_error("The thread pool has been stopped");
                    }

                    tasks.emplace([task]() -> void { (*task)(); });
                }
                cv.notify_one();
                futures.emplace_back(std::move(res));
            }

            for (auto& f : futures)
            {
                results.emplace_back(std::move(f.get()));
            }
        }

        return results;
    }

private:
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> tasks;
    std::mutex mtx;
    std::condition_variable cv;
    bool terminate = false;
};

namespace AOC
{
    template<typename TInput, typename Func, typename... CommonArgs>
    auto ForAll(const std::vector<TInput>& inputs, Func task, CommonArgs &... args)
    {
        return ThreadPool(0).ForAll(inputs, task, args...);
    }
}
