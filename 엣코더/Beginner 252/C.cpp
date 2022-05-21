#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>
#include <set>

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);

	int n;
	std::cin >> n;

	std::vector<std::string> slot(n);
	for (int i = 0; i < n; ++i) {
		std::cin >> slot[i];
	}

	int answer = INT32_MAX;
	for (int v = 0; v <= 9; ++v) {
		std::set<int> jobs;
		for (int i = 0; i < n; ++i) {
			auto found = std::find(slot[i].begin(), slot[i].end(), char(v+'0'));
			int time = found-slot[i].begin();
			while (jobs.count(time) == 1) {
				time += slot[i].size();
			}
			jobs.insert(time);
		}
		answer = std::min(answer, *std::prev(jobs.end()));
	}

	std::cout << answer;

	return 0;
}