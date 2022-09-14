#include <iostream>

int n;
int heights[50];
double slopes[50][50];

int main()
{
    scanf("%d", &n);

    for (int i = 0; i < n; ++i)
        scanf("%d", heights+i);
    
    for (int i = 0; i < n; ++i)
        for (int j = i+1; j < n; ++j)
            slopes[i][j] = ((double)heights[j]-heights[i])/(j-i);
    
    int answer = 0;
    
    for (int c = 0; c < n; ++c)
    {
        double leftSlope = 2000000000, rightSlope = -2000000001;
        int current = 0;
        for (int i = c-1; i >= 0; --i)
        {
            if (slopes[i][c] < leftSlope)
            {
                ++current;
                leftSlope = slopes[i][c];
            }
        }

        for (int i = c+1; i < n; ++i)
        {
            if (rightSlope < slopes[c][i])
            {
                ++current;
                rightSlope = slopes[c][i];
            }
        }

        if (answer < current)
            answer = current;
    }

    printf("%d", answer);

    return 0;
}