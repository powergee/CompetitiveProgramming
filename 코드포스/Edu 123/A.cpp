#include <iostream>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        char map[7];
        scanf("%s", map);

        bool redKey = false, blueKey = false, greenKey = false, failed = false;
        for (int i = 0; i < 6; ++i) {
            switch (map[i])
            {
            case 'R':
                if (!redKey) {
                    failed = true;
                }
                break;
            case 'G':
                if (!greenKey) {
                    failed = true;
                }
                break;
            case 'B':
                if (!blueKey) {
                    failed = true;
                }
                break;
            case 'r':
                redKey = true;
                break;
            case 'g':
                greenKey = true;
                break;
            case 'b':
                blueKey = true;
                break;
            }
        }

        if (failed) {
            printf("NO\n");
        } else {
            printf("YES\n");
        }
    }

    return 0;
}