#include <iostream>
#include <algorithm>
using namespace std;

int aCount = 0, bCount = 0, cCount = 0;
int length;
char result[51];
bool isChecked[51][51][51][51][4][4];

// 해당 날짜에 그 사람이 일할수 있는가? && 이전에 체크했던 경우가 아닌가?
bool IsPossible(char ch, int pos, bool** checkedArr)
{
    for (int i = 0; i < 2; ++i)
    {
        int canWork;
        if (pos - i < 0)
            canWork = -1;
        else
        {
            if (result[pos - i] == ch)
                canWork = 0;
            else canWork = result[pos - i];
        }
    
        switch (canWork)
        {
            case -1:
                checkedArr[i][0] = true;
                return !checkedArr[0];

            case 0:
                return false; 
    
            default:
                checkedArr[i][canWork - 'A' + 1];
                return !checkedArr[canWork - 'A' + 1];
        }
    }
}

bool Find(int pos, int aRemain, int bRemain, int cRemain)
{
    if (pos >= length)
        return true;

    bool** checkedArr = (bool**)isChecked[pos][aRemain][bRemain][cRemain];

    // A가 출근할 경우
    if (aRemain > 0)
    {
        result[pos] = 'A';
        if (Find(pos + 1, aRemain - 1, bRemain, cRemain))
            return true;
        else result[pos] = '\0';
    }

    // B가 출근할 경우
    if (bRemain > 0 && IsPossible('B', pos, checkedArr))
    {
        result[pos] = 'B';
        if (Find(pos + 1, aRemain, bRemain - 1, cRemain))
            return true;
        else result[pos] = '\0';
    }

    // C가 출근할 경우
    if (cRemain > 0 && IsPossible('C', pos, checkedArr) && IsPossible('C', pos, checkedArr))
    {
        result[pos] = 'C';
        if (Find(pos + 1, aRemain, bRemain, cRemain - 1))
            return true;
        else result[pos] = '\0';
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
    fill(&isChecked[0][0][0][0][0], &isChecked[0][0][0][0][0] + sizeof(isChecked) / sizeof(bool), false);

    if (Find(0, aCount, bCount, cCount))
        printf("%s", result);
    else printf("-1");

    return 0;
}