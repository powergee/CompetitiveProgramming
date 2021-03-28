#include <iostream>
#include <cstring>
#include <vector>

int main() {
    int T;
    scanf("%d", &T);

    for (int t = 1; t <= T; ++t) {
        printf("Case #%d: ", t);

        int x, y;
        char str[1001];
        scanf("%d %d %s", &x, &y, str);
        int length = strlen(str);

        std::vector<char> refined;
        for (int i = 0; i < length; ++i) {
            if (str[i] != '?') {
                refined.push_back(str[i]);
            }
        }

        int answer = 0;
        for (int i = 0; i < (int)refined.size() - 1; ++i) {
            if (refined[i] == 'C' && refined[i+1] == 'J') {
                answer += x;
            } else if (refined[i] == 'J' && refined[i+1] == 'C') {
                answer += y;
            }
        }

        printf("%d\n", answer);
    }
}