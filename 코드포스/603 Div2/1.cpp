#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>

int main()
{
	int t;
	scanf("%d", &t);

	while (t--)
	{
		std::vector<int> candies(3);
		int answer = 0;
		scanf("%d %d %d", &candies[0], &candies[1], &candies[2]);

		std::sort(candies.begin(), candies.end(), std::greater<int>());

		answer += candies[2];
		if (candies[0] - candies[2] < candies[1])
		{
			int av = (candies[0] + candies[1] - candies[2]) / 2;
			int temp = candies[0];
			candies[0] = av;
			candies[1] = temp + candies[1] - candies[2] - av;
			candies[2] = 0;
		}
		else
		{
			candies[0] -= candies[2];
			candies[2] = 0;
		}

		std::sort(candies.begin(), candies.end(), std::greater<int>());
		answer += candies[1];

		printf("%d\n", answer);
	}

	return 0;
}