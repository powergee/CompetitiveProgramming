#include <iostream>
#include <algorithm>
#include <unordered_set>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        unsigned int n, m;
        scanf("%u %u", &n, &m);
        unsigned int p = m+1;

        unsigned int k = 0;
        for (int i = 31; i >= 0; --i) {
            int pBit = (p & (1<<i)) ? 1 : 0;
            int nBit = (n & (1<<i)) ? 1 : 0;
            
            if (pBit > nBit) {
                k |= (1<<i);
            } else if (pBit < nBit) {
                break;
            }
        }

        printf("%u\n", k);
    }
    
    return 0;
}