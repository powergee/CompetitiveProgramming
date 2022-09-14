#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::vector<std::pair<bool, int>> markersForType[1000001];
int diffOfScore[1000001];

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;

    for (int i = 1; i <= n; ++i)
    {
        std::string str;
        std::cin >> str;
        bool isStart = str[0] == 's' ? true : false;
        int num = std::stoi(str.substr(1));
        markersForType[num].push_back({isStart, i});
    }

    for (int i = 0; i < 1000001; ++i)
    {
        if (markersForType[i].empty())
            continue;

        int count = 0;
        int minCount = 0;
        for (auto marker : markersForType[i])
        {
            if (marker.first)
                ++count;
            else --count;

            minCount = std::min(minCount, count);
        }

        if (count != 0)
            continue;
        
        for (int j = 0; j < (int)markersForType[i].size(); ++j)
        {
            if (markersForType[i][j].first)
                ++count;
            else --count;

            if (minCount == count)
            {
                ++diffOfScore[markersForType[i][j].second];

                if (j == (int)markersForType[i].size() - 1)
                {
                    ++diffOfScore[0];
                    --diffOfScore[markersForType[i][0].second];
                }
                else --diffOfScore[markersForType[i][j + 1].second];
            }
        }
    }

    int currScore = 0;
    int maxScore = 0, numOfMax = 1;
    for (int i = 0; i < 1000001; ++i)
    {
        if (currScore > maxScore)
        {
            maxScore = currScore;
            numOfMax = i;
        }
        currScore += diffOfScore[i];
    }
    
    std::cout << numOfMax << " " << maxScore;

    return 0;
}