#include <iostream>

std::pair<int, int> points[100000];
int n;

std::pair<int, int> GetPoint(int index)
{
    index %= n;
    return points[index];
}

std::pair<int, int> ToVec(std::pair<int, int> p1, std::pair<int, int> p2)
{
    return {p1.first - p2.first, p1.second - p2.second};
}

int main()
{
    scanf("%d", &n);

    for (int i = 0; i < n; ++i)
        scanf("%d %d", &points[i].first, &points[i].second);

    if (n % 2 == 0)
    {
        for (int i = 0; i < n / 2; ++i)
        {
            std::pair<int, int> vec1, vec2;
            vec1 = ToVec(GetPoint(i + 1), GetPoint(i));
            vec2 = ToVec(GetPoint(i + n / 2), GetPoint(i + n / 2 + 1));

            if (vec1 != vec2)
            {
                printf("NO");
                return 0;
            }
        }

        printf("YES");
    }
    else
        printf("NO");
    

    return 0;
}