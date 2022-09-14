#include <iostream>
#include <stack>

std::stack<char> s;
char str[1000001];

char table[4][4] = {
    {'A', 'C', 'A', 'G'},
    {'C', 'G', 'T', 'A'},
    {'A', 'T', 'C', 'G'},
    {'G', 'A', 'G', 'T'}
};

int BTI(char b)
{
    switch (b)
    {
    case 'A':
        return 0;
        break;

    case 'G':
        return 1;
        break;

    case 'C':
        return 2;
        break;

    case 'T':
        return 3;
        break;
    
    default:
        return -1;
        break;
    }
}

int main()
{
    int N;
    scanf("%d", &N);
    scanf("%s", str);

    for (int i = 0; i < N; ++i)
        s.push(str[i]);

    while (s.size() > 1)
    {
        int row, col;
        col = s.top();
        s.pop();
        row = s.top();
        s.pop();



        s.push(table[BTI(row)][BTI(col)]);
    }

    printf("%c", s.top());

    return 0;
}