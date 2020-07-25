#include <iostream>

int cards[3];
int k;

bool isPossible(int remaining)
{
    if (cards[0] < cards[1] && cards[1] < cards[2])
        return true;
    
    if (remaining <= 0)
        return false;
    
    for (int i = 0; i < 3; ++i)
    {
        cards[i] *= 2;
        if (isPossible(remaining - 1))
            return true;
        cards[i] /= 2;
    }
    return false;
}

int main()
{
    scanf("%d %d %d", &cards[0], &cards[1], &cards[2]);
    scanf("%d", &k);
    
    printf("%s", isPossible(k) ? "Yes" : "No");

    return 0;
}