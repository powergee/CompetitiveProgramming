#include <iostream>
#include <algorithm>

struct Square
{
    int x1, x2, y1, y2;

    bool operator < (const Square& s) const
    {
        if (y1 == s.y1)
            return x1 <= s.x1;
        return y1 < s.y1;
    }

    bool IsInside(int x, int y)
    {
        return (x1 <= x && x <= x2) && (y1 <= y && y <= y2);
    }
};

Square sq[200000];

int main()
{
    int N;
    scanf("%d", &N);

    for (int i = 0; i < N; ++i)
    {
        int x1, x2, y1, y2;
        scanf("%d %d %d %d", &x1, &x2, &y1, &y2);

        sq[i] = {x1, x2, y1, y2};
    }

    return 0;
}