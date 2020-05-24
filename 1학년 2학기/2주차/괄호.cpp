#include <iostream>
#include <string>

int main()
{
    int T;
    std::cin >> T;

    std::string input;
    int count = 0;
    
    while (T--)
    {
        std::cin >> input;

        for (auto i = input.begin(); i != input.end(); ++i)
        {
            char ch = *i;
            if (ch == '(')
                ++count;
            else if (ch == ')')
                --count;

            if (count < 0)
            {
                printf("NO\n");
                goto nextCase;
            }
        }

        if (count > 0)
            printf("NO\n");
        
        else printf("YES\n");

        nextCase:
    }

    return 0;
}