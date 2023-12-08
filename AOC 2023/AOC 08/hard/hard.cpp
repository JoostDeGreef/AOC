#include "AOC.h"

using namespace std;

struct Node
{
    Node()
        : Node("INVALID", "INVALID", "INVALID")
    {}
    Node(const string& s0, const string& s1, const string& s2)
    {
        auto filter = [](const string& s)
        {
            string res;
            for (const auto c : s)
            {
                switch (c)
                {
                case ',':
                case '(':
                case ')':
                    break;
                default:
                    res += c;
                    break;
                }
            }
            return res;
        };
        name = s0;
        left = filter(s1);
        right = filter(s2);
        startnode = name.back() == 'A';
        endnode = name.back() == 'Z';
    }
    Node(const Node& node)
    {
        Copy(node);
    }
    Node& operator - (const Node& node)
    {
        Copy(node);
        return *this;
    }
    void Copy(const Node& node)
    {
        name = node.name;
        left = node.left;
        right = node.right;
        startnode = node.startnode;
        endnode = node.endnode;
    }
    string name;
    string left;
    string right;
    bool startnode;
    bool endnode;
};

int main()
{
    TextFile f("../../AOC 08/data/simple.txt");
//    TextFile f("../../AOC 08/data/hard.txt");

    const auto& lines = f.GetLines();
    string lr = lines[0];

    map<string, Node> nodes;
    vector<Node> cur;
    for (size_t i = 2; i < lines.size(); ++i)
    {
        auto words = lines[i].GetWords();
        if (!words.empty())
        {
            auto iter = nodes.emplace(words[0], Node(words[0], words[2], words[3]));
            if (iter.first->second.startnode)
            {
                cur.push_back(iter.first->second);
            }
        }
    }

    int64_t res = 1;
    cout << "LR size = " << lr.size() << endl;
    for (auto& node : cur)
    {
        auto iter = lr.begin();
        int count = 0;
        cout << node.name << " ";
        while (!node.endnode)
        {
            if (*iter == 'L')
            {
                node = nodes[node.left];
            }
            else
            {
                node = nodes[node.right];
            }
            iter++;
            if (iter == lr.end())
            {
                iter = lr.begin();
            }
            count++;
        }
        cout << count << endl;
        res *= count / lr.size();
    }

    res *= lr.size();
    cout << res << endl;

    return 0;
}

