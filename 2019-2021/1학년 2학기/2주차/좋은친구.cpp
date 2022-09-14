#include <iostream>
#include <string>
#include <queue>

int main()
{
	std::string name;
	std::queue<int> q[21];
	int N, K;
	scanf("%d %d", &N, &K);

	for (int i = 1; i <= N; ++i)
	{
		std::cin >> name;
		int nameLength = name.length();
		q[nameLength].push(i);
	}

	long long result = 0;
	for (int i = 2; i < 21; ++i)
	{
		std::queue<int> temp;
		while (q[i].size() > 1)
		{
			temp.push(q[i].front());
			q[i].pop();

			while (!temp.empty() && q[i].front() - temp.front() > K)
				temp.pop();

			result += temp.size();
		}
	}

	printf("%lld", result);
}