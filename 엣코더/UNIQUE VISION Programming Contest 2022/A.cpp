#include <iostream>

int main() {
    char input[10];
    scanf("%s", input);
    bool exist[10] = {0,};
    for (int i = 0; i < 10; ++i) {
        exist[input[i]-'0'] = true;
    }
    for (int i = 0; i < 10; ++i) {
        if (!exist[i]) {
            printf("%d", i);
        }
    }

    return 0;
}