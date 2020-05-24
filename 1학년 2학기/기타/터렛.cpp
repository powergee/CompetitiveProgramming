#include <iostream>

inline int pow2(int n)
{
	return n * n;
}

typedef std::pair<int, int> Point;

int main()
{
	int T;
	scanf("%d", &T);

	while (T--)
	{
		Point p1, p2;
		int r1, r2;

		scanf("%d %d %d %d %d %d", &p1.first, &p1.second, &r1, &p2.first, &p2.second, &r2);

		int dx = p1.first - p2.first;
		int dy = p1.second - p2.second;
		int sum = pow2(r1 + r2);
		int sub = pow2(r1 - r2);
		int dist = pow2(dx) + pow2(dy);

		if (dist < sum && dist > sub)
			printf("2\n");
		else if (dist == sum || (dist == sub && dist != 0))
			printf("1\n");
		else if (dist < sub || dist > sum)
			printf("0\n");
		else if (dist == 0)
		{
			if (r1 == r2)
				printf("-1\n");
			else printf("0\n");
		}
	}

	return 0;
}