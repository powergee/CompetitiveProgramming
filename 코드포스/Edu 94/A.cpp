#include <iostream>
#include <algorithm>

char str[100];
char answer[51];

int main()
{
    int T;
    scanf("%d", &T);

    for (int t = 0; t < T; ++t)
    {
        int n;
        scanf("%d%s", &n, str);

        std::fill(answer, answer+n+1, 0);
        for (int i = 0; i < n; ++i)
            answer[i] = str[2*i];
        
        printf("%s\n", answer);
    }

    return 0;
}