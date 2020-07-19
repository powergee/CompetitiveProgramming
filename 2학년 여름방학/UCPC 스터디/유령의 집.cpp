#include <iostream>

enum Direction {north = 0, south = 1, east = 2, west = 3};

struct Node
{
    Node* next[4];
    
};

int n, m, k, q;

int main()
{
    scanf("%d %d %d %d", &n, &m, &k, &q);

    for (int i = 0; i < k; ++i)
    {
        int x, y;
        char c;
        scanf("%d %d %c", &x, &y, &c);
    }



    return 0;
}