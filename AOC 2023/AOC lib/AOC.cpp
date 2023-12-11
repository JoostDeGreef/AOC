
#include "AOC.h"

using namespace std;

std::ostream& operator << (std::ostream& os, const Pos& p)
{
    os << "(" << p.x << "," << p.y << ")";
    return os;
}
