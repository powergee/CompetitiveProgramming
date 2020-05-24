#include <iostream>
#include <algorithm>
#include <stack>

int result[1000000];

int main()
{
	int N;
	std::stack<std::pair<int, int>> s;

	scanf("%d", &N);

	for (int i = 0; i < N; ++i)
	{
		int now;
		scanf("%d", &now);

		while (!s.empty() && s.top().second < now)
		{
			result[s.top().first] = now;
			s.pop();
		}

		s.push({ i, now });
	}

	while (!s.empty())
	{
		result[s.top().first] = -1;
		s.pop();
	}

	for (int i = 0; i < N; ++i)
	{
		printf("%d ", result[i]);
	}

	return 0;
}