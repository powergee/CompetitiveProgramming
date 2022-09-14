#include <iostream>
#include <algorithm>
#include <vector>

typedef std::pair<int, int> TimeSpan;

inline int ToMinutes(int n)
{
	return (n / 100 * 60) + n % 100;
}

std::vector<TimeSpan> workSpans;
std::vector<TimeSpan> combinedSpans;

const int OPEN_TIME = ToMinutes(1000);
const int CLOSE_TIME = ToMinutes(2200);

int main()
{
	int N;
	scanf("%d", &N);

	for (int i = 0; i < N; ++i)
	{
		int a, b;
		scanf("%d %d", &a, &b);

		workSpans.push_back(std::make_pair(ToMinutes(a) - 10, ToMinutes(b) + 10));
	}

	std::sort(workSpans.begin(), workSpans.end());

	TimeSpan current = workSpans[0];

	for (int i = 1; i < N; ++i)
	{
		if (current.second >= workSpans[i].second)
			continue;
		else if (current.second >= workSpans[i].first && current.second <= workSpans[i].second)
			current.second = workSpans[i].second;
		else if (current.second < workSpans[i].first && current.second <= workSpans[i].second)
		{
			combinedSpans.push_back(current);
			current = workSpans[i];
		}
	}

	combinedSpans.push_back(current);

	int longest = combinedSpans[0].first - OPEN_TIME;
	for (int i = 1; i < combinedSpans.size(); ++i)
	{
		int freeTime = combinedSpans[i].first - combinedSpans[i - 1].second;
		if (longest < freeTime)
			longest = freeTime;
	}
	int lastTime = CLOSE_TIME - combinedSpans.back().second;
	if (longest < lastTime)
		longest = lastTime;

	printf("%d", longest);

	return 0;
}