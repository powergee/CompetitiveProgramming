#include <iostream>
#include <vector>
#include <algorithm>
#define VERTEX_COUNT 100001
typedef std::pair<int, std::pair<int, int>> Edge;

std::vector<int> map[VERTEX_COUNT];
std::vector<Edge> edges;

int Cost(int u, int v)
{
	if (std::find(map[u].begin(), map[u].end(), v) == map[u].end())
		return 0;

	int sum = 0;
	std::pair<int, int> e1 = { u, v };
	std::pair<int, int> e2 = { v, u };
	for (auto i = edges.begin(); i != edges.end(); ++i)
	{
		sum += (*i).first;
		sum %= 1000000000;

		if ((*i).second == e1 || (*i).second == e2)
			break;
	}

	return sum;
}

int main()
{
	int N, M;
	scanf("%d %d", &N, &M);

	for (int i = 0; i < M; ++i)
	{
		int x, y, w;
		scanf("%d %d %d", &x, &y, &w);

		map[x].push_back(y);
		map[y].push_back(x);
		edges.push_back({ w, { x, y } });
	}

	std::sort(edges.begin(), edges.end());

	int sum = 0;
	for (int u = 1; u < N; ++u)
	{
		for (int v = u + 1; v < N; ++v)
		{
			sum += Cost(u, v);
			sum %= 1000000000;
		}
	}

	printf("%d", sum);

	return 0;
}