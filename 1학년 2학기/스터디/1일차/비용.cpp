#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#define VERTEX_COUNT 100001
#define MOD 1000000000
typedef std::pair<int, std::pair<int, int>> Edge;
typedef long long Long;

int N, M;
Long total = 0, size[VERTEX_COUNT];
int parent[VERTEX_COUNT];
std::vector<Edge> edges;

int Find(int n)
{
	if (parent[n] == n) return n;
	return parent[n] = Find(parent[n]);
}

void Union(int a, int b)
{
	a = Find(a);
	b = Find(b);

	if (a != b) parent[b] = a;

	size[a] += size[b];
	size[b] = 1;
}

int main()
{
	scanf("%d %d", &N, &M);

	for (int i = 0; i < M; ++i)
	{
		int x, y, w;
		scanf("%d %d %d", &x, &y, &w);
		total += w;

		edges.push_back({ w, { x, y } });
	}

	for (int i = 0; i <= N; ++i)
	{
		parent[i] = i;
		size[i] = 1;
	}

	std::sort(edges.begin(), edges.end(), std::greater<Edge>());

	Long sum = 0;
	int edgesCount = edges.size();
	for (int i = 0; i < edgesCount; ++i)
	{
		int par1 = Find(edges[i].second.first);
		int par2 = Find(edges[i].second.second);

		if (par1 != par2)
		{
			sum += (((size[par1] * size[par2]) % MOD) * total) % MOD;
			sum %= MOD;
			Union(par1, par2);
		}

		total -= edges[i].first;
	}

	printf("%lld\n", sum);

	return 0;
}