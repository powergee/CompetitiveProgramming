#include <iostream>
#include <vector>
#include <algorithm>

double dp[301][301][301];

int main() {
    int n;
    scanf("%d", &n);

    int count[4] = {};
    for (int i = 0; i < n; ++i) {
        int c;
        scanf("%d", &c);
        count[c]++;
    }
    
    std::function<double(int, int, int)> getExpected = [&](int c1, int c2, int c3) -> double {
        if (c1 == 0 && c2 == 0 && c3 == 0) {
            return 0;
        }

        double& result = dp[c1][c2][c3];
        if (result != 0) {
            return result;
        }

        double sum = c1+c2+c3;
        double exp = 0;
        if (c1) {
            exp += c1/sum * getExpected(c1-1, c2, c3);
        }
        if (c2) {
            exp += c2/sum * getExpected(c1+1, c2-1, c3);
        }
        if (c3) {
            exp += c3/sum * getExpected(c1, c2+1, c3-1);
        }
        return result = (n/sum) + exp;
    };
    printf("%.10lf", getExpected(count[1], count[2], count[3]));

    return 0;
}