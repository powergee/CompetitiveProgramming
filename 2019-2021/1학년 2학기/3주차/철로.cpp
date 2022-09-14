#include <iostream>
#include <algorithm>
#include <vector>

typedef std::pair<int, int> Point;
typedef std::vector<Point>::iterator PointIter;
const int START = 1;
const int END = 0;

std::vector<Point> points; 

int main()
{
    int N;
    scanf("%d", &N);

    for (int i = 0; i < N; ++i)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        points.push_back(std::make_pair(std::min(a, b), START));
        points.push_back(std::make_pair(std::max(a, b), END));
    }

    std::sort(points.begin(), points.end());

    int D;
    scanf("%d", &D);

    PointIter iFront = points.begin();
    PointIter iBack = points.begin();
}