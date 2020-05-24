#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

int radius[1000];
int answer[1000];

double GetOPT(int* nums, int N)
{
	double opt = nums[0] + nums[N - 1];
	for (int i = 1; i < N; ++i)
	{
		opt += sqrt(pow(nums[i] + nums[i - 1], 2.0) - pow(nums[i] - nums[i - 1], 2.0));
	}

	return opt;
}

int main()
{
	int N;
	scanf("%d", &N);

	for (int i = 0; i < N; ++i)
	{
		scanf("%d", &radius[i]);
	}

	std::sort(radius, radius + N);
	bool leftFirst = true;

	if (N % 2 == 0)
	{
		for (int i = 1; i <= N / 2; ++i, leftFirst = !leftFirst)
		{
			if (leftFirst)
			{
				answer[i - 1] = radius[N / 2 - i];
				answer[N - i] = radius[N / 2 - 1 + i];
			}
			else
			{
				answer[i - 1] = radius[N / 2 - 1 + i];
				answer[N - i] = radius[N / 2 - i];
			}
		}

		printf("%.5lf", GetOPT(answer, N));
	}
	else
	{
		double case1, case2;

		for (int i = 1; i <= N / 2; ++i, leftFirst = !leftFirst)
		{
			if (leftFirst)
			{
				answer[i - 1] = radius[N / 2 - i];
				answer[N - i - 1] = radius[N / 2 + i];
			}
			else
			{
				answer[i - 1] = radius[N / 2 + i];
				answer[N - i - 1] = radius[N / 2 - i];
			}
		}
		answer[N - 1] = radius[(N - 1) / 2];
		case1 = GetOPT(answer, N);

		leftFirst = true;

		for (int i = 1; i <= N / 2; ++i, leftFirst = !leftFirst)
		{
			if (leftFirst)
			{
				answer[i] = radius[N / 2 - i];
				answer[N - i] = radius[N / 2 + i];
			}
			else
			{
				answer[i] = radius[N / 2 + i];
				answer[N - i] = radius[N / 2 - i];
			}
		}
		answer[0] = radius[(N - 1) / 2];
		case2 = GetOPT(answer, N);

		printf("%.5lf", std::min(case1, case2));
	}
}