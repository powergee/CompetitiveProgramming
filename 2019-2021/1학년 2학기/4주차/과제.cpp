#include <iostream>
#include <vector>
#include <algorithm>

std::vector<std::pair<int, int>> assign;
bool schedule[1000];

int compare(const std::pair<int, int>& p1, const std::pair<int, int>& p2)
{
    if (p1.second == p2.second)
        return p1.first < p2.first;
    else return p1.second > p2.second;
}

int main()
{
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i)
    {
        int d, w;
        scanf("%d %d", &d, &w);

        assign.push_back({d, w});
    }

    std::sort(assign.begin(), assign.end(), compare);

    int score = 0;
    for (int i = 0; i < assign.size(); ++i)
    {
        auto& now = assign[i];

        for (int j = now.first - 1; j >= 0; --j)
        {
            if (!schedule[j])
            {
                schedule[j] = true;
                score += now.second;
                break;
            }
        }
    }

    printf("%d", score);

    return 0;
}