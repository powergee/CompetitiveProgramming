#include <iostream>
#include <algorithm>

int n;
int answer[80];

bool IsGood(int pos)
{
    for (int length = 1; length * 2 <= pos + 1; ++length)
    {
        bool isSame = true;
        for (int i = 0; i < length && isSame; ++i)
        {
            if (answer[pos - length + i + 1] != answer[pos - 2*length + i + 1])
                isSame = false;
        }

        if (isSame)
            return false;
    }

    return true;
}

bool FindSmallest(int pos)
{
    if (pos >= n)
        return true;
    
    for (int i = 1; i <= 3; ++i)
    {
        answer[pos] = i;
        if (IsGood(pos))
        {
            if (FindSmallest(pos + 1))
                return true;
        }
    }
    
    return false;
}

int main()
{
    scanf("%d", &n);
    FindSmallest(0);

    for (int i = 0; i < n; ++i)
        printf("%d", answer[i]);

    return 0;
}