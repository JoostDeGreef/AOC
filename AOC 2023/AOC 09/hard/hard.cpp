#include "AOC.h"

using namespace std;

int main()
{
    TextFile f("../../AOC 02/data/hard.txt");

    cout << "++++ file\n";
    cout << f;
    cout << "---- file\n";

    cout << "++++ lines\n";
    for (const auto& line : f.GetLines())
    {
        cout << line << endl;
    }
    cout << "---- lines\n";

    cout << "++++ words\n";
    for (const auto& line : f.GetLines())
    {
        for (const auto& word : line.GetWords())
        {
            cout << word << endl;
        }
    }
    cout << "---- words\n";

    return 0;
}

