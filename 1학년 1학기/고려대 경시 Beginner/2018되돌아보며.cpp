#include <iostream>
using namespace std;

int main ()
{
    char str[11];

    scanf("%s", str);
    
    int n2 = 0, n0 = 0, n1 = 0, n8 = 0;

    for (int i = 0;; ++i)
    {
        if (str[i] == '\0')
            break;

        switch (str[i])
        {
        case '2':
            ++n2;
            break;
        case '0':
            ++n0;
            break;
        case '1':
            ++n1;
            break;
        case '8':
            ++n8;
            break;
        default:
            // 관련없는 수
            printf("0");
            return 0;
        }
    }

    // 관련있는 수
    if (n2 || n0 || n1 || n8)
    {
        // 밀접한 수
        if (n2 && n0 && n1 && n8)
        {
            if (n2 == n0 && n0 == n1 && n1 == n8)
                printf("8");
            else printf("2");
        }
        else printf("1");
    }

    return 0;
}