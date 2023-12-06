#include "AOC.h"

using namespace std;

int main()
{
    TextFile f("../../AOC 04/data/hard.txt");

    struct Card
    {
        std::unordered_set<int> winners;
        std::unordered_set<int> numbers;
        int value = 0;
        int matches = 0;
        int instances = 1;
        int id = -1;
    };

    std::vector<Card> cards;

    for (auto l : f.GetLines())
    {
        int state = 0;
        Card card;
        for (auto w : l.GetWords())
        {
            switch (state)
            {
            case 0:
                state++;
                break;
            case 1:
                card.id = strtol(w.c_str(), nullptr, 10);
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
                card.matches++;
                card.value = max(card.value * 2, 1);
            }
        }
        score += card.value;
    }

    int instances = 0;
    for (auto& card : cards)
    {
        for (int i = card.id; i < card.id + card.matches; ++i)
        {
            if (i >= (int)cards.size()) break;
            cards[i].instances+=card.instances;
        }
        instances += card.instances;
    }

    cout << "score = " << score << endl;
    cout << "cards = " << instances << endl;

    return 0;
}

