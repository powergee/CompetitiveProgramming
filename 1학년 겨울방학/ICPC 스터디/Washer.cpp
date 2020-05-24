#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>

typedef long long Long;

class Point
{
public:
    Long X, Y, Z;

    Point() : X(0), Y(0), Z(0) {}
    Point(Long x, Long y, Long z) : X(x), Y(y), Z(z) {}
    
    Point operator - (const Point& p) const
    {
        return Point(X - p.X, Y - p.Y, Z - p.Z);
    }

    // 위치벡터의 외적
    Point Outer(const Point& p) const
    {
        Long newX = Y*p.Z - Z*p.Y;
        Long newY = Z*p.X - X*p.Z;
        Long newZ = X*p.Y - Y*p.X;
        return Point(newX, newY, newZ);
    }

    // 위치벡터의 내적
    Long Inner(const Point& p) const
    {
        return (X*p.X + Y*p.Y + Z*p.Z);
    }
};

std::vector<Point> cls;
int n, k;

double CalcColorTrans(const std::vector<Point>& v)
{
    Long sumOfSqare = 0;
    Long sumOfR = 0;
    Long sumOfG = 0;
    Long sumOfB = 0;

    for (const Point& p : v)
    {
        sumOfSqare += p.X*p.X + p.Y*p.Y + p.Z*p.Z;
        sumOfR += p.X;
        sumOfG += p.Y;
        sumOfB += p.Z;
    }

    return sumOfSqare - (sumOfR*sumOfR + sumOfG*sumOfG + sumOfB*sumOfB)/(double)v.size();
}

double Calc(int p1, int p2, int p3)
{
    // 세 점으로 만들어지는 평면의 법선 벡터
    Point normalVec = (cls[p2] - cls[p1]).Outer(cls[p3]-cls[p1]);
    std::vector<Point> s1, s2;

    // 세 점을 제외한 나머지 점들을 집합에 담음.
    for (int i = 0; i < n; ++i)
    {
        if (i == p1 || i == p2 || i == p3)
            continue;
        if (normalVec.Inner(cls[i]-cls[p1]) > 0)
            s1.push_back(cls[i]);
        else
            s2.push_back(cls[i]);
    }

    double ans = std::numeric_limits<double>::max();

    for (int xCase = 0; xCase <= 1; ++xCase)
    {
        for (int yCase = 0; yCase <= 1; ++yCase)
        {
            for (int zCase = 0; zCase <= 1; ++zCase)
            {
                if (xCase == yCase && yCase == zCase)
                    continue;
                
                xCase ? s1.push_back(cls[p1]) : s2.push_back(cls[p1]);
                yCase ? s1.push_back(cls[p2]) : s2.push_back(cls[p2]);
                zCase ? s1.push_back(cls[p3]) : s2.push_back(cls[p3]);

                ans = std::min(ans, CalcColorTrans(s1) + CalcColorTrans(s2));

                xCase ? s1.pop_back() : s2.pop_back();
                yCase ? s1.pop_back() : s2.pop_back();
                zCase ? s1.pop_back() : s2.pop_back();
            }
        }
    }

    return ans;
}

int main()
{
    scanf("%d %d", &n, &k);

    cls.resize(n);
    for (int i = 0; i < n; ++i)
        scanf("%lld %lld %lld", &cls[i].X, &cls[i].Y, & cls[i].Z);

    if (n <= k)
        printf("%.6lf", 0);
    else if (k == 1)
    {
        printf("%.6lf", CalcColorTrans(cls));
    }
    else
    {
        double result = std::numeric_limits<double>::max();
        
        for (int p1 = 0; p1 < n; ++p1)
        {
            for (int p2 = 0; p2 < p1; ++p2)
            {
                for (int p3 = 0; p3 < p2; ++p3)
                {
                    result = std::min(result, Calc(p1, p2, p3));
                }
            }
        }

        printf("%.6lf", result);
    }

    return 0;
}