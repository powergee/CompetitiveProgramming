#include <iostream>
#include <algorithm>
using namespace std;

int aCount = 0, bCount = 0, cCount = 0;
int length;
char result[51];

bool Find(int pos, int aRemain, int bRemain, int cRemain)
{
    if (pos >= length)
        return true;

    // C가 출근할 경우
    if (cRemain > 0 && result[pos - 1] != 'C' && result[pos - 2] != 'C')
    {
        result[pos] = 'C';
        return Find(pos + 1, aRemain, bRemain, cRemain - 1);
    }

    // B가 출근할 경우
    if (bRemain > 0 && result[pos - 1] != 'B')
    {
        result[pos] = 'B';
        return Find(pos + 1, aRemain, bRemain - 1, cRemain);
    }

    // A가 출근할 경우
    if (aRemain > 0)
    {
        result[pos] = 'A';
        return Find(pos + 1, aRemain - 1, bRemain, cRemain);
    }

    return false;
}

int main()
{
    char input[51];
    scanf("%s", input);

    bool halt = false;
    for (int i = 0; i < 51; ++i)
    {
        switch (input[i])
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

        default:
            halt = true;
            break;
        }

        if (halt)
            break;
    }

    length = aCount + bCount + cCount;

    if (Find(0, aCount, bCount, cCount))
        printf("%s", result);
    else printf("-1");

    return 0;
}