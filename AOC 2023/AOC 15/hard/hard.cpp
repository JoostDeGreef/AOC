#include "AOC.h"

using namespace std;

struct Lens
{
    string code;
    I hash;
    I strenght;
    I index;
};

Lens CalcLens(I index, const vector<string>& inputs)
{
    Lens l;
    l.index = index;
    l.hash = 0;
    bool nr = false;
    for (unsigned char c : inputs[index])
    {
        if (nr)
        {
            l.strenght = 10 * l.strenght + (c - '0');
        }
        else
        {
            if (c == '-')
            {
                l.strenght = -1;
                nr = true;
            }
            else if (c == '=')
            {
                l.strenght = 0;
                nr = true;
            }
            else
            {
                l.hash = 17 * (l.hash + c) & 0xFF;
                l.code += c;
            }
        }
    }
    return l;
}

typedef map<string, Lens> BoxMap;
typedef vector<Lens> Box;

void AddLensToBox(BoxMap& box, const Lens& lens)
{
    if (lens.strenght > 0)
    {
        auto iter = box.find(lens.code);
        if (iter != box.end())
        {
            iter->second.strenght = lens.strenght;
        }
        else
        {
            box[lens.code] = lens;
        }
    }
    else
    {
        box.erase(lens.code);
    }
}

Box SortLenses(I hash, const vector<Lens>& lenses)
{
    BoxMap m;
    for (const auto & lens : lenses)
    {
        if (lens.hash == hash)
        {
            AddLensToBox(m, lens);
        }
    }
    Box box;
    for (const auto& key : m)
    {
        box.emplace_back(key.second);
    }
    sort(box.begin(), box.end(), [](const Lens& a, const Lens& b) { return a.index < b.index; });
    return box;
}

int main()
{
    TextFile f("../../AOC 15/data/simple.txt");
    ThreadPool pool;

    cout << "step 0" << endl;

    vector<Lens> lenses;
    for (auto line : f.GetLines())
    {
        auto words = line.GetWords(',');
        vector<I> indices;
        for (I i = 0; i < words.size(); ++i)
        {
            indices.emplace_back(i);
        }
        auto nl = pool.ForAll(indices, CalcLens, words);
        lenses.insert(lenses.end(),nl.begin(),nl.end());
    }

    cout << "step 1" << endl;

    vector<I> hashes;
    for (I i = 0; i < 256; ++i)
    {
        hashes.emplace_back(i);
    }
    auto boxes = pool.ForAll(hashes, SortLenses, lenses);

    cout << "step 2" << endl;

    I total = 0;
    for (I i = 0; i < boxes.size(); ++i)
    {
        for (I j = 0; j < boxes[i].size(); ++j)
        {
            I s = boxes[i][j].strenght;
            I v = (i + 1) * (j + 1) * s;
            total += v;
        }
    }

    cout << total << endl;
    return 0;
}

