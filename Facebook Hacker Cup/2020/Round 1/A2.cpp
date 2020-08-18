#include <iostream>
#include <climits>
#include <set>

typedef long long Long;

struct IntervalComp
{
    bool operator()(const std::pair<Long, Long>& i1, const std::pair<Long, Long>& i2) const
    {
        if (i1.second < i2.first || i2.second < i1.first)
            return i1.first < i2.first;
        return false;
    }
};

class IntervalSet
{
private:
    std::set<std::pair<Long, Long>, IntervalComp> iSet;

    std::set<std::pair<Long, Long>, IntervalComp>::iterator find(Long pos)
    {
        if (iSet.empty())
            return iSet.end();

        auto found = iSet.lower_bound({pos, pos});
        if (found != iSet.end() && found->first <= pos && pos <= found->second)
            return found;
        else return iSet.end();
    }

    std::set<std::pair<Long, Long>, IntervalComp>::iterator findToRight(Long pos)
    {
        if (iSet.empty())
            return iSet.end();

        return iSet.lower_bound({pos, pos});
    }

    std::set<std::pair<Long, Long>, IntervalComp>::iterator findToLeft(Long pos)
    {
        if (iSet.empty())
            return iSet.end();

        auto right = findToRight(pos);
        if (right == iSet.begin() && pos < right->first)
            return iSet.end();
        else if (right == iSet.end() || pos < right->first)
            return std::prev(right);
        
        return right;
    }

public:
    // 사이 공백의 길이, 사이에 놓여있거나 걸쳐있는 구간 객체의 개수
    std::pair<Long, int> findGaps(Long s, Long e)
    {
        auto sIt = find(s);
        auto eIt = find(e);

        if (sIt == iSet.end() && eIt == iSet.end())
        {
            sIt = findToRight(s);
            eIt = findToLeft(e);
            if (sIt == iSet.end() || eIt == iSet.end())
                return {e - s, 0};
            else if (eIt->second < sIt->first)
                return {e - s, 0};
            else
            {
                Long dist = (sIt->first - s) + (e - eIt->second);
                int count = 1;
                for (auto it = sIt; it != eIt; ++it)
                {
                    auto next = std::next(it);
                    dist += next->first - it->second;
                    ++count;
                }
                return {dist, count};
            }
        }

        else if (sIt == iSet.end())
        {
            sIt = findToRight(s);
            Long dist = sIt->first - s;
            int count = 1;
            for (auto it = sIt; it != eIt; ++it)
            {
                auto next = std::next(it);
                dist += next->first - it->second;
                ++count;
            }
            return {dist, count};
        }

        else if (eIt == iSet.end())
        {
            eIt = findToLeft(e);
            Long dist = e - eIt->second;
            int count = 1;
            for (auto it = sIt; it != eIt; ++it)
            {
                auto next = std::next(it);
                dist += next->first - it->second;
                ++count;
            }
            return {dist, count};
        }

        else
        {
            Long dist = 0;
            int count = 1;
            for (auto it = sIt; it != eIt; ++it)
            {
                auto next = std::next(it);
                dist += next->first - it->second;
                ++count;
            }
            return {dist, count};
        }
    }

    void addInterval(Long s, Long e)
    {
        auto sIt = find(s);
        auto eIt = find(e);

        if (sIt == iSet.end() && eIt == iSet.end())
        {
            sIt = findToRight(s);
            eIt = findToLeft(e);
            if (sIt == iSet.end() || eIt == iSet.end())
                iSet.emplace(s, e);
            else if (eIt->second < sIt->first)
                iSet.emplace(s, e);
            else
            {
                iSet.erase(sIt, std::next(eIt));
                iSet.emplace(s, e);
            }
        }

        else if (sIt == iSet.end())
        {
            Long newE = eIt->second;
            sIt = findToRight(s);
            iSet.erase(sIt, std::next(eIt));
            iSet.emplace(s, newE);
        }

        else if (eIt == iSet.end())
        {
            Long newS = sIt->first;
            eIt = findToLeft(e);
            iSet.erase(sIt, std::next(eIt));
            iSet.emplace(newS, e);
        }

        else
        {
            Long newS = sIt->first;
            Long newE = eIt->second;
            iSet.erase(sIt, std::next(eIt));
            iSet.emplace(newS, newE);
        }
    }

    std::pair<Long, Long> findInterval(Long pos)
    {
        auto found = find(pos);
        if (found == iSet.end())
            return {LLONG_MAX, LLONG_MIN};
        return *found;
    }

    void printAll()
    {
        for (auto interval : iSet)
            printf("(%lld, %lld) ", interval.first, interval.second);
        printf("\n");
    }
};

int n, k;
Long a, b, c, d;
Long W[1000000];
Long H[1000000];
Long L[1000000];
const Long MOD = 1000000007;

int main()
{
    freopen("/home/hyeon/다운로드/perimetric_chapter_2_input.txt", "r", stdin);
    freopen("/home/hyeon/다운로드/output.txt", "w", stdout);
    int T;
    scanf("%d", &T);

    for (int t = 1; t <= T; ++t)
    {
        Long a, b, c, d;
        scanf("%d %d", &n, &k);

        for (int i = 0; i < k; ++i)
            scanf("%lld", L+i);
        
        scanf("%lld %lld %lld %lld", &a, &b, &c, &d);
        for (int i = k; i < n; ++i)
            L[i] = (a*L[i-2] + b*L[i-1] + c) % d + 1;

        for (int i = 0; i < k; ++i)
            scanf("%lld", W+i);

        scanf("%lld %lld %lld %lld", &a, &b, &c, &d);
        for (int i = k; i < n; ++i)
            W[i] = (a*W[i-2] + b*W[i-1] + c) % d + 1;
        
        for (int i = 0; i < k; ++i)
            scanf("%lld", H+i);

        scanf("%lld %lld %lld %lld", &a, &b, &c, &d);
        for (int i = k; i < n; ++i)
            H[i] = (a*H[i-2] + b*H[i-1] + c) % d + 1;
        
        Long result = 1;
        Long periSum = 0;
        IntervalSet is;

        for (int i = 0; i < n; ++i)
        {
            Long s = L[i];
            Long e = L[i]+W[i];
            auto gap = is.findGaps(s, e);
            Long current = 2*gap.first - ((Long)gap.second-1)*2LL*H[i];
            
            is.addInterval(s, e);
            periSum = (periSum + current) % MOD;
            result = (result * periSum) % MOD;
            //printf("[%d]: %lld\n", i, periSum);

            //is.printAll();
        }

        printf("Case #%d: %lld\n", t, result);
    }
}