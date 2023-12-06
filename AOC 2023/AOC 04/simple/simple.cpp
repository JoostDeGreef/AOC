#include "AOC.h"

using namespace std;

int main()
{
    TextFile f("../../AOC 04/data/simple.txt");

    struct Card
    {
        std::unordered_set<int> winners;
        std::unordered_set<int> numbers;
        int value = 0;
        int id = -1;
    };

    std::vector<Card> cards;

    for (auto l : f.GetLines())
    {
        int state = 0;
        int id = -1;
        Card card;
        for (auto w : l.GetWords())
        {
            switch (state)
            {
            case 0:
                state++;
                break;
            case 1:
                id = strtol(w.c_str(), nullptr, 10);
                state++;
                break;
            case 2:
                if (w == "|")
                {
                    state++;
                }
                else
                {
                    int nr = strtol(w.c_str(), nullptr, 10);
                    card.winners.emplace(nr);
                }
                break;
            case 3:
            {
                int nr = strtol(w.c_str(), nullptr, 10);
                card.numbers.emplace(nr);
            }
            break;
            default:
                cout << "Coding error!" << endl;
                return 1;
            }
        }
        cards.push_back(card);
    }

    int score = 0;
    for (auto& card : cards)
    {
        for (auto w : card.winners)
        {
            if (card.numbers.find(w) != card.numbers.end())
            {
                card.value = max(card.value * 2, 1);
            }
        }
        score += card.value;
    }

    cout << "score = " << score << endl;

    return 0;
}

