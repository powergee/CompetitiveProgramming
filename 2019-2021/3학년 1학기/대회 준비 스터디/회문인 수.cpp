#include <iostream>
#include <vector>

std::vector<int> convert(int val, int kind) {
    std::vector<int> result;
    while (val) {
        result.push_back(val % kind);
        val /= kind;
    }

    return result;
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int input;
        scanf("%d", &input);

        bool possible = false;
        for (int i = 2; i <= 64; ++i) {
            auto converted = convert(input, i);
            bool isPalin = true;
            for (int j = 0; j < converted.size()/2; ++j) {
                if (converted[j] != converted[converted.size()-1-j]) {
                    isPalin = false;
                }
            }
            if (isPalin) {
                possible = true;
                break;
            }
        }

        if (possible) {
            printf("1\n");
        } else {
            printf("0\n");
        }
    }

    return 0;
}