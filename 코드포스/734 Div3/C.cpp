#include <iostream>
#include <string>
#include <algorithm>

class Count {
private:
    int val[5];

public:
    Count() {
        std::fill(val, val+5, 0);
    }
    
    Count(const std::string& str) : Count() {
        for (char ch : str) {
            val[ch-'a']++;
        }
    }

    int getTotal() const {
        int sum = 0;
        for (int i = 0; i < 5; ++i) {
            sum += val[i];
        }
        return sum;
    }

    int& operator[](int index) {
        return val[index];
    }
};

std::string words[200000];
Count counts[200000];
int diff[200000];

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--) {
        int n;
        std::cin >> n;

        for (int i = 0; i < n; ++i) {
            std::cin >> words[i];
            counts[i] = Count(words[i]);
        }

        int answer = 0;
        for (int s = 0; s < 5; ++s) {
            for (int i = 0; i < n; ++i) {
                diff[i] = counts[i][s] - (counts[i].getTotal() - counts[i][s]);
            }

            std::sort(diff, diff+n, std::greater<int>());
            int selected = 0;
            int sum = 0;
            for (int i = 0; i < n; ++i) {
                if (sum + diff[i] > 0) {
                    selected++;
                    sum += diff[i];
                } else {
                    break;
                }
            }

            answer = std::max(answer, selected);
        }

        printf("%d\n", answer);
    }

    return 0;
}