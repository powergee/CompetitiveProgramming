#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main() {
	int n, k;
	scanf("%d %d", &n, &k);

	std::vector<int> arr(n);
	for (int i = 0; i < n; ++i) {
		scanf("%d", &arr[i]);
	}

	int max = *std::max_element(arr.begin(), arr.end());
	bool yes = false;
	for (int i = 0; i < k; ++i) {
		int b;
		scanf("%d", &b);
		if (arr[b-1] == max) {
			yes = true;
		}
	}

	printf(yes ? "Yes" : "No");

	return 0;
}