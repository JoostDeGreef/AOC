#include "AOC.h"

using namespace std;

enum Type
{
    None = 0,
    FiveOfAKind = 7,
    FourOfAKind = 6,
    FullHouse = 5,
    ThreeOfAKind = 4,
    TwoPairs = 3,
    OnePair = 2,
    HighCard = 1,
};

struct Hand
{
    Hand(const string& cards, const int bid)
        : cards(cards)
        , bid(bid)
        , value(0)
        , type(None)
        , rank(-1)
    {
        DetermineValue();
        DetermineType();
    }

    string cards;
    int bid;
    int64_t value;
    Type type;
    int rank;

    void DetermineValue()
    {
        for (const auto c : cards)
        {
            value *= 16;
            switch (c)
            {
            case '2': value += 1; break;
            case '3': value += 2; break;
            case '4': value += 3; break;
            case '5': value += 4; break;
            case '6': value += 5; break;
            case '7': value += 6; break;
            case '8': value += 7; break;
            case '9': value += 8; break;
            case 'T': value += 9; break;
            case 'J': value += 0; break;
            case 'Q': value += 10; break;
            case 'K': value += 11; break;
            case 'A': value += 12; break;
            }
        }
    }

    void DetermineType()
    {
        map<char, int> m;
        int jokers = 0;
        for (const auto c : cards)
        {
            if (c != 'J')
            {
                auto iter = m.find(c);
                if (iter == m.end())
                {
                    iter = m.emplace(c, 0).first;
                }
                iter->second++;
            }
            else
            {
                jokers++;
            }
        }
        switch (m.size())
        {
        case 0: // JJJJJ
        case 1:
            type = FiveOfAKind;
            break;
        case 2:
            if (m.begin()->second == 1 || m.begin()->second+jokers == 4)
            {
                type = FourOfAKind;
            }
            else
            {
                type = FullHouse;
            }
            break;
        case 3:
            type = TwoPairs;
            for (const auto k : m)
            {
                if (k.second+jokers == 3)
                {
                    type = ThreeOfAKind;
                    break;
                }
            }
            break;
        case 4:
            type = OnePair;
            break;
        case 5:
            type = HighCard;
            break;
        }
    }

    bool operator < (const Hand& hand)
    {
        if (type < hand.type)
        {
            return true;
        }
        if (type == hand.type)
        {
            return value < hand.value;
        }
        else
        {
            return false;
        }
    }
};

int main()
{
    TextFile f("../../AOC 07/data/simple.txt");
    //TextFile f("../../AOC 07/data/test.txt");
    vector<Hand> hands;

    for (auto& l : f.GetLines())
    {
        if (!l.Empty())
        {
            const auto words = l.GetWords();
            hands.emplace_back(words[0], strtol(words[1].c_str(), nullptr, 10));
        }
    }

    sort(hands.begin(), hands.end());

    size_t score = 0;
    for (size_t i = 0; i < hands.size(); ++i)
    {
        cout << hands[i].cards << " " << hands[i].type << " " << hands[i].value << endl;
        score += (i + 1) * hands[i].bid;
    }

    cout << score << endl;
    return 0;
}

