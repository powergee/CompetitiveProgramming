#include <iostream>
#include <algorithm>

int n;
char rawTable[56];
char table[10][10];
int answer[10];
int sum[10];

bool isValid(char cond, int val) {
    switch (cond)
    {
    case '0': return val == 0;
    case '+': return val > 0;
    case '-': return val < 0;
    }
    return false;
}

int getSum(int i, int j) {
    return i == 0 ? sum[j] : sum[j] - sum[i-1];
}

bool findAnswer(int start) {
    if (start == n) {
        return true;
    }

    if (table[start][start] == '0') {
        answer[start] = 0;
        sum[start] = (start > 0 ? sum[start-1] : 0) + answer[start];
        return findAnswer(start+1);
    } else {
        int init = table[start][start] == '+' ? 1 : -10;
        int bound = table[start][start] == '+' ? 10 : -1;
        for (int v = init; v <= bound; ++v) {
            answer[start] = v;
            sum[start] = (start > 0 ? sum[start-1] : 0) + answer[start];
            bool valid = true;
            for (int row = 0; row < start; ++row) {
                if (!isValid(table[row][start], getSum(row, start))) {
                    valid = false;
                    break;
                }
            }
            if (valid && findAnswer(start+1)) {
                return true;
            }
        }
    }

    return false;
}

int main() {
    scanf("%d", &n);
    scanf("%s", rawTable);
    
    int index = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            table[i][j] = rawTable[index++];
        }
    }

    if (findAnswer(0)) {
        for (int i = 0; i < n; ++i) {
            printf("%d ", answer[i]);
        }
    } else {
        exit(-1);
    }

    return 0;
}