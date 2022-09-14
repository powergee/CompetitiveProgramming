#include "findVertices.h"
#include <algorithm>

void find(int n) {
	std::vector<int> u, v;
	int isDifferent[7] = {0,};

	auto appendConnected = [&](std::vector<int>& cluster) {
		for (int i = 0; i+1 < cluster.size(); ++i) {
			u.push_back(cluster[i]);
			v.push_back(cluster[i+1]);
		}
	};

	for (int i = 0; i < 7; ++i) {
		std::vector<int> cluster[2];
		for (int j = 1; j <= n; ++j) {
			cluster[(j & (1<<i)) ? 1 : 0].push_back(j);
		}
		if (cluster[0].empty() || cluster[1].empty()) {
			continue;
		}
		u.clear(), v.clear();
		appendConnected(cluster[0]);
		appendConnected(cluster[1]);
		isDifferent[i] = query(u, v, cluster[0].front(), cluster[1].front());
	}

	int firstDifferent = std::find(isDifferent, isDifferent+7, 1)-isDifferent;
	int a = 0, b = 1 << firstDifferent;
	for (int i = 0; i < 7; ++i) {
		if (i == firstDifferent) {
			continue;
		}
		if (isDifferent[i]) {
			std::vector<int> cluster[2];
			for (int j = 1; j <= n; ++j) {
				bool isolated = (j & (1<<i)) > 0 && (j & (1<<firstDifferent)) > 0;
				cluster[isolated ? 1 : 0].push_back(j);
				
			}
			if (cluster[0].empty() || cluster[1].empty()) {
				a = a | (1<<i);
				continue;
			}
			u.clear(), v.clear();
			appendConnected(cluster[0]);
			appendConnected(cluster[1]);
			if (query(u, v, cluster[0].front(), cluster[1].front())) {
				b = b | (1<<i);
			} else {
				a = a | (1<<i);
			}
		} else {
			std::vector<int> cluster[2];
			for (int j = 1; j <= n; ++j) {
				if (j & (1<<i)) {
					cluster[j & (1<<firstDifferent) ? 1 : 0].push_back(j);
				}
			}
			if (cluster[0].empty() || cluster[1].empty()) {
				continue;
			}
			u.clear(), v.clear();
			appendConnected(cluster[0]);
			appendConnected(cluster[1]);
			if (query(u, v, cluster[0].front(), cluster[1].front())) {
				a = a | (1<<i);
				b = b | (1<<i);
			}
		}
	}

	answer(a, b);
}
