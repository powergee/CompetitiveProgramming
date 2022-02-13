#include <iostream>
#include <string>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int d;
    std::cin >> d;
    std::string num;
    std::cin >> num;

    for (int i = 0; i < d-1; ++i) {
        if (num[i] < num[i+1]) {
            std::swap(num[i], num[i+1]);
            break;
        }
    }

    std::cout << num << "\n";
    return 0;
}