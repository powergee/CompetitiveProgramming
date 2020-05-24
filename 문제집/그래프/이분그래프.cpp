#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#define RED 1
#define BLUE -1

std::vector<int> graph[20001];
char vertexes[20001];

int main()
{
	int tc;
	scanf("%d", &tc);

	while (tc--)
	{
		for (int i = 0; i < 20001; ++i)
			graph[i].clear();
		std::fill(vertexes, vertexes + 20000, 0);

		int V, E;
		scanf("%d %d", &V, &E);

		for (int i = 0; i < E; ++i)
		{
			int a, b;
			scanf("%d %d", &a, &b);
			graph[a].push_back(b);
			graph[b].push_back(a);
		}

		std::queue<int> q;
		bool isBipartite = true;
		for (int i = 1; i <= V; ++i)
		{
			if (vertexes[i] == 0)
			{
				q.push(i);
				vertexes[i] = RED;
                

				while (!q.empty())
				{
					int now = q.front();
					q.pop();

					for (int next : graph[now])
					{
						if (vertexes[next] == 0)
						{
							vertexes[next] = -vertexes[now];
							q.push(next);
						}
						else if (vertexes[next] == vertexes[now])
						{
							isBipartite = false;
							goto breakAll;
						}
						else continue;
					}
				}
			}
		}
	breakAll:

		printf(isBipartite ? "YES\n" : "NO\n");
	}

	return 0;
}