#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        std::vector<int> arr(n);
        std::for_each(arr.begin(), arr.end(), [](int& v) { scanf("%d", &v); });

        auto isPossible_RightLeft = [&]() -> bool {
            auto curr = arr;
            long long rightHeal = 0, leftHeal = 0;
            for (int i = 1; i < n-1; ++i) {
                if (curr[i] % 2 == 1) {
                    if (rightHeal) {
                        --rightHeal;
                        ++curr[i];
                    }
                }
                rightHeal += curr[i]/2;
            }
            for (int i = n-2; i >= 1; --i) {
                if (curr[i] % 2 == 1) {
                    if (leftHeal) {
                        --leftHeal;
                        ++curr[i];
                    }
                }
                leftHeal += curr[i]/2;
            }
            for (int i = 1; i < n-1; ++i) {
                if (curr[i] % 2 == 1) {
                    return false;
                }
            }
            return true;
        };

        auto isPossible_LeftRight = [&]() -> bool {
            auto curr = arr;
            long long rightHeal = 0, leftHeal = 0;
            for (int i = n-2; i >= 1; --i) {
                if (curr[i] % 2 == 1) {
                    if (leftHeal) {
                        --leftHeal;
                        ++curr[i];
                    }
                }
                leftHeal += curr[i]/2;
            }
            for (int i = 1; i < n-1; ++i) {
                if (curr[i] % 2 == 1) {
                    if (rightHeal) {
                        --rightHeal;
                        ++curr[i];
                    }
                }
                rightHeal += curr[i]/2;
            }
            for (int i = 1; i < n-1; ++i) {
                if (curr[i] % 2 == 1) {
                    return false;
                }
            }
            return true;
        };

        if (isPossible_LeftRight() || isPossible_RightLeft()) {
            long long answer = 0;
            for (int i = 1; i < n-1; ++i) {
                answer += arr[i] / 2 + (arr[i] % 2);
            }
            printf("%lld\n", answer);
        } else {
            printf("-1\n");
        }
    }

    return 0;
}