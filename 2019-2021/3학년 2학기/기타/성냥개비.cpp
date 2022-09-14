#include <iostream>
#include <algorithm>
#include <string>

const int COST[10] { 6, 2, 5, 5, 4, 5, 6, 3, 7, 7 };
std::string minDP[101], maxDP[101];

const std::string MIN = "";
const std::string MAX = std::string(101, '9');

bool isRightGreater(std::string& left, std::string& right) {
    if (left.size() != right.size()) {
        return left.size() < right.size();
    } else {
        return left < right;
    }
}

std::string& getMinNumber(int sticks) {
    std::string& result = minDP[sticks];
    if (result != "-") {
        return result;
    }

    result = MAX;
    for (int i = 0; i < 10; ++i) {
        if (sticks == COST[i] && i > 0) {
            std::string curr = std::to_string(i);
            if (isRightGreater(curr, result)) {
                result = curr;
            }
        } else if (COST[i] < sticks) {
            std::string& next = getMinNumber(sticks-COST[i]);
            if (next != MAX) {
                std::string curr = next + std::to_string(i);
                if (isRightGreater(curr, result)) {
                    result = curr;
                }
            }
        }
    }
    return result;
}

std::string& getMaxNumber(int sticks) {
    std::string& result = maxDP[sticks];
    if (result != "-") {
        return result;
    }

    result = MIN;
    for (int i = 0; i < 10; ++i) {
        if (sticks == COST[i] && i > 0) {
            std::string curr = std::to_string(i);
            if (isRightGreater(result, curr)) {
                result = curr;
            }
        } else if (COST[i] < sticks) {
            std::string& next = getMaxNumber(sticks-COST[i]);
            if (next != MIN) {
                std::string curr = next + std::to_string(i);
                if (isRightGreater(result, curr)) {
                    result = curr;
                }
            }
        }
    }
    return result;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::fill(minDP, minDP+sizeof(minDP)/sizeof(std::string), "-");
    std::fill(maxDP, maxDP+sizeof(maxDP)/sizeof(std::string), "-");

    int T;
    std::cin >> T;

    while (T--) {
        int n;
        std::cin >> n;
        std::cout << getMinNumber(n) << " " << getMaxNumber(n) << "\n";
    }

    return 0;
}