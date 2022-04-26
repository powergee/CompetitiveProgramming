#include <iostream>
#include <string>

bool isHappy(int v) {
    std::string str = std::to_string(v);
    for (int i = 0; i+1 < str.size(); ++i) {
        if (str[i] > str[i+1]) {
            return false;
        }
    }
    return true;
}

int main() {
    int n;
    scanf("%d", &n);

    int count = 0;
    for (int i = 1; i <= n; ++i) {
        count += (isHappy(i) ? 1 : 0);
    }
    printf("%d", count);

    return 0;
}