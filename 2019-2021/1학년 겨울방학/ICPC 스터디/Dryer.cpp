#include <iostream>
#include <algorithm>
#include <vector>

int T_ToCompare = 0;
struct Clothes
{
    int t, w;

    Clothes()
    {
        t = w = 0;
    }

    Clothes(int t, int w)
    {
        this->t = t;
        this->w = w;
    }

    int GetTime(int T) const
    {
        return 30 + (t - T) * w;
    }
};

// t 값에 따라 정렬. 즉, y=30과의 교점의 x값에 따라 정렬.
bool CompareTemp(const Clothes& c1, const Clothes& c2)
{
    return c1.t < c2.t;
}

// GetTime(T_ToCompare) 값에 따라 정렬.
bool CompareTime(const Clothes& c1, const Clothes& c2)
{
    return c1.GetTime(T_ToCompare) < c2.GetTime(T_ToCompare);
}

std::vector<Clothes> clVec;
int n, k;

int GetMinTemp(int left, int right)
{
    if (right < left)
        return 0;

    int minTemp = 0x7fffffff;
    for (int i = left; i <= right; ++i)
        minTemp = std::min(minTemp, clVec[i].t);

    return minTemp;
}

int GetMaxTime(int left, int right, int temp)
{
    if (right < left)
        return 0;

    int maxTime = -1;
    for (int i = left; i <= right; ++i)
        maxTime = std::max(maxTime, clVec[i].GetTime(temp));

    return maxTime;
}

int Calc(int currK, int left, int right)
{
    if (right < left)
        return 987654321;

    if (currK == 1)
    {
        return GetMaxTime(left, right, GetMinTemp(left, right));
    }
    else
    {
        int temp = GetMinTemp(left, right);
        int minTime = Calc(currK - 1, left, right);
        for (int last = left; last <= right; ++last)
        {
            T_ToCompare = temp;
            std::sort(clVec.begin() + left, clVec.begin() + right + 1, CompareTime);

            minTime = std::min(minTime, GetMaxTime(left, last, temp) + Calc(currK - 1, last + 1, right));
        }

        return minTime;
    }
}

int main()
{
    scanf("%d %d", &n, &k);

    for (int i = 0; i < n; ++i)
    {
        int t, w;
        scanf("%d %d", &t, &w);

        int vecIndex = 0;
        for (Clothes& cl : clVec)
        {
            if (cl.t == t)
                break;

            ++vecIndex;
        }

        if (vecIndex == clVec.size())
            clVec.push_back(Clothes(t, w));
        else
            clVec[vecIndex].w = std::max(w, clVec[vecIndex].w);
    }

    printf("%d", Calc(k, 0, clVec.size() - 1));

    return 0;
}