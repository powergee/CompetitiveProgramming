#include <iostream>
#include <algorithm>
#include <map>

struct State {
    int baseline; // [0, N]
    int r[4]; // [0, 2]

    void reduceBaseline() {
        int minR = *std::min_element(r, r+4);
        if (minR) {
            for (int i = 0; i < 4; ++i) {
                r[i] -= minR;
            }
            baseline -= minR;
        }
    }

    bool canPutVertical(int top) {
        return baseline > 0 &&
               top+1 < 4 &&
               r[top] == r[top+1] &&
               r[top] == 0;
    }

    State putVertical(int top) {
        State result = *this;
        result.r[top]++;
        result.r[top+1]++;
        result.reduceBaseline();
        return result;
    }

    bool canPutHorizontal(int pos) {
        return baseline > 1 &&
               r[pos] == 0;
    }

    State putHorizontal(int pos) {
        State result = *this;
        result.r[pos] += 2;
        result.reduceBaseline();
        return result;
    }

    int getHash() const {
        return r[0] + 3*r[1] + 9*r[2] + 27*r[3] + 81*baseline;
    }

    bool operator<(const State& s) const {
        return getHash() < s.getHash();
    }
};

std::map<State, int> dp;

int countCases(State goal) {
    if (goal.baseline == 0) {
        return 1;
    }
    
    if (dp.find(goal) != dp.end()) {
        return dp[goal];
    }

    int result = 0;
    bool added = false;
    for (int pos = 0; pos < 4 && !added; ++pos) {
        if (goal.canPutVertical(pos)) {
            result += countCases(goal.putVertical(pos));
            added = true;
        }
        if (goal.canPutHorizontal(pos)) {
            result += countCases(goal.putHorizontal(pos));
            added = true;
        }
    }

    dp[goal] = result;
    return result;
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);
        State init = {
            n, { 0, 0, 0, 0 }
        };
        printf("%d\n", countCases(init));
    }

    return 0;
}