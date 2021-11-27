#include <cstdio>
#include <iostream>

int main() {
    char map[2][3];
    scanf("%s%s", map[0], map[1]);

    if (map[0][0] == map[1][1] && map[0][1] == map[1][0] && map[0][0] != map[0][1]) {
        printf("No");
    } else {
        printf("Yes");
    }

    return 0;
}
