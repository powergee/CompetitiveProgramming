#include <iostream>

int main() {
    double x, y, z;
    scanf("%lf %lf %lf", &x, &y, &z);

    // y/x > z/?

    int answer = 0;
    for (int v = 0; v < 1e9; ++v) {
        if (x/y >= z/v) {
            break;
        } else {
            answer = v;
        }
    }

    std::cout << answer;

    return 0;
}