#include <iostream>
#include <algorithm>

typedef long long Long;

class SeqInfo
{
public:
    int Start, Last;

    static SeqInfo Merge(const SeqInfo& s1, const SeqInfo& s2)
    {
        SeqInfo ret;
        ret.Start = std::min(s1.Start, s2.Start);
        ret.Last = std::max(s1.Last, s2.Last);
        return ret;
    }

    int GetLength()
    {
        return Last - Start + 1;
    }
};

Long nums[250001];
Long tree[750001];
Long msTemp[250001];

SeqInfo MergeSort(SeqInfo s1, SeqInfo s2)
{
    int i1 = s1.Start, i2 = s2.Start, pos = 0;
    while (i1 <= s1.Last && i2 <= s2.Last)
    {
        if (nums[i1] > nums[i2])
            msTemp[pos++] = nums[i2++];
        else msTemp[pos++] = nums[i1++];
    }

    while (i1 <= s1.Last)
        msTemp[pos++] = nums[i1++];

    while (i2 <= s2.Last)
        msTemp[pos++] = nums[i2++];

    SeqInfo mergedInfo = SeqInfo::Merge(s1, s2);

    std::copy(msTemp, msTemp + mergedInfo.GetLength(), nums + std::min(s1.Start, s2.Start));
    return mergedInfo;
}

SeqInfo Init(int node, int start, int end)
{
    if (start == end)
    {
        tree[node] = nums[start];
        return {start, end};
    }

    SeqInfo left = Init(node * 2, start, (start + end) / 2);
    SeqInfo right = Init(node * 2 + 1, (start + end) / 2 + 1, end);

    SeqInfo merged = MergeSort(left, right);
    tree[node] = nums[merged.Last];

    return merged;
}

Long QueryMax(int index, int nodeStart, int nodeEnd, int reqStart, int reqEnd)
{
    int nodeMed = (nodeStart + nodeEnd) / 2;

    if (nodeStart > reqEnd || nodeEnd < reqStart)
        return -1;

    else if (nodeStart == reqStart && nodeEnd == reqEnd)
        return tree[index];

    else if (nodeMed >= reqEnd)
        return QueryMax(index * 2, nodeStart, nodeMed, reqStart, reqEnd);
    
    else if (nodeMed + 1 <= reqStart)
        return QueryMax(index * 2 + 1, nodeMed + 1, nodeEnd, reqStart, reqEnd);

    else
        return std::max(QueryMax(index * 2, nodeStart, nodeMed, reqStart, nodeMed), QueryMax(index * 2 + 1, nodeMed + 1, nodeEnd, nodeMed + 1, reqEnd));
}

Long FindMed(int start, int end)
{
    return QueryMax(1, 1, N, start, (start + end) / 2, );
}

int main()
{
    int N, K;
    scanf("%d %d", &N, &K);

    for (int i = 1; i <= N; ++i)
    {
        scanf("%lld", &nums[i]);
    }



    return 0;
}