#include <iostream>
#include <cassert>
#include <string>

const std::string TILES[] = {
    "1.,?!",
    "2ABC",
    "3DEF",
    "4GHI",
    "5JKL",
    "6MNO",
    "7PQRS",
    "8TUV",
    "9WXYZ"
};

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    std::cin >> n;
    std::string seq;
    std::cin >> seq;

    std::string result;
    for (int i = 0; i < n;) {
        int j = seq.find_first_not_of(seq[i], i);
        if (j == seq.npos) {
            j = seq.size();
        }
        int len = j-i;
        int pressed = seq[i]-'1';
        result += TILES[pressed][(len-1)%TILES[pressed].size()];
        i = j;
    }

    std::cout << result;

    return 0;
}