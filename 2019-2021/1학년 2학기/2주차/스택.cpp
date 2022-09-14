#include <iostream>
#include <string>
#include <stack>

int main()
{
    std::string input;
    std::stack<int> s;
    int N, num;
    std::cin >> N;

    while (N--)
    {
        std::cin >> input;

        if (input == "push")
        {
            std::cin >> num;
            s.push(num);
        }
        else if (input == "pop")
        {
            if (s.empty())
                printf("-1\n");
            else
            {
                num = s.top();
                s.pop();
                printf("%d\n", num);
            }
        }
        else if (input == "size")
        {
            printf("%d\n", s.size());
        }
        else if (input == "empty")
        {
            printf("%d\n", s.empty() ? 1 : 0);
        }
        else if (input == "top")
        {
            if (s.empty())
                printf("-1\n");
            else printf("%d\n", s.top());
        }
    }

    return 0;
}