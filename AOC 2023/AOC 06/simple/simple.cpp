#include "AOC.h"

using namespace std;

typedef int64_t T;
typedef int64_t D;

struct Race
{
    Race(const T t, const D d)
        : t(t)
        , d(d)
    {}
    T t;
    D d;

    pair<T, T> press;
    T possibilities;
};

D distance(T time_pressed,T total_time)
{
    return max((T)0,time_pressed * (total_time - time_pressed));
}

pair<T, T> press(T time, D dist)
{
    // take a stab at the times
    T press0 = (T)((time - sqrt(time * time - 4 * dist)) / 2);
    T press1 = (T)((time + sqrt(time * time - 4 * dist)) / 2);
    // check for correctness
    while (distance(press0, time) <= dist && press0<time) { press0++; }
    while (distance(press1, time) <= dist && press1>0) { press1--; }

    return { press0,press1 };
}

int main()
{
    TextFile f("../../AOC 06/data/simple.txt");
    //TextFile f("../../AOC 06/data/test.txt");

    std::vector<Race> races;
    const auto& lines = f.GetLines();
    auto times = lines[0].GetWords();
    auto distances = lines[1].GetWords();
    if (times.size() != distances.size() || times.size() < (size_t)(1))
    {
        cout << "error reading input" << endl;
        return 1;
    }
    for (size_t i = 1; i < times.size(); ++i)
    {
        T t = strtoll(times[i].c_str(), nullptr, 10);
        D d = strtoll(distances[i].c_str(), nullptr, 10);
        races.emplace_back( t, d );
    }

    for (auto& race : races)
    {
        race.press = press(race.t, race.d);
        race.possibilities = max((T)0,race.press.second - race.press.first + 1);
    }

    T res = 1;
    for (auto& race : races)
    {
        res *= race.possibilities;
    }

    cout << res << " (answered 138915)" << endl;

    return 0;
}

