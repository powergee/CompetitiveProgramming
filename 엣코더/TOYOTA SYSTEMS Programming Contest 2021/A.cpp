#include <cstdio>
#include <iostream>

int main() {
    int s, t, x;
    scanf("%d %d %d", &s, &t, &x);
    
    bool yes = true;
    if (s < t) {
        yes = s <= x && x < t;
    } else {
        yes = s <= x || x < t;
    }
    printf(yes ? "Yes" : "No");

    return 0;
}
