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
int bTime[250][62501];

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
    scanf("%d", &n);
    aTotal = bTotal = 0;

    for (int i = 0; i < n; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        aTotal += a;
        bTotal += b;
        jobs.push_back({a, b});
    }

    std::fill(&bTime[0][0], &bTime[0][0] + sizeof(bTime) / sizeof(int), UND);

    int answer = __INT32_MAX__;
    for (int aRunning = 1; aRunning <= aTotal; ++aRunning) {
        int bRunning = bTotal - getMaxRestingOfB(0, aRunning);
        answer = std::min(answer, std::max(aRunning, bRunning));
    }

    printf("%d", answer);
    
    return 0;
}