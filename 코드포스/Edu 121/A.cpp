#include <iostream>
#include <cstring>
#include <algorithm>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        char str[100];
        scanf("%s", str);
        int n = std::strlen(str);
        std::sort(str, str+n);
        printf("%s\n", str);
    }

    return 0;
}