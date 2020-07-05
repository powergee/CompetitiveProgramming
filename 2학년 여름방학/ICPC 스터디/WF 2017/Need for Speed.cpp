#include <iostream>
#include <cmath>
#include <algorithm>

int n;
double t;
std::pair<double, double> history[1000];

double calcF(double c)
{
    double result = t;
    for (int i = 0; i < n; ++i)
        result -= history[i].first / (history[i].second + c);
    return result;
}

double calcFp(double c)
{
    double result = 0;
    for (int i = 0; i < n; ++i)
        result += history[i].first / std::pow((history[i].second + c), 2);
    return result;
}

int main()
{
    scanf("%d %lf", &n, &t);

    for (int i = 0; i < n; ++i)
        scanf("%lf %lf", &history[i].first, &history[i].second);
    double minS = history[0].second;
    for (int i = 1; i < n; ++i)
        minS = std::min(minS, history[i].second);
    
    double answer = -minS + 1e-6;
    for (int i = 0; i < 1000000; ++i)
    {
        double prev = answer;
        answer = prev - calcF(prev) / calcFp(prev);

        if (std::abs(prev - answer) < 1e-7)
            break;
    }

    printf("%.7lf", answer);

    return 0;
}