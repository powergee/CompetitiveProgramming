#include <iostream>
#include <map>
#include <vector>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    while (true) {
        int x;
        std::cin >> x;
        x *= 10000000;
        
        if (std::cin.eof()) {
            break;
        }

        int n;
        std::cin >> n;
        std::map<int, int> blCnt;
        std::vector<int> blSet;
        for (int i = 0; i < n; ++i) {
            int l;
            std::cin >> l;
            blSet.push_back(l);
            blCnt[l]++;
        }
        std::sort(blSet.begin(), blSet.end());

        bool found = false;
        for (int l1 : blSet) {
            if (l1*2 == x && blCnt[l1] > 1) {
                std::cout << "yes " << l1 << " " << l1 << "\n";
                found = true;
                break;
            }
            int l2 = x-l1;
            if (l1 >= l2) {
                break;
            }
            if (blCnt.find(l2) != blCnt.end() && blCnt[l2]) {
                std::cout << "yes " << l1 << " " << l2 << "\n";
                found = true;
                break;
            }
        }

        if (!found) {
            std::cout << "danger\n";
        }
    }

    return 0;
}