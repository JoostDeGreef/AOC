#include "AOC.h"

using namespace std;

struct Data
{
    string input;
    vector<int> seq;
    int possibilities;
};

vector<int> GetSequence(const string& s)
{
    vector<int> res;
    int i = 0;
    for (char c : s)
    {
        if (isdigit(c))
        {
            i = i * 10 + (c - '0');
        }
        else
        {
            res.emplace_back(i);
            i = 0;
        }
    }
    res.emplace_back(i);
    return res;
}

int GetPosibilities(unsigned forced, unsigned place, unsigned int maxmask, unsigned int value, vector<unsigned int>& masks)
{
    int total = 0;
    if (masks.size() > 0)
    {
        vector<unsigned int> nm;
        unsigned int mask = masks[0];
        for (size_t i = 1; i < masks.size(); ++i)
        {
            nm.push_back(masks[i]);
        }
        while (mask <= maxmask)
        {
            total += GetPosibilities(forced, place, maxmask, value + mask, nm);
            mask *= 2;
            for (auto& m : nm) m *= 2;
        }
    }
    else
    {
        if (((value & forced) == forced) && ((value & place) == value))
        {
            return 1;
        }
        return 0;
    }
    return total;
}

Data ProcessLine(const Line& line)
{
    const auto words = line.GetWords();
    string fields = words[0];
    vector<int> seq = GetSequence(words[1]);

    int p = 0;
    unsigned forced = 0;
    unsigned place = 0;

    unsigned i_max = 1;
    for (char c : fields)
    {
        switch (c)
        {
        default:
            cout << "unexpected char '" << c << "'" << endl;
            exit(1);
        case '.':
            break;
        case '#':
            forced += i_max;
            place += i_max;
            break;
        case '?':
            place += i_max;
            break;
        }
        i_max *= 2;
    }

    vector<unsigned int> masks;
    int j = 0;
    for (int s : seq)
    {
        unsigned int m = (0xFFFFFFFF >> (32 - s));
        m <<= j;
        masks.push_back(m);
        j += s + 1;
    }

    p = GetPosibilities(forced, place, i_max, 0, masks);

    return Data{ fields, seq, p };
}

int main()
{
//    TextFile f("../../AOC 12/data/test.txt");
    TextFile f("../../AOC 12/data/simple.txt");

    vector<Data> datas;
    for (const auto& line : f.GetLines())
    {
        datas.emplace_back(ProcessLine(line));
    }

    int total = 0;
    for (const Data& d : datas)
    {
        cout << d.input << " ";
        for (size_t i = 0; i < d.seq.size(); ++i)
        {
            if (i) cout << ",";
            cout << d.seq[i];
        }
        cout << " " << d.possibilities << endl;
        total += d.possibilities;
    }

    cout << endl << total << endl;

    return 0;
}

