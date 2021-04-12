#include <iostream>
#include <string>

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    std::string result = "";
    while (result.size() < n) {
        for (char c = 'a'; c < 'a'+k && result.size() < n; ++c) {
            result += c;
            for (char d = c+1; d < 'a'+k && result.size() < n; ++d) {
                result += c;
                result += d;
            }
        }
    }

    std::cout << result.substr(0, n);

    return 0;
}