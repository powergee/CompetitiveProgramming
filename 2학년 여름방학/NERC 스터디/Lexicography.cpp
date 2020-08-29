#include <iostream>
#include <algorithm>
#include <cstring>

char letters[1000001];
char answers[1000][1001];
int count[26];

char getMinChar()
{
    static int index = 0;

    while (index < 26)
    {
        if (count[index])
        {
            --count[index];
            return index + 'a';
        }
        else ++index;
    }

    return '-';
}

int main()
{
    int n, l, k;
    
    scanf("%d%d%d%s", &n, &l, &k, letters);
    int length = strlen(letters);

    for (int i = 0; i < length; ++i)
        ++count[letters[i]-'a'];
    
    int ansStart = 0;
    for (int i = 0; i < l; ++i)
    {
        for (int j = ansStart; j < k; ++j)
            answers[j][i] = getMinChar();
        int prevAnsStart = ansStart;
        for (int j = k-1; j >= prevAnsStart; --j)
        {
            if (answers[j][i] == answers[k-1][i])
                ansStart = j;
            else break;
        }
    }

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < l; ++j)
            if (answers[i][j] == 0)
                answers[i][j] = getMinChar();
        printf("%s\n", answers[i]);
    }

    return 0;
}