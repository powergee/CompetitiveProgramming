#include <iostream>
#define LEFT (1)
#define RIGHT (-1)

enum Direction { North, South, East, West };

Direction dir = East;
int north = 0, south = 0, east = 0, west = 0;
int x = 0, y = 0;

int main()
{
    int n;
    scanf("%d", &n);
    
    while (n--)
    {
        int length, turn;
        scanf("%d %d", &length, &turn);

        switch (dir)
        {
        case North:
            printf("%d ", (north + 1) - y);
            y = ++north;

            if (turn == LEFT)
                dir = West;
            else dir = East;
            break;

        case South:
            printf("%d ", y - (south - 1));
            y = --south;

            if (turn == LEFT)
                dir = East;
            else dir = West;
            break;

        case East:
            printf("%d ", (east + 1) - x);
            x = ++east;

            if (turn == LEFT)
                dir = North;
            else dir = South;
            break;

        case West:
            printf("%d ", x - (west - 1));
            x = --west;

            if (turn == LEFT)
                dir = South;
            else dir = North;
            break;
        }
    }

    return 0;
}