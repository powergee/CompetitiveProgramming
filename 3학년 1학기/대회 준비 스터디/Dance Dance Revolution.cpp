#include <iostream>
#include <algorithm>

enum Position {
    center=0, up=1, left=2, down=3, right=4
};

int count = 0;
int queries[100000];
int dp[5][5][100000];

bool isBeside(Position p1, Position p2) {
    return  (p1 == up && p2 == right) ||
            (p1 == right && p2 == down) ||
            (p1 == down && p2 == left) ||
            (p1 == left && p2 == up) ||

            (p2 == up && p1 == right) ||
            (p2 == right && p1 == down) ||
            (p2 == down && p1 == left) ||
            (p2 == left && p1 == up) ||

            (p1 == center && p2 != center) ||
            (p2 == center && p1 != center);
}

bool isOpposite(Position p1, Position p2) {
    return  (p1 == up && p2 == down) ||
            (p1 == left && p2 == right) ||
            (p2 == up && p1 == down) ||
            (p2 == left && p1 == right);
}

int getMinPower(Position f1, Position f2, int index) {
    if (count <= index) {
        return 0;
    }

    if (index != 0 && f1 == f2) {
        return __INT32_MAX__ / 2;
    }

    int& result = dp[f1][f2][index];
    if (result != __INT32_MAX__) {
        return result;
    }

    Position qPos = (Position)queries[index];

    if (f1 == queries[index] || f2 == queries[index]) {
        result = std::min(result, getMinPower(f1, f2, index+1) + 1);
    }
    if (isBeside(f1, qPos)) {
        result = std::min(result, getMinPower(qPos, f2, index+1) + (f1 == center ? 2 : 3));
    }
    if (isBeside(f2, qPos)) {
        result = std::min(result, getMinPower(f1, qPos, index+1) + (f2 == center ? 2 : 3));
    }
    if (isOpposite(f1, qPos)) {
        result = std::min(result, getMinPower(qPos, f2, index+1) + 4);
    }
    if (isOpposite(f2, qPos)) {
        result = std::min(result, getMinPower(f1, qPos, index+1) + 4);
    }

    return result;
}

int main() {
    int pos;
    while (scanf("%d", &pos), pos != 0) {
        queries[count++] = pos;
    }

    std::fill(&dp[0][0][0], &dp[0][0][0] + sizeof(dp) / sizeof(int), __INT32_MAX__);
    printf("%d", getMinPower(center, center, 0));

    return 0;
}