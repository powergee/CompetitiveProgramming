#include <iostream>
#include <string>
#include <stack>

bool isValid(std::string& input)
{
    std::stack<char> parStack;

    for (int i = 0; i < (int)input.size(); ++i)
    {
        if (input[i] == '(' || input[i] == '[')
            parStack.push(input[i]);
        else if (input[i] == ')')
        {
            if (parStack.empty() || parStack.top() == '[')
                return false;
            parStack.pop();
        }
        else
        {
            if (parStack.empty() || parStack.top() == '(')
                return false;
            parStack.pop();
        }
    }

    return parStack.size() == 0;
}

int getScore(std::string& input, int& pos)
{
    char opening = input[pos++];
    char closing = (opening == '(' ? ')' : ']');
    int childSum = 0;

    while (pos < (int)input.size())
    {
        if (input[pos] == closing)
        {
            if (childSum == 0)
                return (opening == '(' ? 2 : 3);
            else
                return childSum * (opening == '(' ? 2 : 3);
        }
        else
            childSum += getScore(input, pos); 

        ++pos;
    }

    return 0;
}

int main()
{
    std::string input;
    std::cin >> input;

    if (isValid(input))
    {
        int pos = 0, answer = 0;
        while (pos < (int)input.size())
        {
            answer += getScore(input, pos);
            ++pos;
        }
        printf("%d", answer);
    }
    else printf("0");
}