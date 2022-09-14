#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>

typedef long long Long;
const Long INF = 1LL<<32;

int data[5003];
int sum[5003];
Long d[5003][5003];
int p[5003][5003];

int getCost(int left, int right)
{
    return sum[right] - sum[left-1];
}

// data의 [left, right]에 값을 채우고 아래 함수를 실행하면 d에 dp값이 채워진다.
void doKnuthOpt(int left, int right)
{
    for (int i = left; i <= right; i++)
		d[i-1][i] = 0, p[i-1][i] = i;

	for (int l = 2; l <= right-left+1; l++) 
	{
		for (int i = left-1; i + l <= right; i++) 
		{
			int j = i + l;
			d[i][j] = INF;
			for (int k = p[i][j - 1]; k <= p[i + 1][j]; k++) 
			{
                int current = d[i][k] + d[k][j] + getCost(i+1, j);
				if (d[i][j] > current) 
				{
					d[i][j] = current;
					p[i][j] = k;
				}
			}
		}
	}
}

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int n;
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i)
        {
            scanf("%d", data+i);
            sum[i] = sum[i-1] + data[i];
        }

        doKnuthOpt(1, n);
        printf("%lld\n", d[0][n]);
    }

    return 0;
}