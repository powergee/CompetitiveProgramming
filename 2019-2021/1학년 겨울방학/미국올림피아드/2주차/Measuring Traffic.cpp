#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>

enum SegType { None, On, Off };

struct Segment
{
    int MinFlow, MaxFlow;
    SegType Type;

    Segment(int minFlow, int maxFlow, SegType type)
        : MinFlow(minFlow), MaxFlow(maxFlow), Type(type) { }
};

int n;
std::vector<Segment> segs;
std::vector<int> nonePos;

void AddNone(std::vector<Segment>& noneSegs)
{
    if (noneSegs.empty())
        return;

    int minFlow = INT32_MIN, maxFlow = INT32_MAX;
    for (Segment& seg : noneSegs)
    {
        minFlow = std::max(minFlow, seg.MinFlow);
        maxFlow = std::min(maxFlow, seg.MaxFlow);
    }

    noneSegs.clear();
    nonePos.push_back(segs.size());
    segs.push_back(Segment(minFlow, maxFlow, SegType::None));
}

int main()
{
    std::cin.sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::cin >> n;
    std::vector<Segment> noneSegs;
    for (int i = 0; i < n; ++i)
    {
        int minF, maxF;
        std::string type;
        std::cin >> type >> minF >> maxF;

        if (type == "on")
        {
            AddNone(noneSegs);
            segs.push_back(Segment(minF, maxF, SegType::On));
        }
        else if (type == "off")
        {
            AddNone(noneSegs);
            segs.push_back(Segment(minF, maxF, SegType::Off));
        }
        else if (type == "none")
        {
            noneSegs.push_back(Segment(minF, maxF, SegType::None));
        }
    }
    AddNone(noneSegs);

    std::pair<int, int> onStart = { INT32_MIN / 2, INT32_MAX / 2 };
    std::pair<int, int> onEnd = { INT32_MIN / 2, INT32_MAX / 2 };

    for (int pos : nonePos)
    {
        std::pair<int, int> calcStart = { segs[pos].MinFlow, segs[pos].MaxFlow };
        std::pair<int, int> calcEnd = { segs[pos].MinFlow, segs[pos].MaxFlow };

        for (int i = pos - 1; i >= 0; --i)
        {
            switch (segs[i].Type)
            {
            case SegType::None:
                continue;

            case SegType::On:
                calcStart.first -= segs[i].MaxFlow;
                calcStart.second -= segs[i].MinFlow;
                if (calcStart.first < 0)
                    calcStart.first = 0;
                if (calcStart.second < 0)
                    calcStart.second = 0;
                break;

            case SegType::Off:
                calcStart.first += segs[i].MinFlow;
                calcStart.second += segs[i].MaxFlow;
                break;
            }
        }

        /*if (onStart.second - onStart.first > calcStart.second - calcStart.first)
            onStart = calcStart;*/
        onStart.first = std::max(onStart.first, calcStart.first);
        onStart.second = std::min(onStart.second, calcStart.second);

        for (int i = pos + 1; i < (int)segs.size(); ++i)
        {
            switch (segs[i].Type)
            {
            case SegType::None:
                continue;

            case SegType::On:
                calcEnd.first += segs[i].MinFlow;
                calcEnd.second += segs[i].MaxFlow;
                break;

            case SegType::Off:
                calcEnd.first -= segs[i].MaxFlow;
                calcEnd.second -= segs[i].MinFlow;
                if (calcEnd.first < 0)
                    calcEnd.first = 0;
                if (calcEnd.second < 0)
                    calcEnd.second = 0;
                break;
            }
        }

        /*if (onEnd.second - onEnd.first > calcEnd.second - calcEnd.first)
            onEnd = calcEnd;*/
        onEnd.first = std::max(onEnd.first, calcEnd.first);
        onEnd.second = std::min(onEnd.second, calcEnd.second);
    }

    printf("%d %d\n%d %d", onStart.first, onStart.second, onEnd.first, onEnd.second);

    return 0;
}