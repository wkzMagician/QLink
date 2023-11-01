#include "pos.h"

Pos operator+(const Pos &p1, const Pos &p2)
{
    return Pos(p1.x + p2.x, p1.y + p2.y);
}

Pos operator-(const Pos &p1, const Pos &p2)
{
    return Pos(p1.x - p2.x, p1.y - p2.y);
}

Pos& operator+=(Pos &p1, const Pos &p2)
{
    p1.x += p2.x;
    p1.y += p2.y;
    return p1;
}

bool operator==(const Pos &p1, const Pos &p2)
{
    return p1.x == p2.x && p1.y == p2.y;
}

bool operator!=(const Pos &p1, const Pos &p2)
{
    return not (p1.x == p2.x && p1.y == p2.y);
}

QDebug operator<<(QDebug debug, const Pos& pos)
{
    debug.nospace() << "(" << pos.x << ", " << pos.y << ")";
    return debug.space();
}
