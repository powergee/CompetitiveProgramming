#include <iostream>
#include <algorithm>
#include <limits>

int n, m, c;
int arrTime[100000];

bool IsPossible(int T, int start = 0, int bus = m)
{
    if (start >= n)
        return true;
    
    if (bus == 0)
        return false;

    int last;

    for (last = start; last < start + c && last < n; ++last)
        if (arrTime[last] - arrTime[start] > T)
            break;

    return IsPossible(T, last, bus - 1);
}

int BinarySearch(int left, int right)
{
    if (left == right)
        return left;

    int med = (left + right) / 2;

    if (IsPossible(med))
        return BinarySearch(left, med);
    else
        return BinarySearch(med + 1, right);
}

int main()
{
    scanf("%d %d %d", &n, &m, &c);

    for (int i = 0; i < n; ++i)
        scanf("%d", arrTime + i);

    std::sort(arrTime, arrTime + n);
    printf("%d", BinarySearch(0, arrTime[n - 1] - arrTime[0]));

    return 0;
}