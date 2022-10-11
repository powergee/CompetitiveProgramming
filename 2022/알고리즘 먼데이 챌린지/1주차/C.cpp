#include <iostream>
#include <string>
#include <algorithm>

int main() {
    int arr[4];
    for (int i = 0; i < 4; ++i) {
        std::cin >> arr[i];
    }

    std::sort(arr, arr+4);
    int answer = 0;
    do {
        answer = std::max(answer, std::abs(arr[0]-arr[1]) + std::abs(arr[2]-arr[3]));
    } while (std::next_permutation(arr, arr+4));

    std::cout << answer;

    return 0;
}