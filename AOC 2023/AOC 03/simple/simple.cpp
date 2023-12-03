#include "AOC.h"

using namespace std;

int main()
{
    TextFile f("../../AOC 03/data/simple.txt");
    CharacterMatrix m(f);

    int sum = 0;

    auto AddNR = [&](const int x1, const int x2, const int y)
    {
        for (int yy = y - 1; yy < y + 2; ++yy)
        {
            for (int x = x1 - 1; x < x2 + 1; ++x)
            {
                auto c = m(x, yy);
                cout << c;
                if (!isdigit(c) && c != ' ' && c != '.') return true;
            }
        }
        return false;
    };

    for (int y = 0; y < m.Height(); ++y)
    {
        int xs = -1;
        int nr = 0;
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
                cout << nr << " : " << sum << " : ";
                if (AddNR(xs, x, y)) sum += nr;
                xs = -1;
                nr = 0;
                cout << " : " << sum << endl;
            }
        }
        if (nr > 0)
        {
            cout << nr << " : " << sum << " : ";
            if (AddNR(xs, m.Width() - 1, y)) sum += nr;
            cout << " : " << sum << endl;
        }
    }

    cout << sum << endl;
    return 0;
}

