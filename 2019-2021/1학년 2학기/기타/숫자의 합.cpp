#include <iostream>

int main()
{
    int N;
    long long sum = 0;
    scanf("%d", &N);
    char tempInput;

    do
    {
        scanf("%c", &tempInput);
    } while (tempInput == '\n' || tempInput == '\r');

    sum += tempInput - '0';

    for (int i = 1; i < N; ++i)
    {
        scanf("%c", &tempInput);
        sum += tempInput -'0';
    }

    printf("%lld", sum);

    return 0;
}