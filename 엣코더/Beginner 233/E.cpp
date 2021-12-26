#include <iostream>
#include <vector>
#include <string>

typedef long long Long;

int main() {
    std::string x;
    std::cin >> x;
    
    std::vector<Long> sum(x.size());
    for (int i = 0; i < x.size(); ++i) {
        int curr = x[i]-'0';
        if (i > 0) {
            sum[i] += sum[i-1] + curr;
        } else {
            sum[i] = curr;
        }
    }

    for (int i = int(x.size())-1; i > 0; --i) {
        sum[i-1] += sum[i] / 10;
        sum[i] %= 10;
    }

    for (int i = 0; i < x.size(); ++i) {
        printf("%lld", sum[i]);
    }

    return 0;
}