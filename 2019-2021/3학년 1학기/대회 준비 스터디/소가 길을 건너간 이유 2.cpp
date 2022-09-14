#include <iostream>
#include <algorithm>

int main() {
    char str[53];
    int answer = 0;
    scanf("%s", str);

    for (char c = 'A'; c <= 'Z'; ++c) {
        int l, r;
        for (int i = 0; i < 52; ++i) {
            if (str[i] == c) {
                l = i;
                break;
            }
        }
        for (int i = 51; i >= 0; --i) {
            if (str[i] == c) {
                r = i;
                break;
            }
        }

        int count[26];
        std::fill(count, count+26, 0);
        for (int i = l+1; i < r; ++i) {
            count[str[i]-'A']++;
            if (count[str[i]-'A'] == 1) {
                ++answer;
            } else {
                --answer;
            }
        }
    }

    printf("%d", answer/2);
    return 0;
}