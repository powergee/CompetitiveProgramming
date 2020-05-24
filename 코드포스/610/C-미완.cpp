#include <iostream>
#include <algorithm>

int n, T, a, b;
// first(char): mandatory가 되는데 걸리는 시간
// second(char): 난이도 (1 일 때 hard), 입력을 받을 때 문자로 받지 않고 정수로 받음.
std::pair<int, char> problems[200000];
// costSum[i]: 정렬한  0~i까지의 총 소요 시간
long long costSum[200000];

inline long long Cost(const std::pair<int, char>& prob)
{
    return prob.second ? b : a;
}

int main()
{
    int m;
    scanf("%d", &m);

    while (m--)
    {
        scanf("%d %d %d %d", &n, &T, &a, &b);

        for (int i = 0; i < n; ++i)
            scanf("%d", &problems[i].second);

        for (int i = 0; i < n; ++i)
            scanf("%d", &problems[i].first);

        std::sort(problems, problems + n);

        costSum[0] = Cost(problems[0]);
        for (int i = 1; i < n; ++i)
            costSum[i] = costSum[i-1] + Cost(problems[i]);

        // 가장 최근에 확인한 문제의 인덱스를 저장해둠
        int lastChecked = 0;
        int maxPoint = -1;

        for (int time = 0; time <= T; ++time)
        {
            
        }
    }

    return 0;
}