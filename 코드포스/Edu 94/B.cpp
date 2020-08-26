#include <iostream>
#include <algorithm>
#include <climits>

typedef long long Long;
int p, f, sCount, wCount, sWeight, wWeight;

bool possibleToCarry(int count)
{
    int sUsed, wUsed;
    if (sWeight < wWeight)
    {
        sUsed = std::min(sCount, count);
        wUsed = count - sUsed;
        
        Long minExtra = LLONG_MAX;
        int sofp = 0, wofp = 0;
        for (int i = 0; i <= sUsed; ++i)
        {
            Long sw = i * sWeight;
            if (sw > (Long)p)
                break;
            
            Long wNeed = std::min((p - sw) / wWeight, (Long)wUsed);
            Long extra = p - sw - wNeed * wWeight;
            if (extra >= 0 && minExtra > extra)
            {
                sofp = i;
                wofp = (int)wNeed;
                minExtra = extra;
            }
        }

        int soff = sUsed - sofp;
        int woff = wUsed - wofp;
        return (Long)f >= (Long)soff * sWeight + (Long)woff * wWeight;
    }
    else
    {
        wUsed = std::min(wCount, count);
        sUsed = count - wUsed;

        Long minExtra = LLONG_MAX;
        int sofp = 0, wofp = 0;
        for (int i = 0; i <= wUsed; ++i)
        {
            Long ww = i * wWeight;
            if (ww > (Long)p)
                break;
            
            Long sNeed = std::min((p - ww) / sWeight, (Long)sUsed);
            Long extra = p - ww - sNeed * sWeight;
            if (extra >= 0 && minExtra > extra)
            {
                wofp = i;
                sofp = (int)sNeed;
                minExtra = extra;
            }
        }

        int soff = sUsed - sofp;
        int woff = wUsed - wofp;
        return (Long)f >= (Long)soff * sWeight + (Long)woff * wWeight;
    }
}

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        scanf("%d%d%d%d%d%d", &p, &f, &sCount, &wCount, &sWeight, &wWeight);

        int left = 0, right = sCount+wCount+1;
        while (left+1 < right)
        {
            int med = (left+right)/2;
            if (possibleToCarry(med))
                left = med;
            else right = med;
        }

        printf("%d\n", left);
    }

    return 0;
}