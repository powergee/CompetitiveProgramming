#include <iostream>
#include <vector>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template<typename T>
using OrderedSet = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int T;
    std::cin >> T;

    while (T--) {
        int n, m;
        std::cin >> n >> m;

        OrderedSet<std::pair<int, int>> movies;
        std::vector<int> index(n+1);

        for (int v = 1; v <= n; ++v) {
            index[v] = v-1;
            movies.insert(std::make_pair(index[v], v));
        }

        while (m--) {
            int want;
            std::cin >> want;
            auto key = std::make_pair(index[want], want);
            std::cout << movies.order_of_key(key) << " ";

            auto it = movies.find(key);
            int minIdx = movies.find_by_order(0)->first;
            auto bucket = *it;
            movies.erase(it);
            index[bucket.second] = minIdx-1;
            bucket.first = minIdx-1;
            movies.insert(bucket);
        }
        std::cout << "\n";
    }

    return 0;
}