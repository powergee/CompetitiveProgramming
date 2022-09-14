#include <iostream>
#include <queue>
#include <set>
using namespace std;

bool visited[200001];

int main()
{
	int n, k;
	scanf("%d %d", &n, &k);

	if (n >= k)
	{
		printf("%d", n-k);
		return 0;
	}

	queue<pair<int, int>> q;
	q.push(make_pair(n, 0));

	while (!q.empty())
	{
		pair<int, int> now = q.front();
		q.pop();
		if (now.first == k)
		{
			printf("%d", now.second);
			return 0;
		}

		if (!visited[now.first])
		{
			visited[now.first] = true;
			int nextTime = now.second + 1;

			if (now.first + 1 <= k && !visited[now.first + 1])
				q.push(make_pair(now.first + 1, nextTime));
			if (now.first - 1 >= 0 && !visited[now.first - 1])
				q.push(make_pair(now.first - 1, nextTime));
			if (now.first * 2 < k * 2 && !visited[now.first * 2])
				q.push(make_pair(now.first * 2, nextTime));
		}
	}

	return 0;
}