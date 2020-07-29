#include <iostream>
#include <algorithm>

char answer[1048577];

int getProperPow(int n)
{
    int result = 1;
    while (result < n)
        result <<= 1;
    return result;
}

void fillAnswer(int count, int left, int right)
{
    if (count == 1)
        answer[left] = '#';
    else if (count <= 0)
        return;
    else if (count <= (right-left+1)/2)
        fillAnswer(count, left, (left+right)/2);
    else
    {
        int bigger = count/2 + count%2;
        int smaller = count/2;
        int mid = (left+right)/2;
        fillAnswer(bigger, left, mid);
        fillAnswer(smaller, mid+1, right);
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    int length = getProperPow(n);
    std::fill(answer, answer + length, '.');
    fillAnswer(n, 0, length-1);
    printf("%s", answer);

    return 0;
}