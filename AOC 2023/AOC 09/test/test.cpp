#include "AOC.h"

using namespace std;

typedef int64_t I;

I ProcessSequence(const vector<I> & seq)
{
    I res = 0;
    vector<I> diff;
    I maxDiff = numeric_limits<I>::min();
    I minDiff = numeric_limits<I>::max();

    for (size_t i = 1; i < seq.size(); ++i)
    {
        I d = seq[i] - seq[i - 1];
        maxDiff = max(maxDiff, d);
        minDiff = min(minDiff, d);
        diff.push_back(d);
    }

    if (maxDiff == minDiff)
    {
        return seq.back()+minDiff;
    }
    else
    {
        return seq.back() + ProcessSequence(diff);
    }
}

int main()
{
    TextFile f("../../AOC 09/data/test.txt");

    vector<I> res;
    vector<I> seq;

    for (const auto & line : f.GetLines())
    {
        seq.clear();
        if (!line.Empty())
        {
            const auto words = line.GetWords();
            for (const auto & word : words)
            {
                seq.emplace_back(strtoll(word.c_str(),nullptr,10));
            }
            I s = ProcessSequence(seq);
            res.emplace_back(s);
            cout << s << endl;
        }
    }

    I total = 0;
    for (I s : res)
    {
        total += s;
    }
    cout << "total = " << total << endl;
    return 0;
}

