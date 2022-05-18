#include <iostream>
#include <deque>
#include <algorithm>
#include <string>

int main() {
    int T;
    std::cin >> T;

    while (T--) {
        std::string src, dst;
        std::cin >> src >> dst;

        std::deque<char> dstLeft, dstRight(dst.begin(), dst.end());
        bool yes = true;
        while (!dstRight.empty()) {
            if (dstLeft.size() + dstRight.size() > src.size() || src.size() <= dstLeft.size()) {
                yes = false;
                break;
            }
            int index = dstLeft.size();
            char goal = src[index];
            char curr = dstRight.front();
            dstRight.pop_front();

            if (curr == goal) {
                dstLeft.push_back(curr);
            } else if (curr > goal) {
                dstRight.push_front(curr-1);
                dstRight.push_front(curr-1);
            } else {
                yes = false;
                break;
            }
        }
        if (dstLeft.size() != src.size()) {
            yes = false;
        }

        printf(yes ? "YES\n" : "NO\n");
    }

    return 0;
}