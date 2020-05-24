#include <iostream>
#include <set>
#include <algorithm>

int numOfPeo1[200010];
int numOfPeo2[200010];
std::set<int> posOfPeo;
int n;

int CountMin()
{
    int result = 0;

    for (int i = 1; i <= n; ++i)
    {
        if (numOfPeo1[i] == 0)
            continue;

        numOfPeo1[i] = numOfPeo1[i+1] = numOfPeo1[i+2] = 0;
        ++result;
    }

    return result;
}

int CountMax()
{
    int result = 0;

    for (int i = 1; i <= n; ++i)
    {
        if (numOfPeo2[i] == 0)
            continue;

        int& left = numOfPeo2[i - 1];
        int& it = numOfPeo2[i];
        int& right = numOfPeo2[i + 1];

        if (left && it && right)
            continue;

        else if (!left && it && !right)
        {
            if (!left && it)
            {
                ++result;
                ++left;
                --it;
            }
            if (!right && it)
            {
                ++result;
                ++right;
                --it;
            }
        }
        
        else if (!left && it)
        {

        }
    }

    return result;
}

int main()
{
    scanf("%d", &n);

    for (int i = 0; i < n; ++i)
    {
        int pos;
        scanf("%d", &pos);
        
        ++numOfPeo1[pos];
        ++numOfPeo2[pos];

        posOfPeo.insert(pos);
    }

    int resMin = CountMin();
    int resMax = CountMax();

    printf("%d %d", resMin, resMax);

    return 0;
}