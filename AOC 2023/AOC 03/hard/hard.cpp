#include "AOC.h"

using namespace std;

int main()
{
    TextFile f("../../AOC 03/data/hard.txt");
    CharacterMatrix m(f);

    int sum = 0;
    int ratios = 0;

    struct NR
    {
        int nr = -1;
        int x1 = -1;
        int x2 = -1;
    };
    Grid<NR> nrs;

    auto AddNR = [&](const int x1, const int x2, const int y)
    {
        for (int yy = y - 1; yy < y + 2; ++yy)
        {
            for (int x = x1 - 1; x < x2 + 1; ++x)
            {
                auto c = m(x, yy);
                if (!isdigit(c) && c != ' ' && c != '.')
                {
                    return true;
                }
            }
        }
        return false;
    };

    auto StoreNR = [&](const int x1, const int x2, const int y, const int nr)
    {
        for (int i = x1; i <= x2; ++i)
        {
            nrs(y,i).nr = nr;
            nrs(y,i).x1 = x1;
            nrs(y,i).x2 = x2;
        }
    };

    for (int y = 0; y < m.Height(); ++y)
    {
        int nr = 0;
        int xs = -1;
        for (int x = 0; x < m.Width(); ++x)
        {
            auto c = m(x, y);
            if (isdigit(c))
            {
                if (xs < 0) xs = x;
                nr = 10 * nr + (c - '0');
            }
            else if (nr > 0)
            {
                if (AddNR(xs, x, y))
                {
                    sum += nr;
                }
                StoreNR(xs, x - 1, y, nr);
                xs = -1;
                nr = 0;
            }
        }
        if (nr > 0)
        {
            if (AddNR(xs, m.Width() - 1, y))
            {
                sum += nr;
            }
            StoreNR(xs, m.Width() - 1, y, nr);
        }
    }

    auto GetRatio = [&](const int x, const int y)
    {
        int r1 = -1;
        int r2 = -1;
        for (int i = y - 1; i < y + 2; ++i)
        {
            for (int j = x - 1; j < x + 2; ++j)
            {
                NR& n = nrs(i,j);
                if (n.nr >= 0)
                {
                    if (r1 == -1) r1 = n.nr;
                    else r2 = n.nr;
                    j = n.x2;
                }
            }
        }
        return r1 * r2;
    };

    for (int y = 0; y < m.Height(); ++y)
    {
        for (int x = 0; x < m.Width(); ++x)
        {
            if (m(x, y) == '*')
            {
                auto r = GetRatio(x, y);
                if (r > 0) ratios += r;
            }
        }
    }

    cout << sum << endl;
    cout << ratios << endl;
    return 0;
}

