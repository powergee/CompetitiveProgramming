#include <iostream>
#include <map>
 
std::map<std::pair<int, int>, int> dp;
 
int query(int left, int right) {
    auto p = std::make_pair(left, right);
    if (dp.find(p) != dp.end()) {
        return dp[p];
    }
 
    printf("? %d %d\n", left+1, right+1);
    fflush(stdout);
    int respond;
    scanf("%d", &respond);
    dp[p] = respond;
 
    return respond;
}
 
void answer(int x) {
    printf("! %d\n", x+1);
    fflush(stdout);
}
 
void findkthZero(int left, int right, int k) {
    if (left == right) {
        answer(left);
        return;
    }
 
    int med = (right + left) / 2;
    int leftZeroCount = (med-left+1) - query(left, med);
    if (leftZeroCount >= k) {
        findkthZero(left, med, k);
        dp[std::make_pair(left, med)]++;
    } else {
        findkthZero(med+1, right, k-leftZeroCount);
    }
}
 
int main() {
    int n, t;
    scanf("%d %d", &n, &t);
    
    while (t--) {
        int k;
        scanf("%d", &k);
        findkthZero(0, n-1, k);
    }
 
    return 0;
}