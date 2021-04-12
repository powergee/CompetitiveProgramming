#include <iostream>
#include <string>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);

        int gcd = 7;
        while (std::to_string(gcd).size() < c) {
            gcd *= 7;
        }

        int x = gcd;
        while (std::to_string(x).size() < a) {
            x *= 2;
        }

        int y = gcd;
        while (std::to_string(y).size() < b) {
            y *= 3;
        }

        printf("%d %d\n", x, y);
    }
}