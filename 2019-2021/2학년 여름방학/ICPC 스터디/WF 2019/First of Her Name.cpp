#include <iostream>
#include <vector>
#include <algorithm>

int n, k;
std::vector<int> mother, suffixArr, ancestor;
std::vector<char> additionCh;
std::vector<std::pair<int, int>> order;

int compareSuffixAndQuery(int lady, std::string& query)
{
	for (int i = 0; i < (int)query.size(); ++i)
	{
		if (query[i] != additionCh[lady])
			return query[i] < additionCh[lady] ? -1 : 1;
		lady = mother[lady];
	}
	return 0;
}

int lowerBound(int left, int right, std::string& query)
{
	if (left == right)
		return left;

	int mid = (left + right) / 2;
	if (compareSuffixAndQuery(order[mid].second, query) > 0)
		return lowerBound(mid + 1, right, query);

	return lowerBound(left, mid, query);
}

int upperBound(int left, int right, std::string& query)
{
	if (left == right)
		return left;

	int mid = (left + right) / 2;
	if (compareSuffixAndQuery(order[mid].second, query) >= 0)
		return upperBound(mid + 1, right, query);

	return upperBound(left, mid, query);
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> k;

	mother.resize(n + 1);
	suffixArr.resize(n + 1);
	additionCh.resize(n + 1);

	for (int i = 1; i <= n; ++i)
	{
		std::cin >> additionCh[i] >> mother[i];
		suffixArr[i] = additionCh[i];
	}

	ancestor = mother;

	for (int d = 1; d <= n; d <<= 1)
	{
		std::vector< std::pair<std::pair<int, int>, int> > vec(n + 1);

		for (int i = n; i >= 0; --i)
		{
			vec[i] = { {suffixArr[i], suffixArr[ancestor[i]]}, i };
			ancestor[i] = ancestor[ancestor[i]];
		}

		std::sort(vec.begin(), vec.end());
		int newPri = 0;
		for (int i = 0; i < n + 1; ++i)
		{
			if (i > 0 && vec[i - 1].first != vec[i].first)
				++newPri;
			suffixArr[vec[i].second] = newPri;
		}
	}

	order.resize(n + 1);
	for (int i = 1; i < n + 1; ++i)
		order[i] = { suffixArr[i], i };
	std::sort(order.begin(), order.end());

	for (int i = 0; i < k; ++i)
	{
		std::string query;
		std::cin >> query;

		std::cout << upperBound(0, n + 1, query) - lowerBound(0, n + 1, query) << "\n";
	}

	return 0;
}