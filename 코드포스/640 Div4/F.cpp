#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>

enum Selection { Undefined, NN, NP, PN, PP, End, Impossible };

Selection dp[2][101][101][101];

Selection getPossibleNext(int curr, int nn, int np, int pp) {
    Selection& result = dp[curr][nn][np][pp];
    if (result != Undefined) {
        return result;
    }

    if (nn == 0 && np == 0 && pp == 0) {
        return result = End;
    } else if (curr == 0 && nn > 0 && getPossibleNext(0, nn-1, np, pp) != Impossible) {
        return result = NN;
    } else if (curr == 0 && np > 0 && getPossibleNext(1, nn, np-1, pp) != Impossible) {
        return result = NP;
    } else if (curr == 1 && np > 0 && getPossibleNext(0, nn, np-1, pp) != Impossible) {
        return result = PN;
    } else if (curr == 1 && pp > 0 && getPossibleNext(1, nn, np, pp-1) != Impossible) {
        return result = PP;
    } else {
        return result = Impossible;
    }
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int nn, np, pp;
        scanf("%d %d %d", &nn, &np, &pp);
        int curr = -1;
        if (getPossibleNext(0, nn, np, pp) != Impossible) {
            curr = 0;
        } else {
            curr = 1;
        }

        putchar(char('0'+curr));
        while (nn > 0 || np > 0 || pp > 0) {
            switch (getPossibleNext(curr, nn, np, pp)) {
                case NN:
                    curr = 0;
                    nn--;
                    break;
                case NP:
                    curr = 1;
                    np--;
                    break;
                case PN:
                    curr = 0;
                    np--;
                    break;
                case PP:
                    curr = 1;
                    pp--;
                    break;
                default:
                    printf("Failed: %d %d %d %d -> %d", curr, nn, np, pp, getPossibleNext(curr, nn, np, pp));
                    exit(1);
                    break;
            }
            putchar(char('0'+curr));
        }
        putchar('\n');
    }

    return 0;
}