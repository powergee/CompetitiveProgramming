#include <iostream>
#include <string>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    while (true) {
        std::string name;
        int age, weight;
        std::cin >> name >> age >> weight;

        if (name == "#") {
            break;
        }

        if (age > 17 || weight >= 80) {
            std::cout << name << " " << "Senior\n";
        } else {
            std::cout << name << " " << "Junior\n";
        }
    }

    return 0;
}