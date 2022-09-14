#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

typedef long long Long;

template<typename T>
class SegTree
{
private:
    int count;
    std::vector<T> nodes;

    T initialize(int index, int start, int end, const std::vector<T>& original)
    {
        if (start == end)
            return nodes[index] = original[start];
        
        int mid = (start + end) / 2;
        T left = initialize(index * 2, start, mid, original);
        T right = initialize(index * 2 + 1, mid + 1, end, original);

        return nodes[index] = left + right;
    }

    T query(int index, int nodeStart, int nodeEnd, int reqStart, int reqEnd)
    {
        int nodeMid = (nodeStart + nodeEnd) / 2;

        if (reqEnd < nodeStart || nodeEnd < reqStart)
            return 0;
        else if (reqStart <= nodeStart && nodeEnd <= reqEnd)
            return nodes[index];
        else
        {
            T left = query(index * 2, nodeStart, nodeMid, reqStart, reqEnd);
            T right = query(index * 2 + 1, nodeMid + 1, nodeEnd, reqStart, reqEnd);
            return left + right;
        }
    }

    void update(int index, int nodeStart, int nodeEnd, int reqIndex, T newVal)
    {
        int nodeMid = (nodeStart + nodeEnd) / 2;

        if (nodeStart == nodeEnd)
            nodes[index] = newVal;
        else
        {
            if (reqIndex <= nodeMid)
                update(index * 2, nodeStart, nodeMid, reqIndex, newVal);
            else
                update(index * 2 + 1, nodeMid + 1, nodeEnd, reqIndex, newVal);
            nodes[index] = nodes[index * 2] + nodes[index * 2 + 1];
        }
    }
    
public:
    SegTree(const std::vector<T>& original)
    {
        count = (int)original.size();
        int treeHeight = (int)ceil(log2(count));
        int vecSize = (1 << (treeHeight + 1));
        nodes.resize(vecSize);
        initialize(1, 0, count - 1, original);
    }

    SegTree(int size)
    {
        count = size;
        int treeHeight = (int)ceil(log2(count));
        int vecSize = (1 << (treeHeight + 1));
        nodes.resize(vecSize);
    }

    T query(int start, int end)
    {
        return query(1, 0, count - 1, start, end);
    }

    void update(int index, T newVal)
    {
        update(1, 0, count - 1, index, newVal);
    }
};

int main()
{
    int n;
    scanf("%d", &n);

    std::vector<std::pair<Long, int>> jobs;
    for (int i = 0; i < n; ++i)
    {
        int time;
        scanf("%d", &time);
        jobs.emplace_back(time, i);
    }

    SegTree<Long> shortJobs(n), longJobs(std::vector<Long>(n, 1));
    std::sort(jobs.begin(), jobs.end());
    
    std::vector<Long> answer(n, 0);
    for (int i = 0; i < n; ++i)
    {
        if (jobs[i].second > 0)
            answer[jobs[i].second] += shortJobs.query(0, jobs[i].second - 1) + longJobs.query(0, jobs[i].second - 1) * jobs[i].first;
        if (jobs[i].second < n-1)
            answer[jobs[i].second] += shortJobs.query(jobs[i].second + 1, n-1) + longJobs.query(jobs[i].second + 1, n-1) * (jobs[i].first-1);
        answer[jobs[i].second] += jobs[i].first;

        longJobs.update(jobs[i].second, 0);
        shortJobs.update(jobs[i].second, jobs[i].first);
    }

    for (int i = 0; i < n; ++i)
        printf("%lld\n", answer[i]);

    return 0;
}