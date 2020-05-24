#include <iostream>
#include <vector>
#include <algorithm>

enum Direction { Left, Right };

std::vector<int> cows;
std::vector<int> dist;
std::vector<bool> visited;
std::vector<bool> fr_visited;

bool CanGive(int from, Direction dir)
{
	int leftDist = (from <= 0) ? INT32_MAX : dist[from - 1];
	int rightDist = (from >= cows.size() - 1) ? INT32_MAX : dist[from];

	if (leftDist == INT32_MAX && rightDist == INT32_MAX)
		return false;
	else if ((leftDist <= rightDist && dir == Direction::Left) || (leftDist > rightDist && dir == Direction::Right))
		return true;
	else return false;
}

void DFS(int start)
{
	if (visited[start])
		return;

	visited[start] = true;

	if (CanGive(start, Direction::Right))
		DFS(start + 1);
	if (CanGive(start, Direction::Left))
		DFS(start - 1);
}

int FindRoot(int start)
{
	if (start < 0 || start > cows.size() - 1)
		return start;

	fr_visited[start] = true;

	if (start > 0 && !visited[start - 1] && !fr_visited[start - 1] && (CanGive(start - 1, Direction::Right)))
		return FindRoot(start - 1);

	else if (start < cows.size() - 1 && !visited[start + 1] && !fr_visited[start + 1] && (CanGive(start + 1, Direction::Left)))
		return FindRoot(start + 1);

	return start;
}

int main()
{
	int n;
	scanf("%d", &n);

	cows.resize(n);
	dist.resize(n - 1);
	visited.resize(n);
	fr_visited.resize(n);

	std::fill(visited.begin(), visited.end(), false);

	for (int i = 0; i < n; ++i)
		scanf("%d", &cows[i]);

	std::sort(cows.begin(), cows.end());

	for (int i = 0; i < n - 1; ++i)
		dist[i] = cows[i + 1] - cows[i];

	int answer = 0;
	for (int i = 0; i < n; ++i)
	{
		if (!visited[i])
		{
			std::fill(fr_visited.begin(), fr_visited.end(), false);
			++answer;
			DFS(FindRoot(i));
		}
	}

	printf("%d", answer);

	return 0;
}