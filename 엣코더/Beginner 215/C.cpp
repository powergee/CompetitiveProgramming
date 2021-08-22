#include <iostream>
#include <algorithm>
#include <string>

int main() {
    int k;
    std::string line;
    std::cin >> line >> k;

    std::sort(line.begin(), line.end());
    do {
        if (k == 1) {
            break;
        }
        --k;
    } while (std::next_permutation(line.begin(), line.end()));

    std::cout << line;

    return 0;
}