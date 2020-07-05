#include <iostream>

typedef long long Long;
int n;
int jobs[100000];

bool ableToSchedule(Long interval)
{

}

Long searchMinInterval(Long left, Long right)
{

}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
        scanf("%d", jobs + i);

    std::cout << searchMinInterval(0, 1e12);

    return 0;
}