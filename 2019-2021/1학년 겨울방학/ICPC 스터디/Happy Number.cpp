#include <iostream>
#include <unordered_set>

typedef long long Long;

Long Convert(Long n)
{
    Long result = 0;
    while (n != 0)
    {
        result += (n % 10) * (n % 10);
        n /= 10;
    }

    return result;
}

int main()
{
    Long input;
    scanf("%lld", &input);

    Long num = input;
    std::unordered_set<Long> used;
    used.insert(num);
    do
    {
        num = Convert(num);
        if (used.find(num) != used.end())
            num = input;
        else used.insert(num);
    } while (num != input && num != 1);
    
    if (num == 1)
        printf("HAPPY");
    else printf("UNHAPPY");

    return 0;
}