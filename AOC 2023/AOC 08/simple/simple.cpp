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
    }
    string name;
    string left;
    string right;
};

int main()
{
    TextFile f("../../AOC 08/data/simple.txt");

    const auto& lines = f.GetLines();
    string lr = lines[0];

    map<string, Node> nodes;
    for (size_t i = 2; i < lines.size(); ++i)
    {
        auto words = lines[i].GetWords();
        if (!words.empty())
        {
            nodes.emplace(words[0], Node(words[0], words[2], words[3]));
        }
    }

    int count = 0;
    Node node = nodes["AAA"];
    auto iter = lr.begin();
    while (node.name != "ZZZ")
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
        cout << node.name << endl;
        count++;
    }

    cout << count;
    return 0;
}

