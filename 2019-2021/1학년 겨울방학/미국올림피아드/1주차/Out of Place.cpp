#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> seq;

int CountByBubble()
{
    int count = 0;
    std::vector<int> arr(seq.begin(), seq.end());

    for (int i = 0; i < arr.size(); ++i)
    {
        for (int j = 0; j <= (signed)arr.size() - 2 - i; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                std::swap(arr[j], arr[j + 1]);
                ++count;
            }
        }
    }

    return count;
}

int main()
{
    int N;
    scanf("%d", &N);

    for (int i = 0; i < N; ++i)
    {
        int input;
        scanf("%d", &input);

        if (seq.empty() || seq.back() != input)
            seq.push_back(input);
    }

    if (N == 2)
    {
        if (seq.front() <= seq.back())
            printf("0");
        else printf("1");
    }
    else
    {
        printf("%d", CountByBubble());
    }

    return 0;
}