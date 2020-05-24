#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

std::pair<std::string, int> cards[10];
std::vector<std::vector<std::pair<std::string, int>>> sameSet;

bool comp(std::pair<std::string, int> c1, std::pair<std::string, int> c2)
{
	return c1.second < c2.second;
}

int main()
{
	int t;
	std::cin >> t;

	while (t--)
	{
		sameSet.clear();

		int n;
		std::cin >> n;

		for (int i = 0; i < n; ++i)
		{
			std::string pin;
			std::cin >> pin;
			cards[i] = { pin, i };
		}

		std::sort(cards, cards + n);

		bool in = false;
		int start, end;
		for (int i = 0; i < n - 1; ++i)
		{
			if (in)
			{
				if (cards[i].first == cards[i + 1].first)
				{
					end = i + 1;
				}
				else
				{
					in = false;
					sameSet.push_back(std::vector<std::pair<std::string, int>>());
					for (int j = start; j <= end; ++j)
						sameSet[sameSet.size() - 1].push_back(cards[j]);
				}
			}
			else
			{
				if (cards[i].first == cards[i + 1].first)
				{
					in = true;
					start = i;
					end = i + 1;
				}
			}
		}

		if (in)
		{
			sameSet.push_back(std::vector<std::pair<std::string, int>>());
			for (int j = start; j <= end; ++j)
				sameSet[sameSet.size() - 1].push_back(cards[j]);
		}

		int count = 0;
		for (auto v : sameSet)
			count += v.size() - 1;
		std::cout << count << '\n';

		if (sameSet.size() == 0)
		{
			std::sort(cards, cards + n, comp);
			for (int i = 0; i < n; ++i)
				std::cout << cards[i].first << '\n';
		}

		else
		{
			std::vector<std::pair<std::string, int>> fin;
			for (auto v : sameSet)
			{
				std::vector<std::vector<char>> used(4);
				for (int i = 0; i < 4; ++i)
					used[i].push_back(v[0].first[i]);

				for (int i = 1; i < v.size(); ++i)
				{
					for (int j = 0; j < 4; ++j)
					{
						for (char toChange = '0'; toChange <= '9'; ++toChange)
						{
							if (std::find(used[j].begin(), used[j].end(), toChange) == used[j].end())
							{
								v[i].first[j] = toChange;
								used[j].push_back(toChange);
								j = 1000;
								break;
							}
						}
					}
				}

				fin.insert(fin.end(), v.begin(), v.end());
			}

			std::sort(fin.begin(), fin.end(), comp);
			for (int i = 0; i < n; ++i)
				std::cout << fin[i].first << '\n';
		}
	}

	return 0;
}