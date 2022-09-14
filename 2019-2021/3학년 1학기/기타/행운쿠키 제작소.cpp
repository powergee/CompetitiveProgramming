#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>

const int UND = std::numeric_limits<int>::min();

struct Job {
    int a, b;
};

int n, aTotal, bTotal;
std::vector<Job> jobs;
int bTime[2][100001];

int getMaxRestingOfB(int start, int aRunning) {
    if (aRunning == 0 || start == n) {
        return 0;
    }

    int& result = bTime[start][aRunning];
    if (result != UND) {
        return result;
    }

    if (jobs[start].a <= aRunning) {
        result = std::max(result, getMaxRestingOfB(start+1, aRunning-jobs[start].a) + jobs[start].b);
    }
    result = std::max(result, getMaxRestingOfB(start+1, aRunning));

    return result;
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        scanf("%d", &n);
        aTotal = bTotal = 0;
        jobs.clear();

        for (int i = 0; i < n; ++i) {
            int a, b;
            scanf("%d %d", &a, &b);
            aTotal += a;
            bTotal += b;
            jobs.push_back({a, b});
        }

        for (int i = 0; i < 2; ++i) {
            std::fill(bTime[i], bTime[i]+aTotal+1, 0);
        }

        for (int i = n-1; i >= 0; --i) {
            bTime[1][0] = 0;
            for (int aRunning = 1; aRunning <= aTotal; ++aRunning) {
                if (jobs[i].a <= aRunning) {
                    bTime[1][aRunning] = std::max(bTime[1][aRunning], bTime[0][aRunning-jobs[i].a] + jobs[i].b);
                }
                bTime[1][aRunning] = std::max(bTime[1][aRunning], bTime[0][aRunning]);
            }
            std::copy(bTime[1], bTime[1]+aTotal+1, bTime[0]);
        }

        int answer = __INT32_MAX__;
        for (int aRunning = 1; aRunning <= aTotal; ++aRunning) {
            int bRunning = bTotal - bTime[1][aRunning];
            answer = std::min(answer, std::max(aRunning, bRunning));
        }

        printf("%d\n", answer);
    }
    
    return 0;
}