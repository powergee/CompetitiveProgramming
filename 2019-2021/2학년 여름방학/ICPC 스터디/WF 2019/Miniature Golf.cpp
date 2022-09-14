#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cmath>

typedef long long Long;

int main()
{
    int p, h;
    scanf("%d %d", &p, &h);

    std::vector<std::vector<int>> scores(p);

    for (int i = 0; i < p; ++i)
    {
        for (int j = 0; j < h; ++j)
        {
            int s;
            scanf("%d", &s);
            scores[i].push_back(s);
        }

        std::sort(scores[i].begin(), scores[i].end());
    }

    for (int i = 0; i < p; ++i)
    {
        std::vector<std::pair<int, int>> points;

        for (int j = 0; j < p; ++j)
        {
            if (i == j)
                continue;
            
            std::vector<int> pivots;
            for (int s : scores[i])
                pivots.push_back(s);
            for (int s : scores[j])
                pivots.push_back(s);

            std::sort(pivots.begin(), pivots.end());

            std::vector<int> turningPoints;
            bool iIsSmaller = false;
            Long prevIScore, prevJScore;
            int iBound = 0, jBound = 0;
            Long iSum = 0, jSum = 0;
            for (int k = 0; k < (int)pivots.size(); ++k)
            {
                while (iBound != (int)scores[i].size() && scores[i][iBound] <= pivots[k])
                    iSum += scores[i][iBound++];
                Long iScore = iSum + ((Long)scores[i].size() - iBound) * pivots[k];

                while (jBound != (int)scores[j].size() && scores[j][jBound] <= pivots[k])
                    jSum += scores[j][jBound++];
                Long jScore = jSum + ((Long)scores[j].size() - jBound) * pivots[k];

                if ((iScore < jScore) != iIsSmaller)
                {
                    if (iScore == jScore)
                        turningPoints.push_back(pivots[k] - 1);
                    else if (iScore > jScore)
                    {
                        Long nume = (jScore - iScore) * (pivots[k] - pivots[k-1]);
                        Long deno = iScore - jScore - prevIScore + prevJScore;
                        if (nume % deno == 0)
                            turningPoints.push_back((int)(pivots[k] + nume/deno) - 1);
                        else
                            turningPoints.push_back((int)ceil(pivots[k] + (double)nume/deno) - 1);
                    }
                    else if (iScore < jScore)
                    {
                        Long nume = (iScore - jScore) * (pivots[k] - pivots[k-1]);
                        Long deno = jScore - iScore - prevJScore + prevIScore;
                        if (nume % deno == 0)
                            turningPoints.push_back((int)(pivots[k] + nume/deno) + 1);
                        else
                            turningPoints.push_back((int)floor(pivots[k] + (double)nume/deno) + 1);
                    }

                    iIsSmaller = (iScore < jScore);
                }

                prevIScore = iScore;
                prevJScore = jScore;
            }

            int count = (int)turningPoints.size();
            for (int t = 1; t < count; t += 2)
            {
                points.emplace_back(turningPoints[t-1], -1);
                points.emplace_back(turningPoints[t], 1);
            }
            if (count % 2 == 1)
            {
                points.emplace_back(turningPoints.back(), -1);
                points.emplace_back(INT32_MAX, 1);
            }
        }

        std::sort(points.begin(), points.end());

        int maxStack = 0;
        int currStack = 0;
        for (auto point : points)
        {
            currStack -= point.second;
            maxStack = std::max(currStack, maxStack);
        }

        printf("%d\n", p - maxStack);
    }

    return 0;
}