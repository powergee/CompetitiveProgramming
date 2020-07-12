#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

typedef long long Long;

Long getFinalScore(int bound, std::vector<int>& scores, std::vector<Long>& sums)
{
    auto biggerIter = std::lower_bound(scores.begin(), scores.end(), bound);
    if (biggerIter == scores.end())
        return sums.back();
    else
    {
        int smallerCount = biggerIter - scores.begin();
        return sums[smallerCount] + (Long)((int)scores.size() - smallerCount) * bound;
    }
}

int main()
{
    //freopen("/home/hyeon/바탕화면/result.txt", "w", stdout);
    int p, h;
    scanf("%d %d", &p, &h);

    std::vector<std::vector<int>> scores(p);
    std::vector<std::vector<Long>> sums(p);

    for (int i = 0; i < p; ++i)
    {
        for (int j = 0; j < h; ++j)
        {
            int s;
            scanf("%d", &s);
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
        //printf("%d번 사람에 대한 정답을 구합니다...\n", i);
        std::vector<std::pair<int, int>> points;

        for (int j = 0; j < p; ++j)
        {
            if (i == j)
                continue;
            
            //printf("%d번 사람과 %d번 사람에 대한 interval을 구합니다.\n", i, j);
            
            std::vector<int> pivots;
            for (int s : scores[i])
                pivots.push_back(s);
            for (int s : scores[j])
                pivots.push_back(s);

            std::sort(pivots.begin(), pivots.end());

            std::vector<int> turningPoints;
            bool iIsSmaller = false;
            //printf("지금부터 turningPoints를 구합니다.\n");
            for (int k = 0; k < (int)pivots.size(); ++k)
            {
                //printf("%lld를 pivot으로 합니다.\n", pivots[k]);
                Long iScore = getFinalScore(pivots[k], scores[i], sums[i]);
                Long jScore = getFinalScore(pivots[k], scores[j], sums[j]);
                //printf("i의 점수: %lld, j의 점수: %lld, 이전 iIsSmaller: %s\n", iScore, jScore, (iIsSmaller ? "true" : "false"));

                if ((iScore < jScore) != iIsSmaller)
                {
                    //printf("이전의 iIsSmaller와 다릅니다.\n");
                    if (iScore == jScore)
                        turningPoints.push_back(pivots[k] - 1);
                    else if (iScore > jScore)
                    {
                        int left = pivots[k-1];
                        int right = pivots[k];

                        while (left+1 < right)
                        {
                            int mid = (left + right) / 2;
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
                        int left = pivots[k-1];
                        int right = pivots[k];

                        while (left < right)
                        {
                            int mid = (left + right) / 2;
                            Long iScoreAtMid = getFinalScore(mid, scores[i], sums[i]);
                            Long jScoreAtMid = getFinalScore(mid, scores[j], sums[j]);
                            
                            if (iScoreAtMid < jScoreAtMid)
                                right = mid;
                            else
                                left = mid + 1;
                        }

                        turningPoints.push_back(left);
                    }

                    //printf("turningPoints에 %lld를 추가했습니다.\n", turningPoints.back());
                    iIsSmaller = (iScore < jScore);
                }
            }

            int count = (int)turningPoints.size();
            //printf("turningPoints의 원소 수는 %d입니다.\n", count);
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

        //printf("%d번 사람에 대한 points의 개수는 %d입니다.\n", i, (int)points.size());
        std::sort(points.begin(), points.end());

        int maxStack = 0;
        int currStack = 0;
        for (auto point : points)
        {
            //printf("{%lld, %d}\n", point.first, -point.second);
            currStack -= point.second;
            maxStack = std::max(currStack, maxStack);
        }

        answer[i] = p - maxStack;
    }

    for (int an : answer)
        printf("%d\n", an);

    return 0;
}