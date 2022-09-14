#include <iostream>

int N, r, c;

int Calc(int rStart, int rEnd, int cStart, int cEnd)
{
    int rLen = rEnd - rStart + 1;
    int cLen = cEnd - cStart + 1;

    if (rLen == 1 && cLen == 1)
        return 0;

    if (rStart <= r && r <= rStart + rLen / 2 - 1 &&
        cStart <= c && c <= cStart + cLen / 2 - 1)
        return Calc(rStart, rStart + rLen / 2 - 1, cStart, cStart + cLen / 2 - 1);

    if (rStart <= r && r <= rStart + rLen / 2 - 1 &&
        cStart + cLen / 2 <= c && c <= cEnd)
        return (rLen / 2) * (cLen / 2) + Calc(rStart, rStart + rLen / 2 - 1, cStart + cLen / 2, cEnd);
    
    if (rStart + rLen / 2 <= r && r <= rEnd &&
        cStart <= c && c <= cStart + cLen / 2 - 1)
        return 2 * (rLen / 2) * (cLen / 2) + Calc(rStart + rLen / 2, rEnd, cStart, cStart + cLen / 2 - 1);

    return 3 * (rLen / 2) * (cLen / 2) + Calc(rStart + rLen / 2, rEnd, cStart + cLen / 2, cEnd);
}

int main()
{
    scanf("%d %d %d", &N, &r, &c);
    printf("%d", Calc(0, (1 << N) - 1, 0, (1 << N) - 1));

    return 0;
}