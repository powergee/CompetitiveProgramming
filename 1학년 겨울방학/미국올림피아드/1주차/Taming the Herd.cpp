#include <iostream>
#include <vector>

std::vector<int> logs;

int CountMin()
{
    int answer = 0;
    for (int log : logs)
        if (log == 0)
            ++answer;

    return answer;
}

int CountMax()
{
    int answer = 0;
    for (int log : logs)
        if (log == 0 || log == -1)
            ++answer;

    return answer;
}

int main()
{
    int N;
    bool isPossible = true;
    scanf("%d", &N);

    for (int i = 0; i < N; ++i)
    {
        int input;
        scanf("%d", &input);

        if (i == 0)
            logs.push_back(0);
        else if (input == -1)
            logs.push_back(-1);
        else
        {
            logs.push_back(input);

            int length = logs.size();
            for (int i = 0; i < input; ++i)
            {
                int newVal = logs[length - 1 - i] - 1;
                if (logs[length - 2 - i] == -1)
                    logs[length - 2 - i] = newVal;
                else if (logs[length - 2 - i] != newVal)
                {
                    isPossible = false;
                    break;
                }
            }
        }
    }

    if (isPossible)
        printf("%d %d", CountMin(), CountMax());

    else printf("-1");

    return 0;
}