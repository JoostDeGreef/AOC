#include "AOC.h"

using namespace std;

enum Source
{
    None = 0,
    N = 1,
    S = 2,
    W = 4,
    E = 8
};

enum Lens
{
    Empty = 0,
    NS = 1,
    WE = 2,
    NWSE = 4,
    NESW = 8
};

struct Tile
{
    Lens lens = Empty;
    int active = 0;
    int source = None;
};

int main()
{
    ThreadPool pool;
    //TextFile f("../../AOC 16/data/test.txt");
    TextFile f("../../AOC 16/data/simple.txt");
    cout << f << endl;

    auto& lines = f.GetLines();
    Grid<Tile> tiles;
    for (I y = 0; y < lines.size(); ++y)
    {
        const string& line = lines[(size_t)y];
        for (I x = 0; x < line.size(); ++x)
        {
            Tile& tile = tiles(x, y);
            char c = line[(size_t)x];
            switch (c)
            {
            case '.':
                break;
            case '|':
                tile.lens = NS;
                break;
            case '-':
                tile.lens = WE;
                break;
            case '\\':
                tile.lens = NWSE;
                break;
            case '/':
                tile.lens = NESW;
                break;
            default:
                break;
            }
        }
    }

    map<Pos, int> sources;
    map<Pos, int> new_sources;

    auto AddSrc = [&](I x, I y, Source src)
    {
        Pos p(x, y);
        auto iter = sources.find(p);
        if (iter == sources.end())
        {
            new_sources[p] |= src;
        }
        else
        {
            auto& s = iter->second;
            if ((s & src) == 0)
            {
                new_sources[p] |= src;
            }
        }
    };

    auto AddBeam = [&](I x, I y, Source src)
    {
        I dx = 0, dy = 0;
        switch (src)
        {
        case N: dy = -1; break;
        case S: dy = 1; break;
        case W: dx = -1; break;
        case E: dx = 1; break;
        }
        x += dx;
        y += dy;
        while (tiles.Inside(x, y))
        {
            auto& tile = tiles(x, y);
            tile.active++;
            switch (tile.lens)
            {
            case Empty:
                x += dx;
                y += dy;
                break;
            case NS:
                if (dx)
                {
                    AddSrc(x, y, N);
                    AddSrc(x, y, S);
                    x = -1;
                }
                else
                {
                    y += dy;
                }
                break;
            case WE:
                if (dy)
                {
                    AddSrc(x, y, W);
                    AddSrc(x, y, E);
                    x = -1;
                }
                else
                {
                    x += dx;
                }
                break;
            case NWSE:
                switch (src)
                {
                case N: AddSrc(x, y, W); break;
                case S: AddSrc(x, y, E); break;
                case W: AddSrc(x, y, N); break;
                case E: AddSrc(x, y, S); break;
                }
                x = -1;
                break;
            case NESW:
                switch (src)
                {
                case N: AddSrc(x, y, E); break;
                case S: AddSrc(x, y, W); break;
                case W: AddSrc(x, y, S); break;
                case E: AddSrc(x, y, N); break;
                }
                x = -1;
                break;
            }
        }
    };

    auto DrawTiles = [&]()
    {
        for (I y = 0; y < tiles.Height(); ++y)
        {
            for (I x = 0; x < tiles.Width(); ++x)
            {
                cout << (tiles(x, y).active ? '#' : '.');
            }
            cout << endl;
        }
    };

    AddSrc(-1, 0, E);

    while (!new_sources.empty())
    {
        map<Pos, int> temp;
        swap(temp, new_sources);

        for (auto& key : temp)
        {
            const Pos& p = key.first;
            int src = key.second;
            if (src & N) AddBeam(p.x, p.y, N);
            if (src & S) AddBeam(p.x, p.y, S);
            if (src & W) AddBeam(p.x, p.y, W);
            if (src & E) AddBeam(p.x, p.y, E);

            sources[p] |= src;
        }

    }

    DrawTiles();

    I energized = 0;
    for (I y = 0; y < tiles.Height(); ++y)
    {
        for (I x = 0; x < tiles.Height(); ++x)
        {
            if (tiles(x, y).active)
            {
                energized++;
            }
        }
    }

    cout << energized << endl;

    return 0;
}

