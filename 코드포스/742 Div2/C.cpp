#include <iostream>
#include <string>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);
        std::string nStr = std::to_string(n);

        if (n < 10) {
            printf("%d\n", n-1);
        } else {
            std::string evenStr, oddStr;

            for (int i = nStr.size()-1, parity = 1; i >= 0; --i, ++parity) {
                std::string& target = (parity % 2 == 0 ? evenStr : oddStr);
                target = nStr[i] + target;
            }

            long long even = std::stoll(evenStr);
            long long odd = std::stoll(oddStr);

            printf("%lld\n", (even+1)*(odd+1)-2);
        }
    }

    return 0;
}