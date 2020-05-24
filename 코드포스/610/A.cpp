#include <iostream>

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int a, b, c, r;
        scanf("%d %d %d %d", &a, &b, &c, &r);
        if (a > b)
            std::swap(a, b);

        int coverLeft = c - r;
        int coverRight = c + r;
        int answer;

        // 범위가 a, b 밖
        if ((coverLeft <= a && coverRight <= a) || (b <= coverLeft && b <= coverRight))
        {
            answer = b - a;
        }
        // a쪽에서 걸침
        else if (coverLeft <= a && a <= coverRight && coverRight <= b)
        {
            answer = b - coverRight;
        }
        // b쪽에서 걸침
        else if (a <= coverLeft && coverLeft <= b && b <= coverRight)
        {
            answer = coverLeft - a;
        }
        // 범위가 a, b 사이에 있음
        else if (a <= coverLeft && coverRight <= b)
        {
            answer = (b - a) - 2 * r;
        }
        // 범위가 a, b를 포함함
        else
        {
            answer = 0;
        }

        printf("%d\n", answer);
    }

    return 0;
}