#include <iostream>

int main() {
    int a, b, c, d, e, f, x;
    std::cin >> a >> b >> c >> d >> e >> f >> x;

    int tak = (a*b) * (x/(a+c)) + std::min((x%(a+c)), a) * b;
    int aok = (d*e) * (x/(d+f)) + std::min((x%(d+f)), d) * e;

    if (tak == aok) {
        std::cout << "Draw";
    } else if (tak < aok) {
        std::cout << "Aoki";
    } else {
        std::cout << "Takahashi";
    }

    return 0;
}