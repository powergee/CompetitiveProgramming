#include <iostream>

char map[20][21];

int main() {
    int n;
    scanf("%d", &n);
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == 0 || j == 0 || i == n-1 || j == n-1 || i == j || i+j == n-1) {
                map[i][j] = '*';
            } else {
                map[i][j] = ' ';
            }
        }
        printf("%s\n", map[i]);
    }
}