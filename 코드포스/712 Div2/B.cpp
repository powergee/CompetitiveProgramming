#include <iostream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int T;
    std::cin >> T;

    while (T--) {
        int n;
        std::string a, b;
        std::cin >> n >> a >> b;

        std::vector<bool> isSame;
        int count[2] = {0, 0};
        bool yes = true;
        int lastChecked = -1;
        for (int i = 0; i < n; ++i) {
            if (a[i] == b[i]) {
                isSame.push_back(true);
            } else {
                isSame.push_back(false);
            }

            count[a[i]-'0']++;

            if (count[0] == count[1]) {
                lastChecked = i;
                bool before = isSame[0];
                bool allSame = true;

                for (bool s : isSame) {
                    if (s != before) {
                        allSame = false;
                        break;
                    }
                }

                if (!allSame) {
                    yes = false;
                    break;
                } else {
                    isSame.clear();
                    count[0] = count[1] = 0;
                }
            }
        }

        for (int i = lastChecked+1; i < n; ++i) {
            if (a[i] != b[i]) {
                yes = false;
                break;
            }
        }

        if (yes) {
            std::cout << "YES\n";
        } else {
            std::cout << "NO\n";
        }
    }
}