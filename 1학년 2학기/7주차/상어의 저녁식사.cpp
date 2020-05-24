#include <iostream>
#include <algorithm>

class Shark
{
private:
	int size;
	int speed;
	int intel;

public:
	void ScanShark()
	{
		scanf("%d %d %d", &size, &speed, &intel);
	}

	bool CanEat(const Shark& s) const
	{
		return size >= s.size && speed >= s.speed && intel >= s.intel;
	}

	bool operator==(const Shark& s) const
	{
		return size == s.size && speed == s.speed && intel == s.intel;
	}

	bool operator!=(const Shark& s) const
	{
		return !operator==(s);
	}
};

int N;
Shark sharks[51];
bool visited[51];
int matching[51];

int DFS(int start)
{
	if (visited[start])
		return 0;

	visited[start] = true;

	for (int i = 1; i <= N; ++i)
	{
		if (i == start || !sharks[start].CanEat(sharks[i]))
			continue;

		if (sharks[i] == sharks[start] && start > i)
			continue;

		if (matching[i] == 0 || DFS(matching[i]))
		{
			matching[i] = start;
			return 1;
		}
	}

	return 0;
}

int Bipartite()
{
	int result = 0;

	for (int i = 1; i <= N; ++i)
	{
		int add = 0;

		for (int j = 0; j < 2; ++j)
		{
			std::fill(visited, visited + 51, false);
			int temp = DFS(i);
			add += temp;
		}

		result += add;
	}

	return result;
}

int main()
{
	scanf("%d", &N);

	for (int i = 1; i <= N; ++i)
		sharks[i].ScanShark();

	printf("%d", N - Bipartite());

	return 0;
}