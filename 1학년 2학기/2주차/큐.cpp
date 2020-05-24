#include <iostream>
#include <queue>

int main()
{
    std::string input;
    std::queue<int> q;
    int N, num;
    std::cin >> N;

    while (N--)
    {
        std::cin >> input;

        if (input == "push")
        {
            std::cin >> num;
            q.push(num);
        }
        else if (input == "pop")
        {
            if (q.empty())
                printf("-1\n");
            else
            {
                num = q.front();
                q.pop();
                printf("%d\n", num);
            }
        }
        else if (input == "size")
        {
            printf("%d\n", q.size());
        }
        else if (input == "empty")
        {
            printf("%d\n", q.empty() ? 1 : 0);
        }
        else if (input == "front")
        {
            if (q.empty())
                printf("-1\n");
            else printf("%d\n", q.front());
        }
        else if (input == "back")
        {
            if (q.empty())
                printf("-1\n");
            else printf("%d\n", q.back());
        }
    }

    return 0;
}