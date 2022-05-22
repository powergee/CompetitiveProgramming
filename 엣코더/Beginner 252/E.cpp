#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>
#include <set>
#include <queue>
#include <tuple>

typedef long long Long;
using Edge = std::tuple<int, int, int>;
using DijkstraState = std::tuple<Long, int, int>;

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);

	int n, m;
	std::cin >> n >> m;

	std::vector<std::vector<Edge>> graph(n+1);
	
	for (int i = 0; i < m; ++i) {
		int a, b, c;
		std::cin >> a >> b >> c;
		graph[a].emplace_back(b, c, i);
		graph[b].emplace_back(a, c, i);
	}

	std::priority_queue<DijkstraState, std::vector<DijkstraState>, std::greater<DijkstraState>> q;
	std::vector<Long> dist(n+1, INT64_MAX/2);
	std::vector<int> from(n+1, -1);

	dist[1] = 0;
	for (auto [next, cost, index] : graph[1]) {
		q.emplace(cost, next, index);
		dist[next] = cost;
	}

	while (!q.empty()) {
		auto [cost, curr, index] = q.top();
		q.pop();

		if (cost > dist[curr]) {
			continue;
		}
		from[curr] = index;
		for (auto [next, nextCost, nextIndex] : graph[curr]) {
			Long newCost = nextCost+dist[curr];
			if (newCost < dist[next]) {
				dist[next] = newCost;
				q.emplace(newCost, next, nextIndex);
			}
		}
	}

	for (int i = 2; i <= n; ++i) {
		std::cout << from[i]+1 << " ";
	}

	return 0;
}