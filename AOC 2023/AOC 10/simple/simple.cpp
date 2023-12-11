#include "AOC.h"

using namespace std;
using namespace AOC;

enum Exits
{
    None = 0,
    North = 1,
    South = 2,
    East = 4,
    West = 8,
    Start = 16
};

struct Section;
typedef Grid<Section> Map;

struct Section
{
    Pos pos;
    int exits = None;
    int64_t distance = -1;
    int connections = -1;

private:
    bool NeighborHasExit(Map& m, int x, int y, Exits dir) const
    {
        if (m.Inside(x, y))
        {
            return (m(x, y).exits & (Start + dir));
        }
        return false;
    }

public:
    bool HasEast(Map& m, int x, int y) const
    {
        return (exits & (Start + East)) && NeighborHasExit(m, x + 1, y, West);
    };
    bool HasWest(Map& m, int x, int y) const
    {
        return (exits & (Start + West)) && NeighborHasExit(m, x - 1, y, East);
    };
    bool HasNorth(Map& m, int x, int y) const
    {
        return (exits & (Start + North)) && NeighborHasExit(m, x, y - 1, South);
    };
    bool HasSouth(Map& m, int x, int y) const
    {
        return (exits & (Start + South)) && NeighborHasExit(m, x, y + 1, North);
    };
};

void ParseMap(const CharacterMatrix& m, Map& map, Pos& start)
{
    //| is a vertical pipe connecting north and south.
    //- is a horizontal pipe connecting east and west.
    //L is a 90 - degree bend connecting north and east.
    //J is a 90 - degree bend connecting north and west.
    //7 is a 90 - degree bend connecting south and west.
    //F is a 90 - degree bend connecting south and east.
    //.is ground; there is no pipe in this tile.
    //S is the starting position of the animal; there is a pipe on this tile, but your sketch doesn't show what shape the pipe has.
    for (int h = 0; h < m.Height(); ++h)
    {
        for (int w = 0; w < m.Width(); ++w)
        {
            Section& s = map(w, h);
            s.pos = Pos{ w,h };
            switch (char c = m(w, h))
            {
            case '|': s.exits = North + South; break;
            case '-': s.exits = East + West; break;
            case 'L': s.exits = North + East; break;
            case 'J': s.exits = North + West; break;
            case '7': s.exits = South + West; break;
            case 'F': s.exits = South + East; break;
            case '.': s.exits = None; break;
            case 'S': s.exits = Start; start = s.pos; s.distance = 0; break;
            default:
                cout << "Unhandled character " + c << endl;
                exit(1);
                break;
            }
        }
    }

    for (int h = 0; h < m.Height(); ++h)
    {
        for (int w = 0; w < m.Width(); ++w)
        {
            Section& s = map(w, h);
            s.connections = (s.HasEast(map, w, h) ? 1 : 0)
                + (s.HasWest(map, w, h) ? 1 : 0)
                + (s.HasNorth(map, w, h) ? 1 : 0)
                + (s.HasSouth(map, w, h) ? 1 : 0);
            cout << s.connections;
        }
        cout << endl;
    }
    cout << endl;

    set<Pos> todo;
    
    auto AddPos = [&](set<Pos>& ps, const Pos p)
    {
        if (map.Inside(p.x - 1, p.y)) ps.emplace(p.x - 1, p.y);
        if (map.Inside(p.x + 1, p.y)) ps.emplace(p.x + 1, p.y);
        if (map.Inside(p.x, p.y - 1)) ps.emplace(p.x, p.y - 1);
        if (map.Inside(p.x, p.y + 1)) ps.emplace(p.x, p.y + 1);
    };
    AddPos(todo, start);

    bool changed = true;
    while (changed)
    {
        changed = false;
        set<Pos> temp;
        swap(temp, todo);
        for(auto p: temp)
        {
            int w = p.x;
            int h = p.y;
            Section& s = map(w,h);
            auto SetDist = [&](int x, int y)
            {
                Section& o = map(x, y);
                if (o.distance >= 0 && (o.distance + 1 < s.distance || s.distance < 0))
                {
                    s.distance = o.distance + 1;
                    changed = true;
                    AddPos(todo, p);
                }
            };
            if (s.connections == 2)
            {
                if (s.HasEast(map, w, h)) SetDist(w + 1, h);
                if (s.HasWest(map, w, h)) SetDist(w - 1, h);
                if (s.HasNorth(map, w, h)) SetDist(w, h - 1);
                if (s.HasSouth(map, w, h)) SetDist(w, h + 1);
            }
        }
    }
}

int main()
{
//    TextFile f("../../AOC 10/data/test.txt");
    TextFile f("../../AOC 10/data/simple.txt");
    CharacterMatrix m(f);

    Grid<Section> map;
    Pos start;
    ParseMap(m, map, start);

    int64_t dist = 0;
    for (int h = 0; h < m.Height(); ++h)
    {
        for (int w = 0; w < m.Width(); ++w)
        {
            Section& s = map(w, h);
            dist = max(dist, s.distance);
        }
    }

    cout << dist << endl;

    return 0;
}

