#include <iostream>

int main() {
    char line[5];
    scanf("%s", line);

    bool allSame = true;
    bool allFollow = true;
    for (int i = 0; i < 3; ++i) {
        if (line[i] != line[i+1]) {
            allSame = false;
        }
        if (!(line[i]+1 == line[i+1] || (line[i] == '9' && line[i+1] == '0'))) {
            allFollow = false;
        }
    }

    if (allFollow || allSame) {
        printf("Weak");
    } else {
        printf("Strong");
    }

    return 0;
}