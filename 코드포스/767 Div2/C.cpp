#include <iostream>
#include <vector>
#include <set>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        std::vector<int> arr(n);
        for (int i = 0; i < n; ++i) {
            scanf("%d", &arr[i]);
        }

        std::vector<int> backMEX(n);
        std::set<int> current;
        int mexCand = 0;
        for (int i = n-1; i >= 0; --i) {
            current.insert(arr[i]);
            while (current.find(mexCand) != current.end()) {
                ++mexCand;
            }
            backMEX[i] = mexCand;
        }

        std::vector<int> answer;
        for (int i = 0; i < n;) {
            current.clear();
            mexCand = 0;
            bool found = false;

            for (int j = i; j < n; ++j) {
                current.insert(arr[j]);
                while (current.find(mexCand) != current.end()) {
                    ++mexCand;
                }
                if (backMEX[i] == mexCand) {
                    answer.push_back(mexCand);
                    i = j+1;
                    found = true;
                    break;
                }
            }
        }

        printf("%d\n", (int)answer.size());
        for (int ans : answer) {
            printf("%d ", ans);
        }
        printf("\n");
    }

    return 0;
}