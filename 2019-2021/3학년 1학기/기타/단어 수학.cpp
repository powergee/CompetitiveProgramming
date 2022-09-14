#include <iostream>
#include <string>
#include <algorithm>

long long coeff[26];

int main() {
    int n;
    std::cin >> n;

    for (int i = 0; i < n; ++i) {
        std::string word;
        std::cin >> word;

        int e = 1;
        for (auto ch = word.rbegin(); ch != word.rend(); ++ch) {
            coeff[*ch-'A'] += e;
            e *= 10;
        }
    }

    std::sort(coeff, coeff+26, std::greater<int>());

    long long result = 0;
    for (int i = 0; i < 9; ++i) {
        result += coeff[i]*(9-i);
    }

    std::cout << result;

    return 0;
}