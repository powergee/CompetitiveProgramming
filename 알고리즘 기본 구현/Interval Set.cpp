#include <iostream>
#include <string>
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
    Long findGaps(Long s, Long e)
    {
        auto sIt = find(s);
        auto eIt = find(e);

        if (sIt == iSet.end() && eIt == iSet.end())
        {
            sIt = findToRight(s);
            eIt = findToLeft(e);
            if (sIt == iSet.end() || eIt == iSet.end())
                return e - s;
            else if (eIt->second < sIt->first)
                return e - s;
            else
            {
                Long dist = (sIt->first - s) + (e - eIt->second);
                for (auto it = sIt; it != eIt; ++it)
                {
                    auto next = std::next(it);
                    dist += next->first - it->second;
                }
                return dist;
            }
        }

        else if (sIt == iSet.end())
        {
            sIt = findToRight(s);
            Long dist = sIt->first - s;
            for (auto it = sIt; it != eIt; ++it)
            {
                auto next = std::next(it);
                dist += next->first - it->second;
            }
            return dist;
        }

        else if (eIt == iSet.end())
        {
            eIt = findToLeft(e);
            Long dist = e - eIt->second;
            for (auto it = sIt; it != eIt; ++it)
            {
                auto next = std::next(it);
                dist += next->first - it->second;
            }
            return dist;
        }

        else
        {
            Long dist = 0;
            for (auto it = sIt; it != eIt; ++it)
            {
                auto next = std::next(it);
                dist += next->first - it->second;
            }
            return dist;
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

int main()
{
    IntervalSet is;
    while (true)
    {
        std::string com;
        std::cin >> com;

        if (com == "add")
        {
            Long s, e;
            std::cin >> s >> e;
            is.addInterval(s, e);
            is.printAll();
        }

        else if (com == "gap")
        {
            Long s, e;
            std::cin >> s >> e;
            std::cout << is.findGaps(s, e) << "\n";
        }

        else if (com == "find")
        {
            Long pos;
            std::cin >> pos;
            auto found = is.findInterval(pos);
            if (found.first == LLONG_MAX)
                std::cout << "Not Found\n";
            else
                printf("(%lld, %lld)\n", found.first, found.second);
        }
    }

    return 0;
}