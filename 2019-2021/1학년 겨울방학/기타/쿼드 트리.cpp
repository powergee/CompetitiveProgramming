#include <iostream>
#include <string>

int N;
bool image[64][64];

void Compress(int rStart, int rEnd, int cStart, int cEnd)
{
    bool allSame = true;
    for (int row = rStart; row <= rEnd; ++row)
    {
        for (int col = cStart; col <= cEnd; ++col)
        {
            if (image[rStart][cStart] != image[row][col])
            {
                allSame = false;
                goto BREAK_ALL;
            }
        }
    } BREAK_ALL:

    if (allSame)
        printf("%d", image[rStart][cStart] ? 1 : 0);
    else
    {
        printf("(");
        int rMed = (rStart + rEnd) / 2;
        int cMed = (cStart + cEnd) / 2;
        Compress(rStart, rMed, cStart, cMed);
        Compress(rStart, rMed, cMed + 1, cEnd);
        Compress(rMed + 1, rEnd, cStart, cMed);
        Compress(rMed + 1, rEnd, cMed + 1, cEnd);
        printf(")");
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::cin >> N;
    for (int row = 0; row < N; ++row)
    {
        std::string str;
        std::cin >> str;
        for (int col = 0; col < N; ++col)
            image[row][col] = str[col] == '1';
    }

    Compress(0, N - 1, 0, N - 1);

    return 0;
}