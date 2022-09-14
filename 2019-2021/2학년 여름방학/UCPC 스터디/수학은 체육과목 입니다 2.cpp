#include <iostream>

int main()
{
    int input;
    scanf("%d", &input);

    int rem = input % 8;
    int answer;
    switch (rem)
    {
    case 1:
        answer = 1;
        break;
    case 2:
    case 0:
        answer = 2;
        break;
    case 3:
    case 7:
        answer = 3;
        break;
    case 4:
    case 6:
        answer = 4;
        break;
    case 5:
        answer = 5;
        break;
    }

    printf("%d", answer);
    return 0;
}