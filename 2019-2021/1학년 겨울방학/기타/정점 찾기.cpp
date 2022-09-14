//#include "findVertices.h"
#include <vector>
#include <queue>

std::vector<int> up, down;
int upPoint, downPoint;

bool IsValid()
{
	std::vector<int> u, v;

	for (int i = 0; i < (int)up.size() - 1; ++i)
	{
		u.push_back(up[i]);
		v.push_back(up[i + 1]);
	}

	for (int i = 0; i < (int)down.size() - 1; ++i)
	{
		u.push_back(down[i]);
		v.push_back(down[i + 1]);
	}

	return query(u, v, up[0], down[0]);
}

void SwapSubVec(int left, int right)
{
	for (int i = left; i <= std::min(right, (int)up.size() - 1); ++i)
		std::swap(up[i], down[i]);
}

// left, right 인덱스 0부터
void DivideUp(int left, int right)
{
	if (right - left == 0)
	{
		upPoint = up[left];
		return;
	}

	int med = (right + left) / 2;
	std::vector<int> u, v;

	for (int i = left; i < med; ++i)
	{
		u.push_back(up[i]);
		v.push_back(up[i + 1]);
	}

	for (int i = 0; i < (int)down.size() - 1; ++i)
	{
		u.push_back(down[i]);
		v.push_back(down[i + 1]);
	}

	if (query(u, v, up[left], down[0]))
		DivideUp(left, med);
	else DivideUp(med + 1, right);
}

// left, right 인덱스 0부터
void DivideDown(int left, int right)
{
	if (right - left == 0)
	{
		downPoint = down[left];
		return;
	}

	int med = (right + left) / 2;
	std::vector<int> u, v;

	for (int i = left; i < med; ++i)
	{
		u.push_back(down[i]);
		v.push_back(down[i + 1]);
	}

	if (query(u, v, upPoint, down[left]))
		DivideDown(left, med);
	else DivideDown(med + 1, right);
}

void find(int N)
{
	up.clear();
	down.clear();

	for (int i = 1; i <= N / 2; ++i)
		up.push_back(i);
	for (int i = N / 2 + 1; i <= N; ++i)
		down.push_back(i);
	std::queue<std::pair<int, int>> divQ;
	divQ.push({ 0, N / 2 - 1 });

	while (!IsValid())
	{
		int qSize = divQ.size();
		while (qSize--)
		{
			std::pair<int, int> div = divQ.front();
			divQ.pop();

			if (div.second == div.first)
			{
				divQ.push(div);
				continue;
			}

			int med = (div.first + div.second) / 2;
			SwapSubVec(div.first, med);
			divQ.push({ div.first, med });
			divQ.push({ med + 1, div.second });
		}
	}

	DivideUp(0, up.size() - 1);
	DivideDown(0, down.size() - 1);
	answer(upPoint, downPoint);
}