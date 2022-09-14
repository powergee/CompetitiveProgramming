#include <iostream>
#include <unordered_map>
#include <string>
#include <algorithm>

int parent[200010];
int count[200010];

int Union(int, int);
int Find(int, int);

int Union(int x, int y)
{
	int xPar = Find(x, 0);
	int yPar = Find(y, 0);

	int countSum = count[xPar] + count[yPar];
	parent[xPar] = yPar;
	count[yPar] = countSum;
	count[xPar] = 0;
	return countSum;
}

int Find(int x, int countAdd = 0)
{
	if (x == parent[x])
	{
		count[x] += countAdd;
		return x;
	}

	parent[x] = Find(parent[x], countAdd + count[x]);
	count[x] = 0;
	return parent[x];
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	int T;
	std::cin >> T;

	while (T--)
	{
		int F;
		std::cin >> F;

		for (int i = 0; i < 2 * F + 10; ++i)
			parent[i] = i;

		std::fill(count, count + 2 * F + 10, 0);

		std::unordered_map<std::string, int> nameMap;
		int nameIndex = 2;
		std::string name1;
		std::string name2;
		for (int i = 0; i < F; ++i)
		{
			std::cin >> name1 >> name2;
			int n1Index, n2Index;

			if (nameMap.find(name1) == nameMap.end())
			{
				n1Index = nameIndex;
				nameMap[name1] = nameIndex;
				++count[nameIndex++];
			}
			else n1Index = nameMap[name1];

			if (nameMap.find(name2) == nameMap.end())
			{
				n2Index = nameIndex;
				nameMap[name2] = nameIndex;
				++count[nameIndex++];
			}
			else n2Index = nameMap[name2];

			if (Find(n1Index) == Find(n2Index))
				std::cout << count[Find(n1Index)] << '\n';
			else
				std::cout << Union(n1Index, n2Index) <<'\n'; 
		}
	}

	return 0;
}