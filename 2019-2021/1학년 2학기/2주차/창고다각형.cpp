#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>

typedef std::pair<int, int> Pole;

std::vector<Pole> poles;

int main()
{
	int N;
	scanf("%d", &N);

	for (int i = 0; i < N; ++i)
	{
		int index, value;
		scanf("%d %d", &index, &value);

		poles.push_back({ index, value });
	}

	std::sort(poles.begin(), poles.end());

	Pole leftHeighest = { -1, -1 }, rightHeighest = { -1, -1 };
	int leftHeighestIndex, rightHeighestIndex;

	for (int i = 0; i < N; ++i)
	{
		if (leftHeighest.second < poles[i].second)
		{
			leftHeighest = poles[i];
			leftHeighestIndex = i;
		}
	}

	for (int i = N - 1; i >= leftHeighestIndex; --i)
	{
		if (leftHeighest.second == poles[i].second)
		{
			rightHeighest = poles[i];
			rightHeighestIndex = i;
			break;
		}
	}

	std::vector<Pole> leftPoles, rightPoles;

	for (int i = 0; i <= leftHeighestIndex; ++i)
	{
		if (leftPoles.empty())
			leftPoles.push_back(poles[i]);
		else if (leftPoles.back().second < poles[i].second)
			leftPoles.push_back(poles[i]);
	}

	for (int i = N - 1; i >= rightHeighestIndex; --i)
	{
		if (rightPoles.empty())
			rightPoles.push_back(poles[i]);
		else if (rightPoles.back().second < poles[i].second)
			rightPoles.push_back(poles[i]);
	}

	int result = 0;

	for (int i = 0; i < leftPoles.size() - 1; ++i)
	{
		result += (leftPoles[i + 1].first - leftPoles[i].first) * leftPoles[i].second;
	}

	for (int i = 0; i < rightPoles.size() - 1; ++i)
	{
		result += (rightPoles[i].first - rightPoles[i + 1].first) * rightPoles[i].second;
	}

	result += (rightHeighest.first - leftHeighest.first + 1) * leftHeighest.second;

	printf("%d", result);

	return 0;
}