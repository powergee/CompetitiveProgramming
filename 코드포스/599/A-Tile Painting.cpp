
#include <iostream>
#include <cmath>

typedef long long Long;

Long Count(Long input);
bool IsAbleToPaint(Long di1, Long di2, Long length);

int main()
{
	Long input;
	scanf("%lld", &input);
	printf("%lld", Count(input));

	return 0;
}

Long Count(Long input)
{
	Long limit = sqrt(input) + 1;
	Long divisor[2] = { 0, };

	for (Long i = 2; i <= limit; ++i)
	{
		if (input % i == 0)
		{
			if (!divisor[0])
				divisor[0] = i;
			else if (!divisor[1] && i % divisor[0] != 0)
			{
				divisor[1] = i;
				break;
			}
		}
	}

	if (divisor[1])
	{
		if (IsAbleToPaint(divisor[0], divisor[1], input))
			return 1;
		else
			return divisor[0];
	}

	else if (divisor[0])
	{
		Long inputDiv = input;

		while (inputDiv % divisor[0] == 0)
			inputDiv /= divisor[0];

		if (input % (input / divisor[0]) == 0 && input != divisor[0] && inputDiv != 1 && IsAbleToPaint(divisor[0], input / divisor[0], input))
			return 1;

		else return divisor[0];
	}

	else return input;
}

bool IsAbleToPaint(Long di1, Long di2, Long length)
{
	return ((length / di2) * di2) % di1 == 0;
}