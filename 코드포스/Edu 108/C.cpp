#include <iostream>
#include <vector>
#include <algorithm>

typedef long long Long;

std::pair<int, int> raw[200000];
std::vector<Long> arr[200001];
Long sum[200001];
Long answer[200001];

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);
        std::fill(sum+1, sum+1+n, 0);
        std::fill(answer+1, answer+1+n, 0);
        for (int i = 1; i <= n; ++i) {
            arr[i].clear();
            arr[i].push_back(0); // dummy
        }

        for (int i = 0; i < n; ++i) {
            scanf("%d", &raw[i].first);
        }
        for (int i = 0; i < n; ++i) {
            scanf("%d", &raw[i].second);
        }
        for (int i = 0; i < n; ++i) {
            arr[raw[i].first].push_back(raw[i].second);
        }

        for (int i = 1; i <= n; ++i) {
            std::sort(arr[i].begin()+1, arr[i].end(), std::greater<Long>());
            int count = (int)arr[i].size()-1;
            for (int j = 1; j <= count; ++j) {
                sum[j] = sum[j-1] + arr[i][j];
            }
            for (int d = 1; d <= count; ++d) {
                int endPoint = count - (count % d);
                answer[d] += sum[endPoint];
            }
        }

        for (int i = 1; i <= n; ++i) {
            printf("%lld ", answer[i]);
        }
        printf("\n");
    }

    return 0;
}