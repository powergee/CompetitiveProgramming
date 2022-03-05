#include <iostream>

int main() {
    int a, b, c, x;
    std::cin >> a >> b >> c >> x;
    
    if (x <= a) {
        printf("1");
    } else if (x <= b) {
        printf("%.10lf", c/double(b-a));
    } else {
        printf("0\n");
    }

    return 0;
}