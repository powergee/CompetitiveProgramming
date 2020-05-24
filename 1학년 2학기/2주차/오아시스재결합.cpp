#include <iostream>
#include <stack>
typedef long long Long;

int nums[500000];

int main()
{
    int N;
    scanf("%d", &N);

    for (int i = 0; i < N; ++i)
        scanf("%d", &nums[i]);

    // first:키 second:스택의 뒤에 연속적으로 키가 같은 사람 수
    std::stack<std::pair<int, int>> s;
    Long result = 0;
    s.push({nums[0], 1});

    for (int i = 1; i < N; ++i)
    {
        std::pair<int, int> newEle = {nums[i], 1};

        while (!s.empty() && s.top().first <= nums[i])
        {
            result += s.top().second;
            if (s.top().first == nums[i])
                newEle.second += s.top().second;

            s.pop();
        }

        // 키가 작은 사람들을 스택에서 제거한 뒤 스택이 비지 않았다면 1명만 볼 수 있음.
        if (!s.empty())
            ++result;

        s.push(newEle);
    }

    printf("%lld", result);

    return 0;
}