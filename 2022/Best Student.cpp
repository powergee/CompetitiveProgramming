#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <cmath>
#include <cassert>

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);

	int n, q;
	std::cin >> n >> q;

	std::vector<int> arr(n);
	for (int i = 0; i < n; ++i) {
		std::cin >> arr[i];
	}

	std::vector<int> comp = arr;
	std::sort(comp.begin(), comp.end());
	comp.erase(std::unique(comp.begin(), comp.end()), comp.end());
	
	for (int i = 0; i < n; ++i) {
		arr[i] = std::lower_bound(comp.begin(), comp.end(), arr[i]) - comp.begin();
	}

	using Query = std::tuple<int, int, int>;
	std::vector<Query> queries(q);
	for (int i = 0; i < q; ++i) {
		int l, r;
		std::cin >> l >> r;
		l--; r--;
		queries[i] = { l, r, i };
	}

	int SQRT = int(std::sqrt(n)) + 1;
	std::sort(queries.begin(), queries.end(), [&](const Query& q1, const Query& q2) {
		auto [l1, r1, i1] = q1;
		auto [l2, r2, i2] = q2;
		int g1 = r1 / SQRT;
		int g2 = r2 / SQRT;

		if (g1 != g2) {
			return g1 < g2;
		} else {
			return l1 < l2;
		}
	});

	SQRT = 1000;
	std::vector<int> countPerValue(comp.size(), 0);
	std::vector<int> countCount(n + 1, 0);
	std::vector<std::vector<int>> countCountPerGroup(comp.size() / SQRT + 1, std::vector<int>(n + 1, 0));
	std::vector<int> maxCountPerGroup(comp.size() / SQRT + 1, 0);
	int maxCount = 0;

	auto insertValue = [&](int arrIdx) {
		// global count
		int prevCount = countPerValue[arr[arrIdx]]++;
		countCount[prevCount]--;
		countCount[prevCount + 1]++;
		maxCount = std::max(maxCount, prevCount + 1);
		// group count
		int group = arr[arrIdx] / SQRT;
		countCountPerGroup[group][prevCount]--;
		countCountPerGroup[group][prevCount + 1]++;
		maxCountPerGroup[group] = std::max(maxCountPerGroup[group], prevCount + 1);
	};

	auto removeValue = [&](int arrIdx) {
		// global count
		int prevCount = countPerValue[arr[arrIdx]]--;
		countCount[prevCount]--;
		countCount[prevCount - 1]++;
		if (countCount[maxCount] == 0) {
			maxCount--;
		}
		// group count
		int group = arr[arrIdx] / SQRT;
		countCountPerGroup[group][prevCount]--;
		countCountPerGroup[group][prevCount - 1]++;
		if (countCountPerGroup[group][maxCountPerGroup[group]] == 0) {
			maxCountPerGroup[group]--;
		}
	};
	
	std::vector<int> answer(q);
	std::pair<int, int> curr = { 0, 0 };

	countPerValue[arr[0]]++;
	countCount[1]++;
	countCount[0] += n - 1;
	maxCount = 1;

	for (int i = 0; i < countCountPerGroup.size(); ++i) {
		countCountPerGroup[i][0] += SQRT;
	}
	maxCountPerGroup[arr[0] / SQRT]++;
	countCountPerGroup[arr[0] / SQRT][0]--;
	countCountPerGroup[arr[0] / SQRT][1]++;

	for (auto [l, r, qi] : queries) {
		while (curr.second < r) {
			insertValue(++curr.second);
		}
		while (l < curr.first) {
			insertValue(--curr.first);
		}
		while (r < curr.second) {
			removeValue(curr.second--);
		}
		while (curr.first < l) {
			removeValue(curr.first++);
		}
		
		int found = -1;
		for (int group = maxCountPerGroup.size()-1; group >= 0; --group) {
			if (maxCountPerGroup[group] != maxCount) {
				continue;
			}
			for (int v = std::min((group+1)*SQRT-1, int(comp.size())-1); v >= group*SQRT; --v) {
				if (countPerValue[v] == maxCount) {
					found = v;
					goto BREAK;
				}
			}
			assert(false);
		} BREAK:
		assert(found != -1);
		answer[qi] = found;
	}

	for (int i = 0; i < q; ++i) {
		std::cout << comp[answer[i]] << "\n";
	}


	return 0;
}