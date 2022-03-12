#include <iostream>

int main() {
    int v, use[3];
    scanf("%d %d %d %d", &v, use, use+1, use+2);

    const char* rep = "FMT";
    int turn = 0;
    while (v >= use[turn]) {
        v -= use[turn];
        turn = (turn+1) % 3;
    }

    printf("%c", rep[turn]);

    return 0;
}