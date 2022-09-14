#include <iostream>
#include <algorithm>
using namespace std;

char input[51];
char result[51];
bool visited[51][51][51][2][2];
int aCount = 0, bCount = 0, cCount = 0;

bool Attended(int index, char ch)
{
    if (index >= 0 && index <= 50)
    {
        if (result[index] == ch)
            return true;
        else return false;
    }
    else return false;
}

bool Process(int index, int a, int b, int c)
{
    if (a == 0 && b == 0 && c == 0)
        return true;

    bool BAvail = !Attended(index - 1, 'B'), CAvail = !Attended(index - 1, 'C') && !Attended(index - 2, 'C');

    if (visited[a][b][c][BAvail][CAvail])
        return false;
    
    visited[a][b][c][BAvail][CAvail] = true;

    if (a > 0)
    {
        result[index] = 'A';
        if (Process(index + 1, a - 1, b, c))
            return true;
    }
    
    if (b > 0 && BAvail)
    {
        result[index] = 'B';
        if (Process(index + 1, a, b - 1, c))
            return true;
    }

    if (c > 0 && CAvail)
    {
        result[index] = 'C';
        if (Process(index + 1, a, b, c - 1))
            return true;
    }

    return false;
}

int main()
{
    scanf("%s", input);

    char c;
    for (int i = 0; (c = input[i]) != '\0'; ++i)
    {
        switch (c)
        {
            case 'A':
                ++aCount;
                break;
            case 'B':
                ++bCount;
                break;
            case 'C':
                ++cCount;
                break;
        }
    }

    fill (&result[0], result + 51, '\0');
    if (Process(0, aCount, bCount, cCount))
    {
        for (int i = 0; i < 51; ++i)
        {
            if (result[i] == '\0')
                break;
            else printf("%c", result[i]);
        }
    }
    else printf("%d", -1);

    return 0;
}