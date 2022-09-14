#include <iostream>
#include <algorithm>
using namespace std;

int N, K;

bool isChecked[31][31][31][436];
char result[30];

bool FindResult(int pos, int aCount, int bCount, int currScore)
{
	if (pos == N)
	{
		if (currScore == K)
			return true;
		else return false;
	}

	else if (currScore > K)
		return false;

	bool& checked = isChecked[pos][aCount][bCount][currScore];
	if (checked)
		return false;
	checked = true;

	int score;

	score = 0;
	if (FindResult(pos + 1, aCount + 1, bCount, currScore + score))
	{
		result[pos] = 'A';
		return true;
	}

	score = aCount;
	if (FindResult(pos + 1, aCount, bCount + 1, currScore + score))
	{
		result[pos] = 'B';
		return true;
	}

	score = aCount + bCount;
	if (FindResult(pos + 1, aCount, bCount, currScore + score))
	{
		result[pos] = 'C';
		return true;
	}

	return false;
}

int main()
{
	scanf("%d %d", &N, &K);
	fill(result, result + 30, 0);

	if (FindResult(0, 0, 0, 0))
		printf("%s", result);
	else printf("-1");

	return 0;
}