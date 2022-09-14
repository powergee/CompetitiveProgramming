#include <iostream>
#include <list>
#include <algorithm>

std::list<int> q;

int FindFront(int val)
{
    int index = 0;
    for (auto it = q.begin(); it != q.end(); ++it)
    {
        if (*it == val)
            return index;
        else ++index;
    }

    return -1;
}

int main()
{
    int n;
    scanf("%d", &n);

    for (int i = 1; i <= n; ++i)
        q.push_back(i);
    
    int m;
    scanf("%d", &m);

    int count = 0;
    for (int i = 0; i < m; ++i)
    {
        int num;
        scanf("%d", &num);

        int index = FindFront(num);
        int rightIdx = (int)q.size() - index;
        if (index < rightIdx)
        {
            for (int j = 0; j < index; ++j)
            {
                q.push_back(q.front());
                q.pop_front();
            }
            q.pop_front();
            count += index;
        }
        else
        {
            for (int j = 0; j < rightIdx; ++j)
            {
                q.push_front(q.back());
                q.pop_back();
            }
            q.pop_front();
            count += rightIdx;
        }
    }

    printf("%d", count);

    return 0;
}