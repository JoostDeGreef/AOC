#include "AOC.h"

using namespace std;

I CalcHash(const std::string& s)
{
    I res = 0;
    for (unsigned char c : s)
    {
        res = 17*(res+c) & 0xFF;
    }
    return res;
}

int main()
{
    TextFile f("../../AOC 15/data/test.txt");
    ThreadPool pool;

    vector<I> hashes;
    for (auto line : f.GetLines())
    {
        hashes.push_back(AOC::Sum(pool.ForAll(line.GetWords(','),CalcHash)));
    }

    auto result = AOC::Sum(hashes);

    cout << result << endl;

    return 0;
}

