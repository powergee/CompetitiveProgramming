#include <iostream>

int count = 0;

void move(char str[], int end) {
    ++count;
    for (int i = 0; i < end; ++i) {
        str[i] = str[i] == '1' ? '0' : '1';
    }
    std::reverse(str, str+end);
}

int main() {
    int n;
    scanf("%d", &n);

    char str[n+1];
    scanf("%s", str);
    for (int i = 0; i+1 < n; ++i) {
        if (str[i] != str[i+1]) {
            move(str, i+1);
        }
    }

    if (str[0] == '1') {
        move(str, n);
    }

    printf("%d", count);

    return 0;
}