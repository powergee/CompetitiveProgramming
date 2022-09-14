#include <iostream>
#include <vector>
#include <algorithm>

struct Student
{
    int tier;
    std::vector<int> algVec;

    bool operator < (const Student& other)
    {
        return tier < other.tier;
    }
};

int n, k, d;
Student stu[100000];
int known[31];

void FitRight(Student*& left, Student*& right)
{
    while (right != &stu[n - 1] && (right + 1)->tier - left->tier <= d)
    {
        ++right;
        for (int alg : right->algVec)
            ++known[alg];
    }
}

int main()
{
    scanf("%d %d %d", &n, &k, &d);

    for (int i = 0; i < n; ++i)
    {
        int algCount;
        scanf("%d %d", &algCount, &stu[i].tier);
        for (int j = 0; j < algCount; ++j)
        {
            int algNum;
            scanf("%d", &algNum);
            stu[i].algVec.push_back(algNum);
        }
    }

    std::sort(stu, stu + n);
    Student* right = &stu[0];
    for (int alg : right->algVec)
        ++known[alg];
    
    int maxEff = 0;
    for (Student* left = &stu[0]; &stu[n-1] >= left; ++left)
    {
        FitRight(left, right);

        int someKnow = 0, everyKnow = 0;
        int stuCount = (int)(right - left + 1);
        for (int i = 1; i <= k; ++i)
        {
            if (known[i])
            {
                ++someKnow;
                if (known[i] == stuCount)
                    ++everyKnow;
            }
        }
        maxEff = std::max(maxEff, (someKnow - everyKnow) * stuCount);

        for (int alg : left->algVec)
            --known[alg];
    }

    printf("%d", maxEff);

    return 0;
}