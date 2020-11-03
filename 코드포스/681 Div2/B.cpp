#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--)
    {
        int a, b;
        std::string map;
        std::cin >> a >> b >> map;

        int length = map.size();
        bool inInterval = false;
        int interLength = 0;
        int start = map.find('1');
        std::vector<int> intervals;

        if (start == std::string::npos)
        {
            std::cout << "0\n";
        }
        else
        {
            for (int i = start; i < length; ++i)
            {
                if (map[i] == '1')
                {
                    if (inInterval)
                    {
                        inInterval = false;
                        intervals.push_back(interLength);
                    }
                    interLength = 0;
                }
                else
                {
                    if (!inInterval)
                        inInterval = true;
                    
                    ++interLength;
                }
            }

            std::sort(intervals.begin(), intervals.end());
            long long nodeCount = (long long)intervals.size() + 1;
            long long answer = a * nodeCount;
            long long distSum = 0;
            int interCount = 0;
            for (int ele : intervals)
            {
                distSum += ele;
                ++interCount;
                answer = std::min(answer, b * distSum + a * (nodeCount - interCount));
            }
            std::cout << answer << "\n";
        }
    }
}