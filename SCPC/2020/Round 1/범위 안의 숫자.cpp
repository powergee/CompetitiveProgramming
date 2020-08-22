#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <queue>
#include <map>

struct Interval
{
    int leftValue, rightValue;
    int leftIndex, rightIndex;
    int count;
};

int pushDigit(int container, int maxLength, int digit)
{
    static int prevMaxLength = -1;
    static int mod = -1;

    if (prevMaxLength != maxLength)
    {
        prevMaxLength = maxLength;
        mod = (int)(round(pow(10, maxLength-1)));
    }

    return (container % mod) * 10 + digit;
}

int changeDigit(int container, int pos, int newDigit)
{
    int mod = (int)round(pow(10, pos));
    int lower = container % mod;
    int upper = container / (mod*10) * (mod*10);
    int digit = newDigit * mod;
    return upper + digit + lower;
}

std::pair<int, int> findIntervals(std::vector<Interval> intervals, int value)
{
    int left = 0, right = intervals.size() - 1;
    int found = -1;
    while (left < right && found == -1)
    {
        int med = (left + right) / 2;

        if (intervals[med].rightValue < value)
            left = med + 1;
        else if (value < intervals[med].leftValue)
            right = med - 1;
        else
            found = med;
    }

    left = right = found;

    while (0 <= left - 1 && value <= intervals[left - 1].rightValue)
        --left;
    while (right + 1 < (int)intervals.size() && intervals[right + 1].leftValue <= value)
        ++right;

    return {left, right};
}

int main()
{
    int T;
    std::cin >> T;
    for (int t = 1; t <= T; ++t)
    {
        std::cout << "Case #" << t << std::endl;

        std::string input;
        int n, k, m;
        std::cin >> n >> k >> m >> input;

        std::vector<int> parts;
        int current = 0;
        for (int i = 0; i < k; ++i)
            current = pushDigit(current, k, input[i] - '0');
        
        parts.push_back(current);
        for (int i = k; i < n; ++i)
        {
            current = pushDigit(current, k, input[i] - '0');
            parts.push_back(current);
        }

        std::sort(parts.begin(), parts.end());
        std::vector<Interval> intervals;
        std::queue<Interval> measuring;
        int maxCount = 0;

        for (int i = 0; i < (int)parts.size(); ++i)
        {
            while (!measuring.empty() && m < parts[i] - measuring.front().leftValue)
            {
                Interval ended = measuring.front();
                measuring.pop();
                ended.rightValue = parts[i-1];
                ended.rightIndex = i-1;
                ended.count = ended.rightIndex - ended.leftIndex + 1;
                maxCount = std::max(maxCount, ended.count);
                intervals.push_back(ended);
            }

            Interval started;
            started.leftValue = parts[i];
            started.leftIndex = i;
            measuring.push(started);
        }

        while (!measuring.empty())
        {
            Interval ended = measuring.front();
            measuring.pop();
            ended.rightValue = parts.back();
            ended.rightIndex = (int)parts.size() - 1;
            ended.count = ended.rightIndex - ended.leftIndex + 1;
            maxCount = std::max(maxCount, ended.count);
            intervals.push_back(ended);
        }

        for (int i = 0; i < n; ++i)
        {
            if (input[i] == '1')
                continue;
            
            std::map<int, int> backup;
            for (int j = 0; j <= std::min(k-1, i); ++j)
            {
                int partIndex = i-j;
                if (parts.size() <= partIndex)
                    continue;

                int digitPos = k-1-j;
                int newParts = changeDigit(parts[partIndex], digitPos, 1);

                std::pair<int, int> increase = findIntervals(intervals, newParts);
                std::pair<int, int> decrease = findIntervals(intervals, parts[partIndex]);

                for (int itIndex = decrease.first; itIndex <= decrease.second; ++itIndex)
                {
                    if (backup.find(itIndex) == backup.end())
                        backup[itIndex] = intervals[itIndex].count;
                    
                    --intervals[itIndex].count;
                }
                
                for (int itIndex = increase.first; itIndex <= increase.second; ++itIndex)
                {
                    if (backup.find(itIndex) == backup.end())
                        backup[itIndex] = intervals[itIndex].count;
                    
                    ++intervals[itIndex].count;
                    maxCount = std::max(maxCount, intervals[itIndex].count);
                }
            }

            for (auto p : backup)
                intervals[p.first].count = p.second;
        }

        std::cout << maxCount << std::endl;
    }

    return 0;
}