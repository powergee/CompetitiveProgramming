#include <iostream>

int x[500];
int answer[500][500];
int n;

bool isValid(int r, int c) {
    return (0 <= r && r < n && 0 <= c && c <= r);
} 

void downDFS(int r, int c, int val, int remain) {
    answer[r][c] = val;
    
    if (remain == 1) {
        return;
    }

    if (isValid(r, c-1) && answer[r][c-1] == 0) {
        downDFS(r, c-1, val, remain-1);
    } else if (isValid(r+1, c) && answer[r+1][c] == 0) {
        downDFS(r+1, c, val, remain-1);
    }
}

void leftDFS(int r, int c, int val, int remain) {
    answer[r][c] = val;
    
    if (remain == 1) {
        return;
    }

    if (isValid(r+1, c) && answer[r+1][c] == 0) {
        leftDFS(r+1, c, val, remain-1);
    } else if (isValid(r, c-1) && answer[r][c-1] == 0) {
        leftDFS(r, c-1, val, remain-1);
    }
}

void DFS(int r, int c, int val, int remain) {
    answer[r][c] = val;
    
    if (remain == 1) {
        return;
    }

    if (isValid(r+1, c) && answer[r+1][c] == 0) {
        DFS(r+1, c, val, remain-1);
    } else if (isValid(r, c-1) && answer[r][c-1] == 0) {
        DFS(r, c-1, val, remain-1);
    } else if (isValid(r-1, c) && answer[r-1][c] == 0) {
        DFS(r-1, c, val, remain-1);
    } else if (isValid(r, c+1) && answer[r][c+1] == 0) {
        DFS(r, c+1, val, remain-1);
    }
}

int main() {
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        scanf("%d", x+i);
    }

    for (int i = 0; i < n/2; ++i) {
        downDFS(i, i, x[i], x[i]);
        leftDFS(n-i-1, n-i-1, x[n-i-1], x[n-i-1]);
    }

    if (n % 2) {
        DFS(n/2, n/2, x[n/2], x[n/2]);
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= i; ++j) {
            printf("%d ", answer[i][j]);
        }
        printf("\n");
    }
    return 0;
}