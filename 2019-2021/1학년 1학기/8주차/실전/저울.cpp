#include <iostream>
#include <algorithm>
using namespace std;

typedef long long Long;

int N;
int w[1000];

int main()
{
	scanf("%d", &N);
	for (int i = 0; i < N; ++i)
	{
		scanf("%d", &w[i]);
	}

	sort(w, w + N);

	if (w[0] != 1)
		cout << 1 << "\n";

	else
	{
		Long sum = 1;
		for (int i = 1; i < N; i++)
		{
			if (w[i] > sum + 1)
				break;

			sum += w[i];
		}
		cout << sum + 1 << "\n";
	}

	return 0;
}