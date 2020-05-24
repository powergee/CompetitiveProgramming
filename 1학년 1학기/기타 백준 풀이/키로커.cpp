#include <iostream>
#include <stack>

using namespace std;

char input[1000001];
char output[1000001];

int main()
{
    int tc;
    scanf("%d", &tc);

    stack<char> front, back;

    for (; tc > 0; --tc)
    {
        while (!front.empty()) front.pop();
        while (!back.empty()) back.pop();

        cin >> input;

        for (int i = 0; input[i] != '\0'; ++i)
        {
            switch (input[i])
            {
            case '-':
                if (!front.empty())
                    front.pop();
                break;

            case '<':
                if (!front.empty())
                {
                    char chToMove = front.top();
                    front.pop();
                    back.push(chToMove);
                }
                break;

            case '>':
                if (!back.empty())
                {
                    char chToMove = back.top();
                    back.pop();
                    front.push(chToMove);
                }
                break;

            default:
                front.push(input[i]);
                break;
            }
        }

        output[front.size() + back.size()] = '\0';

        int frontSize = front.size();
        for (int i = frontSize -1; !front.empty(); --i)
        {
            output[i] = front.top();
            front.pop();
        }

        for (int i = frontSize; !back.empty(); ++i)
        {
            output[i] = back.top();
            back.pop();
        }

        printf("%s\n", output);
    }

    return 0;
}