#include <iostream>
#include <string>

bool IsValid(int num)
{
    int count = 0;
    while (num)
    {
        if (num % 10 == 6)
            ++count;
        else count = 0;
        num /= 10;

        if (count == 3)
            return true;
    }

    return false;
}

int main()
{
    int n;
    scanf("%d", &n);

    int count = 0;
    for (int i = 666;; ++i)
    {
        if (IsValid(i))
            ++count;
        
        if (count == n)
        {
            printf("%d", i);
            return 0;
        }
    }

    return 0;
}