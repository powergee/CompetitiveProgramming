#include <iostream>

int main() {
    int a, b;
    std::cin >> a >> b;
    if (a%10 + 1 == b || b%10 + 1 == a) {
        printf("Yes");
    } else {
        printf("No");
    }

    return 0;
}