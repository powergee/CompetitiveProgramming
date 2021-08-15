#include <iostream>
#include <algorithm>

char str[100001];

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);
        std::fill(str, str+n, 'a');
        str[n] = '\0';

        if (n > 1) {
            str[n/2] = 'b';
            if (n % 2 == 1) {
                str[n/2+1] = 'c';
            }
        }

        printf("%s\n", str);
    }

    return 0;
}