#include <iostream>
#include <queue>

struct AbsCompare
{
    bool operator()(const int a, const int b)
    {
        if (abs(a) == abs(b))
            return a > b;
        else return abs(a) > abs(b);
    }
};

std::priority_queue<int, std::vector<int>, AbsCompare> heap;

int main()
{
    int n;
    scanf("%d", &n);

    while (n--)
    {
        int x;
        scanf("%d", &x);

        if (x == 0)
        {
            if (heap.empty())
                printf("0\n");
            else
            {
                printf("%d\n", heap.top());
                heap.pop();
            }
        }
        else
            heap.push(x);
    }

    return 0;
}