#include <iostream>
#include <set>
#include <vector>

typedef long long Long;

int Count(std::multiset<Long>& arr, Long i)
{
	int count = 0;
	for (Long arrEle : arr)
	{
		if (1LL << i & arrEle)
			++count;
	}

	return count;
}

int main()
{
	Long u, v;
	scanf("%lld %lld", &u, &v);

	if (v == 0)
	{
		if (u == 0)
			printf("0");
		else
			printf("-1");

		return 0;
	}

	std::multiset<Long> arr;
	for (Long i = 0; i < 63; ++i)
	{
		if (1LL << i & v)
			arr.insert(1LL << i);
	}

	bool fail = false;
	for (Long i = 62; i >= 0 && !fail; --i)
	{
		int count = Count(arr, i);

		if (((1LL << i & u) && count % 2 == 0) || (!(1LL << i & u) && count % 2 == 1))
		{
			if (i == 0)
			{
				fail = true;
				continue;
			}

			auto found = arr.find(1LL << i);

			if (found == arr.end())
			{
				bool valid = false;
				for (Long j = i + 1; j < 63 && !valid; ++j)
				{
					if (Count(arr, j) >= 2)
					{
						valid = true;
						arr.erase(arr.find(1LL << j));
						arr.erase(arr.find(1LL << j));
						for (Long k = j - 1; k > i; --k)
						{
							arr.insert(1LL << k);
							arr.insert(1LL << k);
						}
						arr.insert(1LL << i);
						arr.insert(1LL << i);
						arr.insert(1LL << i);
						arr.insert(1LL << i);
					}
				}

				if (!valid)
					fail = true;
			}

			if (!fail)
			{
				arr.erase(arr.find(1LL << i));
				arr.insert(1LL << (i - 1));
				arr.insert(1LL << (i - 1));
			}
		}
	}

	if (fail)
		printf("-1");
	else
	{
		std::vector<Long> result;
		std::vector<std::multiset<Long>::iterator> increasing;

		while (!arr.empty())
		{
			increasing.push_back(arr.begin());

			for (auto it = arr.begin(); it != arr.end(); ++it)
			{
				if (*increasing.back() < *it)
					increasing.push_back(it);
			}

			if (increasing.size() == 1)
			{
				for (Long ele : arr)
					result.push_back(ele);
				break;
			}
			else
			{
				Long sum = 0;
				for (auto it : increasing)
				{
					sum += *it;
					arr.erase(it);
				}
				result.push_back(sum);
			}

			increasing.clear();
		}

		printf("%d\n", (int)result.size());
		for (Long ele : result)
			printf("%lld ", ele);
	}

	return 0;
}