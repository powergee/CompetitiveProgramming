#include <iostream>
#include <stack>

int main()
{
    int TC;
    scanf("%d", &TC);

    for (int i = 1; i <= TC; ++i)
    {
        int k;
        scanf("%d", &k);

        std::stack<long long> nums;

        while (k--)
        {
            long long input;
            scanf("%lld", &input);

            if (input == 0)
                nums.pop();
            else nums.push(input);
        }

        long long result = 0;
        while (!nums.empty())
        {
            long long toAdd = nums.top();
            nums.pop();
            result += toAdd;
        }

        printf("#%d %lld\n", i, result);
    }

    return 0;
}