#include <iostream>

char lines[5][16];

inline bool IsValid(char ch)
{
    return ('A'<=ch && ch<='Z') || ('a'<=ch && ch<='z') || ('0'<=ch && ch<='9');
}

int main()
{
    for (int i = 0; i < 5; ++i)
        scanf("%s", lines[i]);

    for (int col = 0; col < 16; ++col)
        for (int row = 0; row < 5; ++row)
            if (IsValid(lines[row][col]))
                printf("%c", lines[row][col]);

    return 0;
}