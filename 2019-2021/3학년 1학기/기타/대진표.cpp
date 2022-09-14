#include <iostream>

void printWord(char token, int count) {
    for (int i = 0; i < count; ++i) {
        putchar(token);
    }
}

void printAnswer(int total, int player) {
    if (total == 1) {
        printWord('#', player);
        printWord('.', total - player);
    } else if (player < total / 2) {
        printAnswer(total / 2, player);
        printWord('.', total / 2);
    } else {
        int half = total / 2;
        int right = 1;
        while (right*2 <= player-right*2 && right*2 <= total-half) {
            right *= 2;
        }

        if (player-right > half) {
            right = player - half;
        }
        printAnswer(half, player-right);
        printAnswer(total-half, right);
    }
}

void printAnswer(int n) {
    int total = 1;
    while (total < n) {
        total <<= 1;
    }
    printAnswer(total, n);
}

int main() {
    int n;
    scanf("%d", &n);
    printAnswer(n);

    return 0;
}