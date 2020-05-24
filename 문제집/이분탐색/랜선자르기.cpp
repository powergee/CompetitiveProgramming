#include <iostream>
typedef long long Long;

Long length[10001];

Long Count(Long lenToGet, Long* lenArr, int lenCount);

int main()
{
	int K, N;
	Long left = 1, right = 1;
	scanf("%d %d", &K, &N);

	for (int i = 0; i < K; ++i)
	{
		scanf("%ld", &length[i]);
		if (length[i] > right)
			right = length[i];
	}

	Long pivot = (left + right) / 2;
	Long count = 0;

	if (Count(right, length, K) >= N)
	{
		pivot = right;
	}
	else
	{
		while (count != N)
		{
			count = Count(pivot, length, K);

			if (count > N)
			{
				left = pivot;
			}
			else if (count < N)
			{
				right = pivot;
			}

			Long newPivot = (left + right) / 2;
			if (newPivot == pivot && count != N)
			{
				pivot = left;
				break;
			}
			else pivot = (left + right) / 2;
		}

		while (Count(pivot, length, K) >= N)
			++pivot;
		--pivot;
	}

	printf("%ld", pivot);
}

Long Count(Long lenToGet, Long* lenArr, int lenCount)
{
	Long result = 0;
	for (int i = 0; i < lenCount; ++i)
	{
		result += lenArr[i] / lenToGet;
	}

	return result;
}