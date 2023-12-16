#include "AOC.h"

using namespace std;

typedef int64_t I;

struct Data
{
    string input;
    vector<size_t> seq;
    I possibilities;
};

vector<size_t> GetSequence(const string& s)
{
    vector<size_t> res;
    size_t i = 0;
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

I GetPosibilities(const vector<string>& parts, const vector<size_t>& seq)
{
    if (seq.size() == 0)
    {
        for (const auto& part : parts)
        {
            for (char c : part)
            {
                if (c == '#') return 0;
            }
        }
        return 1;
    }
    else if (parts.size() == 0)
    {
        return 0;
    }
    else if (seq.size() == 1)
    {
        if (parts.size() > 1)
        {
            I count = 0;
            for (size_t k = 0; k < parts.size(); ++k)
            {
                vector<string> p2 = parts;
                p2.erase(p2.begin() + k);
                I s = GetPosibilities(p2, {});
                if(s) count += GetPosibilities({ parts[k] }, seq) * s;
            }
            return count;
        }
        else
        {
            I count = 0;
            auto part = parts[0];
            int j = part.size() - seq[0];
            if (j < 0) return 0;
            if (j == 0) return 1;
            for (int i = 0; i < j + 1; ++i)
            {
                auto p = part;
                p.erase(i, seq[0]);
                bool okay = true;
                for (char c : p)
                {
                    if (c == '#')
                    {
                        okay = false;
                        break;
                    }
                }
                count += okay ? 1 : 0;
            }
            return count;
        }
    }
    else
    {
        size_t total_seq = 0;
        size_t m = seq.size()/2;
        for (size_t i = 0; i < seq.size()/2; ++i)
        {
            size_t c = (seq.size() / 2) - i - 1;
            total_seq += seq[c];
            if (seq[c] > seq[m])
            {
                m = c;
            }
        }
        for (size_t i = seq.size()/2; i < seq.size(); ++i)
        {
            total_seq += seq[i];
            if (seq[i] > seq[m])
            {
                m = i;
            }
        }

        size_t total_wells = 0;
        size_t total_chars = 0;
        for (const auto& part : parts)
        {
            for (char c : part)
            {
                if (c == '#') total_wells++;
                total_chars++;
            }
        }

        if (total_seq < total_wells) return 0;
        if (total_seq > total_chars) return 0;

        vector<size_t> s0(seq.begin(),seq.begin() + m);
        vector<size_t> s1(seq.begin() + m + 1, seq.end());
        I total = 0;
        for (size_t i = 0; i < parts.size(); ++i)
        {
            I sub = 0;
            if (parts[i].size() == seq[m])
            {
                vector<string> p0(parts.begin(), parts.begin() + i);
                vector<string> p1(parts.begin() + i + 1, parts.end());
                I s = GetPosibilities(p0, s0);
                if(s) sub += s * GetPosibilities(p1, s1);
            }
            else if(parts[i].size() > seq[m])
            {
                vector<string> p0(parts.begin(), parts.begin() + i);
                vector<string> p1(parts.begin() + i + 1, parts.end());
                int j = parts[i].size() - seq[m];
                for (int k = 0; k <= j; ++k)
                {
                    string before = { parts[i].begin(),parts[i].begin() + k };
                    string after = { parts[i].begin() + k + seq[m],parts[i].end() };

                    if (before.empty() || before.back() == '?')
                    {
                        if (after.empty() || after.front() == '?')
                        {
                            vector<string> pp0(p0);
                            vector<string> pp1(p1);
                            if (before.size() > 1)
                            {
                                before.erase(before.size() - 1);
                                pp0.push_back(before);
                            }
                            if (after.size() > 1)
                            {
                                after.erase(0, 1);
                                pp1.insert(pp1.begin(), after);
                            }
                            I s = GetPosibilities(pp0, s0);
                            if(s) sub += s * GetPosibilities(pp1, s1);
                        }
                    }
                }
            }
            total += sub;
        }
        return total;
    }
}

Data ProcessLine(const Line& line)
{
    cout << "<";
    const auto words = line.GetWords();
    string fields = words[0] + "?" + words[0] + "?" + words[0] + "?" + words[0] + "?" + words[0];
    vector<size_t> seq = GetSequence(words[1] + "," + words[1] + "," + words[1] + "," + words[1] + "," + words[1]);
    //string fields = words[0];
    //vector<int> seq = GetSequence(words[1]);

    I p = 0;

    vector<string> parts = {};
    string part;
    for (char c : fields)
    {
        switch (c)
        {
        case '#':
        case '?':
            part += c;
            break;
        case '.':
            if (!part.empty())
            {
                parts.emplace_back(part);
                part.clear();
            }
            break;
        }
    }
    if (!part.empty())
    {
        parts.emplace_back(part);
    }

    p = GetPosibilities(parts, seq);

    cout << ">";

    return Data{ fields, seq, p };
}

int main()
{
    TextFile f("../../AOC 12/data/simple.txt");
    //TextFile f("../../AOC 12/data/test.txt");

    auto datas = AOC::ForAll(f.GetLines(),ProcessLine);

    I total = 0;
    int i = 0;
    for (const auto& d: datas)
    {
        cout << ++i << " " << d.input << " ";
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

