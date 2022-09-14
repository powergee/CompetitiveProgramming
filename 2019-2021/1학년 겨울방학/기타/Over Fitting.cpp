#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <algorithm>

typedef std::tuple<int, int, bool> Data;
typedef std::pair<int, int> Vec;

int n;
std::vector<Data> data;

int Inner(Vec v1, Vec v2)
{
    return v1.first * v2.first + v1.second * v2.second;
}

int CalcMax(int p1, int p2)
{
    int x1, y1, x2, y2;
    bool pos;
    std::tie(x1, y1, pos) = data[p1];
    std::tie(x2, y2, pos) = data[p2];
    
    Vec v = {y1 - y2, x2 - x1};

    int upperPos = 0, upperNeg = 0, lowerPos = 0, lowerNeg = 0, linePos = 0, lineNeg = 0;
    for (const Data& d : data)
    {
        int x, y;
        std::tie(x, y, pos) = d;

        if (0 == Inner(v, {x - x1, y - y1}))
            pos ? ++linePos : ++lineNeg;
        else if (0 < Inner(v, {x - x1, y - y1}))
            pos ? ++upperPos : ++ upperNeg;
        else
            pos ? ++lowerPos : ++ lowerNeg;
    }

    int result1 = 0, result2 = 0;

    // upper가 positive 데이터들이 있는 곳이라고 가정할 때
    if (upperNeg == 0)
        result1 = upperPos + linePos;

    // lower가 positive 데이터들이 있는 곳이라고 가정할 때
    if (lowerNeg == 0)
        result2 = lowerPos + linePos;

    return std::max(result1, result2);
}

int main()
{
    std::cin.sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::cin >> n;

    for (int i = 0; i < n; ++i)
    {
        int x, y;
        std::string name;
        std::cin >> x >> y >> name;
        bool positive = name == "LOVELYZ";
        data.push_back(std::make_tuple(x, y, positive));
    }

    std::vector<bool> select(data.size());
    std::fill(select.begin(), select.end(), false);
    select[select.size() - 1] = select[select.size() - 2] = true;

    int result = 0;
    do
    {
        int p1 = -1, p2 = -1;

        for (int i = 0; i < select.size(); ++i)
        {
            if (select[i])
            {
                if (p1 == -1)
                    p1 = i;
                else
                {
                    p2 = i;
                    break;
                }
            }
        }

        if (!std::get<2>(data[p1]) && !std::get<2>(data[p2]))
            continue;

        result = std::max(result, CalcMax(p1, p2));

    } while (std::next_permutation(select.begin(), select.end()));

    printf("%d", result);

    return 0;
}