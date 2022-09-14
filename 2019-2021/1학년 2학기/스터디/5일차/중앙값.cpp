#include <iostream>

int tree[300000];
int nums[250001];

void Add(int value, int toAdd, int index = 1, int start = 0, int end = 65536)
{
	if (value < start || value > end)
		return;

	tree[index] += toAdd;

	if (start == end)
		return;

	int med = (start + end) / 2;

	if (value <= med)
		Add(value, toAdd, index * 2, start, med);
	else Add(value, toAdd, index * 2 + 1, med + 1, end);
}

int GetNum(int nTh, int index = 1, int start = 0, int end = 65536)
{
	if (start == end)
		return start;

	int left = tree[index * 2];

	if (left >= nTh && left)
		return GetNum(nTh, index * 2, start, (start + end) / 2);
	else if (tree[index * 2 + 1])
		return GetNum(nTh - left, index * 2 + 1, (start + end) / 2 + 1, end);

	return -1;
}

int main()
{
	int N, K;
	scanf("%d %d", &N, &K);

	for (int i = 1; i <= N; ++i)
		scanf("%d", nums + i);

	for (int i = 1; i <= K; ++i)
		Add(nums[i], 1);

	long long sum = 0;

	for (int i = K; i < N; ++i)
	{
		sum += GetNum((K + 1) / 2);

		Add(nums[i - K + 1], -1);
		Add(nums[i + 1], 1);
	}
	sum += GetNum((K + 1) / 2);

	printf("%lld", sum);

	return 0;
}