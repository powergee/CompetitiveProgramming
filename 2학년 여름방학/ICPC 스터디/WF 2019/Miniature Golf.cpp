#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

typedef long long Long;

Long getFinalScore(Long bound, std::vector<Long>& scores, std::vector<Long>& sums)
{
    auto biggerIter = std::lower_bound(scores.begin(), scores.end(), bound);
    if (biggerIter == scores.end())
        return sums.back();
    else
    {
        int smallerCount = scores.end() - biggerIter;
        return sums[smallerCount] + ((int)scores.size() - smallerCount) * bound;
    }
}

int main()
{
    int p, h;
    scanf("%d %d", &p, &h);

    std::vector<std::vector<Long>> scores(p);
    std::vector<std::vector<Long>> sums(p);

    for (int i = 0; i < p; ++i)
    {
        for (int j = 0; j < h; ++j)
        {
            Long s;
            scanf("%lld", &s);
            scores[i].push_back(s);
        }

        std::sort(scores[i].begin(), scores[i].end());

        Long sum = 0;
        for (int j = 0; j <= h; ++j)
        {
            sums[i].push_back(sum);
            if (j != h)
                sum += scores[i][j];
        }
    }

    std::vector<int> answer(p);

    for (int i = 0; i < p; ++i)
    {
        std::vector<std::pair<Long, Long>> intervals;

        for (int j = 0; j < p; ++j)
        {
            if (i == j)
                continue;
            
            std::vector<Long> pivots;
            for (Long s : scores[i])
                pivots.push_back(s);
            for (Long s : scores[j])
                pivots.push_back(s);

            std::sort(pivots.begin(), pivots.end());

            std::vector<Long> turningPoints;
            bool iIsSmaller = false;
            for (int k = 0; k < (int)pivots.size(); ++k)
            {
                Long iScore = getFinalScore(pivots[k], scores[i], sums[i]);
                Long jScore = getFinalScore(pivots[k], scores[j], sums[j]);

                if ((iScore < jScore) != iIsSmaller)
                {
                    if (iScore == jScore)
                        turningPoints.push_back(pivots[k] - 1);
                    else if (iScore > jScore)
                    {
                        Long left = pivots[k-1];
                        Long right = pivots[k];

                        while (left+1 < right)
                        {
                            Long mid = (left + right) / 2;
                            Long iScoreAtMid = getFinalScore(mid, scores[i], sums[i]);
                            Long jScoreAtMid = getFinalScore(mid, scores[j], sums[j]);
                            
                            if (iScoreAtMid < jScoreAtMid)
                                left = mid;
                            else
                                right = mid - 1;
                        }

                        turningPoints.push_back(left);
                    }
                    else if (iScore < jScore)
                    {
                        Long left = pivots[k-1];
                        Long right = pivots[k];

                        while (left < right)
                        {
                            Long mid = (left + right) / 2;
                            Long iScoreAtMid = getFinalScore(mid, scores[i], sums[i]);
                            Long jScoreAtMid = getFinalScore(mid, scores[j], sums[j]);
                            
                            if (iScoreAtMid < jScoreAtMid)
                                right = mid;
                            else
                                left = mid + 1;
                        }

                        turningPoints.push_back(left);
                    }

                    iIsSmaller = (iScore < jScore);
                }
            }

            int count = (int)turningPoints.size();
            if (count == 1)
                intervals.emplace_back(1, INT32_MAX);
            else if (count == 2)
                intervals.emplace_back(turningPoints.front(), turningPoints.back());
        }

        std::vector<std::pair<Long, int>> points;
        for (int i = 0; i < (int)intervals.size(); ++i)
        {
            points.emplace_back(intervals[i].first, 1);
            points.emplace_back(intervals[i].second, -1);
        }
        std::sort(points.begin(), points.end());

        int maxStack = 0;
        int currStack = 0;
        for (auto point : points)
        {
            currStack += point.second;
            maxStack = std::max(currStack, maxStack);
        }

        answer[i] = p - maxStack;
    }

    for (int an : answer)
        printf("%d\n", an);

    return 0;
}