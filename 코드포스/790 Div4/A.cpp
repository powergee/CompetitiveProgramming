#include <iostream>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        char ticket[7];
        scanf("%s", ticket);
        if (ticket[0]+ticket[1]+ticket[2] == ticket[3]+ticket[4]+ticket[5]) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }

    return 0;
}