#include <iostream>
#include <algorithm>
using namespace std;

typedef long long Long;

Long memo[31][61];

Long CountCases(int med, int halfMed)
{
	if (med == 0 && halfMed == 0)
		return 1;

	if (med < 0 || halfMed < 0)
		return 0;

	Long& ret = memo[med][halfMed];
	if (ret != -1)
		return ret;

	ret = 0;
	ret += CountCases(med - 1, halfMed + 1) + CountCases(med, halfMed - 1);

	return ret;
}

int main()
{
	fill(&memo[0][0], &memo[0][0] + sizeof(memo) / sizeof(Long), -1);

	while (true)
	{
		int input;
		scanf("%d", &input);

		if (input == 0)
			break;

		printf("%lld\n", CountCases(input, 0));
	}

	return 0;
}