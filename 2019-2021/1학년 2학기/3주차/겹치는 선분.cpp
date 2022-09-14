#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

vector<pair<int, int>> points;

int main()
{
    int N;
    scanf("%d", &N);

    for (int i = 0; i < N; ++i)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        points.push_back({a, 1});
        points.push_back({b, -1});
    }

    sort(points.begin(), points.end());

    int current = 0;
    int result = 0;

    for (int i = 0; i < points.size(); ++i)
    {
        current += points[i].second;
        if (result < current) result = current;
    }

    printf("%d", result);

    return 0;
}