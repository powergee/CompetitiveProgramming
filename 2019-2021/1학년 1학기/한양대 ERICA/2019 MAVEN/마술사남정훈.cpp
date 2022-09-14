#include <iostream>
using namespace std;

class CardArray
{
private:
    // null문자 포함. (실제 문자는 26개)
    char chArray[27];
    int pos = 0;
    int GetRealIndex(int index);
    void MovePos(int d);
public:
    CardArray();
    void Magic();
};

int M;

int main()
{
    scanf("%d", &M);

    CardArray ca;

    for (int i = 0; i < M; ++i)
        ca.Magic();

    return 0;
}

int CardArray::GetRealIndex(int index)
{
    int result = pos + index;

    if (result < 0)
        result += 26;
    else if (result >= 26)
        result -= 26;

    return result;
}

void CardArray::MovePos(int d)
{
    pos += d;

    if (pos < 0)
        pos += 26;
    else if (pos >= 26)
        pos -= 26;
}

CardArray::CardArray()
{
    scanf("%s", chArray);
}

void CardArray::Magic()
{
    char mName;
    scanf("%c", &mName);

    switch (mName)
    {
        case 'E':
        for (int i = 0; i < 26; ++i)
        {
            switch (chArray[i])
            {
                case 'S':
                chArray[i] = 'C';
                break;

                case 'C':
                chArray[i] = 'S';
                break;
                
                case 'D':
                chArray[i] = 'H';
                break;
                
                case 'H':
                chArray[i] = 'D';
                break;
            }
        }
        break;
        
        case 'R':
        for (int i = 0; i < 26; ++i)
        {
            switch (chArray[i])
            {
                case 'S':
                chArray[i] = 'H';
                break;

                case 'C':
                chArray[i] = 'D';
                break;
                
                case 'D':
                chArray[i] = 'C';
                break;
                
                case 'H':
                chArray[i] = 'S';
                break;
            }
        }
        break;

        case 'G':
        int num1;
        scanf("%d", &num1);
        MovePos(-num1);
        break;

        case 'T':
        int num2;
        char alt;
        scanf("%d %c", &num2, &alt);
        chArray[GetRealIndex(num2 - 1)] = alt;
        break;

        case 'A':
        for (int i = 0; i < 26; ++i)
        {
            printf("%c", chArray[GetRealIndex(pos + i)]);
        }
        printf("\n");
        break;
    }
}