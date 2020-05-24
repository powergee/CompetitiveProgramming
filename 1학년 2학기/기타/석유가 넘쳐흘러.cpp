#include <iostream>
#include <limits>
#include <algorithm>

int N;
int capacity[262144];
int extPower[262144];
int overflow[262144];
int tank[262144];
int fullTime[262144];

int GetOther(int tankNum)
{
    return tankNum % 2 == 0 ? tankNum + 1 : tankNum - 1;
}

int GetParent(int tankNum)
{
    return tankNum % 2 == 0 ? tankNum / 2 : (tankNum - 1) / 2;
}

void ThrowOverflow(int tankNum, int amount)
{
    if (tankNum == 1)
        return;

    int other = GetOther(tankNum);
    int parent = GetParent(tankNum);

    if (fullTime[other] == 0)
        overflow[other] = amount;
    else
        overflow[parent] = amount;
}

void FindTime(int tankNum)
{
    if (fullTime != 0) return;

    if (tankNum * 2 >= N)
    {
        extPower[tankNum] = 1;
    }
    else
    {
        FindTime(tankNum * 2);
        FindTime(tankNum * 2 + 1);
    }

    if (overflow[tankNum] >= capacity[tankNum])
    {
        fullTime[tankNum] = fullTime[std::max(fullTime[2 * tankNum], fullTime[2 * tankNum + 1])];
        ThrowOverflow(tankNum, capacity[tankNum] - overflow[tankNum]);

        return;
    }
    else
    {
        int extra = capacity[tankNum] - overflow[tankNum];

        
    }
    fullTime[tankNum] = capacity[tankNum] - overflow[tankNum]
}

int main()
{
    capacity[0] = INT32_MAX;

	scanf("%d", &N);
	for (int i = 1; i <= N; ++i)
	{
		scanf("%d", &capacity[i]);
	}



    return 0;
}