#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>
#include <set>

typedef long long Long;

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);

	int n;
	std::cin >> n;

	std::vector<int> arr(n);
	for (int i = 0; i < n; ++i) {
		std::cin >> arr[i];
	}

	int max = *std::max_element(arr.begin(), arr.end());
	std::vector<int> count(max+1, 0);
	Long answer = 0, multSum = 0;
	for (int i = 0; i < 2; ++i) {
		count[arr[i]]++;
		multSum += (i+1)-count[arr[i]];
	}

	for (Long i = 2; i < n; ++i) {
		answer += multSum - count[arr[i]]*(i-count[arr[i]]);
		count[arr[i]]++;
		multSum += (i+1)-count[arr[i]];
	}

	std::cout << answer;

	return 0;
}