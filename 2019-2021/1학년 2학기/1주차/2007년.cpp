#include <iostream>

int main()
{
    int x, y;
    scanf("%d %d", &x, &y);

    int days = 0;

    for (int i = 1; i < x; ++i)
    {
        switch (i)
        {
        case 4:
        case 6:
        case 9:
        case 11:
            days += 30;
            break;

        case 2:
            days += 28;
            break;
        
        default:
            days += 31;
            break;
        }
    }

    days += y;

    //printf("%d\n", days);

    switch (days % 7)
    {
    case 0:
        printf("SUN");
        break;
    case 1:
        printf("MON");
        break;
    case 2:
        printf("TUE");
        break;
    case 3:
        printf("WED");
        break;
    case 4:
        printf("THU");
        break;
    case 5:
        printf("FRI");
        break;
    case 6:
        printf("SAT");
        break;

    default:
        break;
    }

    return 0;
}