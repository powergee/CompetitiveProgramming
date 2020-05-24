#include <iostream>
#include <algorithm>
using namespace std;

int memo[61][61][61];
int scvs[3];
const int UNDEFINED = 987654321;

int Process(int s1, int s2, int s3, int damage = 9)
{
    if (s1 <= 0 && s2 <= 0 && s3 <= 0)
        return 0;

    int& ret = memo[s1][s2][s3];
    if (ret != UNDEFINED)
        return ret;

    if (damage > 1)
    {
        if (s1 > 0)
            ret = min(ret, Process(s1 - damage, s2, s3, damage / 3) + 1);
        if (s2 > 0)
            ret = min(ret, Process(s1, s2 - damage, s3, damage / 3) + 1);
        if (s3 > 0)
            ret = min(ret, Process(s1, s2, s3 - damage, damage / 3) + 1);
    }

    else
    {

    }
    
}

int main()
{
    int count;
    scanf("%d", &count);
    fill(&memo[0][0][0], &memo[0][0][0] + sizeof(memo) / sizeof(int), UNDEFINED);

    switch (count)
    {
    case 1:
        scanf("%d", &scvs[0]);
        printf("%d", scvs[0] / 9 + (scvs[0] % 9 == 0 ? 0 : 1));
        break;

    case 2:
        scanf("%d %d", &scvs[0], &scvs[1]);
        printf("%d", Process(scvs[0], scvs[1], scvs[2]));
        break;

    case 3:
        scanf("%d %d %d", &scvs[0], &scvs[1], &scvs[2]);
        printf("%d", Process(scvs[0], scvs[1], scvs[2]));
    }
    return 0;
}