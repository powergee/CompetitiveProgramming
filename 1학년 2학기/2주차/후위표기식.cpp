#include <iostream>
#include <stack>

void PrintStack(std::stack<char>& s)
{
    while (!s.empty())
    {
        char ch;
        ch = s.top();
        s.pop();

        if (ch == '(')
            break;

        printf("%c", ch);
    }
}

int main()
{
    std::stack<char> opers;

    char input;
    while (scanf("%c", &input), input != '\n' && input != '\r')
    {
        switch (input)
        {
        case '+':
        case '-':
        case '*':
        case '/':
            if (!opers.empty())
            {
                if (opers.top() == '*' || opers.top() == '/')
                    PrintStack(opers);
            }
            opers.push(input);
            break;

        case '(':
            opers.push(input);
            break;

        case ')':
            PrintStack(opers);
            break;

        default:
            printf("%c", input);
            break;
        }
    }

    PrintStack(opers);

    return 0;
}