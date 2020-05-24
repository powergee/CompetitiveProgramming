#include <iostream>
#include <algorithm>
#include <cstring>
#define CH_TRUE 'T'
#define CH_FALSE 'F'

char input[2501];
int inputLength;
long long memo[2501];
char pelMemo[2501][2501];

void PrintArr(int start, int end)
{
	for (int i = start; i <= end; ++i)
	{
		printf("%c", input[i]);
	}
	printf("\n");
}

bool IsPel(int start, int end)
{
	if (start < 0 || start >= inputLength || end >= inputLength || end < 0)
		return false;

	if (start >= end)
		return true;

	char& result = pelMemo[start][end];

	if (result != 0)
		return result == CH_TRUE;

	if (input[start] == input[end] && IsPel(start + 1, end - 1))
	{
		result = CH_TRUE;
		return true;
	}

	result = CH_FALSE;
	return false;
}

long long Count(int start)
{
	if (start == inputLength - 1)
		return 1;

	if (start >= inputLength)
		return 0;

	long long& result = memo[start];

	if (result != -1)
		return result;
	result = 0x7fffffff;

	for (int i = inputLength - 1; i >= start; --i)
	{
		if (IsPel(start, i))
			result = std::min(Count(i + 1) + 1, result);
	}

	return result;
}

int main()
{
	scanf("%s", input);
	inputLength = strlen(input);
	std::fill(memo, memo + inputLength, -1);

	printf("%lld", Count(0));

	return 0;
}