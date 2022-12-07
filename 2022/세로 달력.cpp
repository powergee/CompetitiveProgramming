#include <iostream>
#include <vector>

int main() {
    int n, dow;
    std::cin >> n >> dow;
    dow--;

    std::vector<std::pair<int, int>> calendar[7];
    bool leap = (n % 4 == 0) && ((n % 400 == 0) || (n % 100 != 0));

    int DAYS[12] {
        31, (leap ? 29 : 28), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
    };

    for (int month = 0; month < 12; ++month) {
        for (int day = 0; day < DAYS[month]; ++day) {
            calendar[dow].emplace_back(month, day);
            dow = (dow+1) % 7;
        }
    }

    int answer = 0;
    for (int i = 0; i < 7; ++i) {
        int start = 0;
        for (size_t j = 1; j < calendar[i].size(); ++j) {
            if (calendar[i][j-1].first != calendar[i][j].first) {
                start = j;
            }
            if (j - start == 4) {
                ++answer;
            }
        }
    }

    std::cout << answer;

    return 0;
}