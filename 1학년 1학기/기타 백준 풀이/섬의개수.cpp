#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

bool map[50][50];
bool visited[50][50];

const pair<int, int> DIRS[8] = { {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1} };

int main()
{
	while (true)
	{
		int w, h;
		scanf("%d %d", &w, &h);

		if (w == 0 && h == 0)
			break;

		for (int row = 0; row < h; ++row)
		{
			for (int col = 0; col < w; ++col)
			{
				int input;
				scanf("%d", &input);
				map[row][col] = (input == 1);
			}
		}

		fill(&visited[0][0], &visited[0][0] + sizeof(visited) / sizeof(bool), false);
		int count = 0;
		queue<pair<int, int>> q;

		for (int row = 0; row < h; ++row)
		{
			for (int col = 0; col < w; ++col)
			{
				if (!visited[row][col] && map[row][col])
				{
					++count;
					// BFS START
					while (!q.empty()) q.pop();
					q.push(make_pair(row, col));

					while (!q.empty())
					{
						pair<int, int> now = q.front();
						q.pop();

						if (!visited[now.first][now.second])
						{
							visited[now.first][now.second] = true;

							for (int i = 0; i < 8; ++i)
							{
								int r = now.first + DIRS[i].first;
								int c = now.second + DIRS[i].second;

								if (r >= 0 && r < h && c >= 0 && c < w && !visited[r][c] && map[r][c])
									q.push(make_pair(r, c));
							}
						}
					}
					// BFS END
				}
			}
		}

		printf("%d\n", count);
	}

	return 0;
}