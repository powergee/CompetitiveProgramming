#include <iostream>
#include <string>
#include <algorithm>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    std::cin >> n;

    int length = 1;
    while (length < n) {
        length *= 2;
    }
    std::string answer(length, '.');

    std::function<void(int, int, int)> assignPlayers = [&](int left, int right, int players) -> void {
        if (left == right) {
            answer[left] = (players ? '#' : '.');
            return;
        }

        int mid = (left+right) / 2;
        if (players <= right-mid) {
            assignPlayers(left, mid, players);
            return;
        }

        int pow = 1;
        while (pow*2 <= players-pow*2) {
            pow *= 2;
        }
        if (mid-left+1 < players-pow) {
            std::fill(answer.begin()+left, answer.begin()+mid+1, '#');
            assignPlayers(mid+1, right, players-(right-mid));
        } else {
            assignPlayers(left, mid, players-pow);
            std::fill(answer.begin()+mid+1, answer.begin()+mid+pow+1, '#');
        }
    };
    assignPlayers(0, length-1, n);

    std::cout << answer;

    return 0;
}