#include <iostream>
#include <string>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string n1, n2;
    std::cin >> n1 >> n2;

    std::reverse(n1.begin(), n1.end());
    std::reverse(n2.begin(), n2.end());

    int maxLength = std::max(n1.size(), n2.size());
    std::string result(maxLength, '0');
    int carry = 0;

    for (int i = 0; i < maxLength; ++i) {
        if (n1.size() <= i) {
            result[i] = n2[i] + carry;
        } else if (n2.size() <= i) {
            result[i] = n1[i] + carry;
        } else {
            result[i] = n1[i] + n2[i] + carry - '0';
        }

        carry = (result[i]-'0') / 10;
        result[i] = (result[i]-'0') % 10 + '0';
    }

    while (carry > 0) {
        result += carry % 10 + '0';
        carry /= 10;
    }

    std::reverse(result.begin(), result.end());

    std::cout << result;

    return 0;
}