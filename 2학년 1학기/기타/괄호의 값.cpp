#include <iostream>
#include <string>
#include <stack>

int getScore(std::string& input)
{
    std::stack<std::pair<char, int>> parStack;
    std::stack<int> valStack;

    for (int i = 0; i < input.size(); ++i)
    {
        if (input[i] == '(' || input[i] == '[')
            parStack.push({input[i], i});
        else if (input[i] == ')')
        {
            if (parStack.empty())
                return false;

            
        }
    }
}

int main()
{
    std::string input;
    std::cin >> input;


}