#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);

	int n;
	std::cin >> n;
	std::string str;
	std::cin >> str;

    if (n == 1) {
        std::cout << "0";
        return 0;
    }
	
	std::vector<int> sa(n);
	std::iota(sa.begin(), sa.end(), 0);

	std::vector<int> group(n);
	for (int i = 0; i < n; ++i) {
		group[i] = str[i] - 'a';
	}

	for (int d = 1; ; d <<= 1) {
		auto compareSuffix = [&](int s1, int s2) {
			if (group[s1] != group[s2]) {
				return group[s1] < group[s2];
			} else if (s1+d < n && s2+d < n) {
				return group[s1 + d] < group[s2 + d];
			} else {
				return s1 > s2;
			}
		};

		std::sort(sa.begin(), sa.end(), compareSuffix);

		std::vector<int> newGroup(n, 0);
		for (int i = 0; i+1 < n; ++i) {
			newGroup[i + 1] = newGroup[i] + (compareSuffix(sa[i], sa[i + 1]) ? 1 : 0);
		}
		for (int i = 0; i < n; ++i) {
			group[sa[i]] = newGroup[i];
		}

		if (newGroup.back() == n - 1) {
			break;
		}
	}

	std::vector<int> lcp(n - 1);
	int lcpVal = 0;
	for (int i = 0; i < n; ++i) {
		lcpVal = std::max(0, lcpVal-1);
		if (group[i] != n - 1) {
			for (int j = sa[group[i] + 1]; str[i + lcpVal] == str[j + lcpVal]; ++lcpVal);
			lcp[group[i]] = lcpVal;
		}
	}

	std::cout << *std::max_element(lcp.begin(), lcp.end());

	return 0;
}