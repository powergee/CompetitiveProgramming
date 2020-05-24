#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> nums;
int bound, k;
int maxDigit;
int answer = -1;

void FindAnswer(int sum, int digit)
{
    if (digit > maxDigit)
        return;

    for (int num : nums)
    {
        int currResult = sum + digit * num;
        if (currResult <= bound)
            answer = std::max(answer, currResult);

        FindAnswer(currResult, digit * 10);
    }
}

int main()
{
    scanf("%d %d", &bound, &k);

    nums.resize(k);
    for (int i = 0; i < k; ++i)
        scanf("%d", &nums[i]);

    int boundCopy = bound;
    int maxDigitCount = 0;

    do
    {
        ++maxDigitCount;
        boundCopy /= 10;
    } while (boundCopy);

    maxDigitCount -= 1;
    maxDigit = 1;
    while (maxDigitCount--)
        maxDigit *= 10;

    FindAnswer(0, 1);
    printf("%d", answer);

    return 0;
}