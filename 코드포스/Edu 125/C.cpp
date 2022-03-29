#include <iostream>
#include <vector>

char str[500001];

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        scanf("%s", str);
        int totalRemoved = 0, operCount = 0, currStart = 0;
        int regCounter = 0, regMin = 0;
        char palFirst = 0;
        for (int i = 0; i < n; ++i) {
            if (palFirst == '\0') {
                currStart = i;
                regCounter = (str[i] == '(' ? 1 : -1);
                regMin = regCounter;
                palFirst = str[i];
            } else {
                regCounter += (str[i] == '(' ? 1 : -1);
                regMin = std::min(regMin, regCounter);
                if ((regCounter == 0 && regMin >= 0) || palFirst == str[i]) {
                    operCount++;
                    totalRemoved += i-currStart+1;
                    palFirst = '\0';
                }
            }
        }

        printf("%d %d\n", operCount, n-totalRemoved);
    }

    return 0;
}