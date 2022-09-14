#include <iostream>
#include <algorithm>
#pragma warning(disable:4996)
using namespace std;

struct Work
{
	int T, P;
};

int memo[1500001];
int N;
Work works[1500001];

int FindMax(int start)
{
	if (start >= N)
		return 0;

	int& ret = memo[start];
	if (ret != -1)
		return ret;

	Work& today = works[start];
	int c1 = -1, c2 = -1;

	c1 = FindMax(start + 1);
	if (start + today.T <= N)
		c2 = FindMax(start + today.T) + today.P;

	return ret = max(c1, c2);
}

int main()
{
	scanf("%d", &N);
	fill(memo, memo + 1500001, -1);

	for (int i = 0; i < N; ++i)
	{
		scanf("%d %d", &works[i].T, &works[i].P);
	}

	printf("%d", FindMax(0));
    return 0;
}