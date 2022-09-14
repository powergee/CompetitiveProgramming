#include <iostream>
#include <algorithm>
#include <vector>

struct Func
{
	long long a, b;
	double cross;
};

inline double getCross(Func f1, Func f2)
{
	return ((double)f2.b - f1.b) / ((double)f1.a - f2.a);
}

std::vector<Func> s;
long long height[100001];
long long cost[100001];
long long dp[100001];

int main()
{
	int n;
	scanf("%d", &n);

	for (int i = 0; i < n; ++i)
		scanf("%lld", height + i);

	for (int i = 0; i < n; ++i)
		scanf("%lld", cost + i);

	int fPos = 0;

	for (int i = 1; i < n; ++i)
	{
		Func newF = { cost[i - 1], dp[i - 1], 0 };
		while (!s.empty())
		{
			newF.cross = getCross(newF, s.back());
			if (s.back().cross < newF.cross)
				break;

			s.pop_back();
			if (s.size() == fPos)
				--fPos;
		}

		s.push_back(newF);

		long long x = height[i];
		while (fPos + 1 < (int)s.size() && s[fPos + 1].cross < x)
			++fPos;

		dp[i] = s[fPos].a * x + s[fPos].b;
	}

	printf("%lld\n", dp[n - 1]);

	return 0;
}