#include <iostream>
#include <string>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        long long n;
        scanf("%lld", &n);

        int answer = 0;
        for (int e = 1; e <= 10; ++e) {
            for (int d = 1; d <= 9; ++d) {
                std::string numStr;
                for (int i = 0; i < e; ++i) {
                    numStr += std::to_string(d);
                }
                if (std::stoll(numStr) <= n) {
                    ++answer;
                }
            }
        }

        printf("%d\n", answer);
    }

    return 0;
}