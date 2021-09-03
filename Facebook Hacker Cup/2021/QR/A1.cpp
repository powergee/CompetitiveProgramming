#include <iostream>
#include <cstring>

char str[101];

bool isVowel(char ch) {
    return ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U';
}

int main() {
    int T;
    scanf("%d", &T);

    for (int t = 1; t <= T; ++t) {
        scanf("%s", str);
        int minCount = INT32_MAX;
        for (char pivot = 'A'; pivot <= 'Z'; ++pivot) {
            int count = 0;
            for (int i = 0; str[i] != '\0'; ++i) {
                if (pivot != str[i]) {
                    count += ((isVowel(str[i]) != isVowel(pivot)) ? 1 : 2);
                }
            }
            minCount = std::min(minCount, count);
        }
        printf("Case #%d: %d\n", t, minCount);
    }

    return 0;
}