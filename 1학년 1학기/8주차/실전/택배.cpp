#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

int N, C, M;
vector<tuple<int, int, int>> boxes;
int loaded[2000];

int CanLoad(int start, int des, int count)
{
    int able = count;

    for (int i = start; i < des; ++i)
    {
        if (loaded[i] + able > C)
            able = C-loaded[i];

        if (able <= 0)
            return 0;
    }

    return able;
}

int Load(int start, int des, int count)
{
    for (int i = start; i < des; ++i)
    {
        loaded[i] += count;
    }

    return count;
}

int main()
{
    scanf("%d %d", &N, &C);
    scanf("%d", &M);

    for (int i = 0; i < M; ++i)
    {
        int start, des, count;
        scanf("%d %d %d", &start, &des, &count);

        boxes.push_back(make_tuple(des - 1, start - 1, count));
    }

    int delivered = 0;
    sort(boxes.begin(), boxes.end());

    for (auto info : boxes)
    {
        int start, des, count;
        tie(des, start, count) = info;

        int able;
        if (able = CanLoad(start, des, count))
            delivered += Load(start, des, able);
    }

    printf("%d", delivered);
}