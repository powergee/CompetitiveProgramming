#include <iostream>
#include <algorithm>
#define undefined -1

struct Art {
    int height, price;

    bool operator<(const Art& other) const {
        return height < other.height;
    }
};

int n, s;
Art arts[300001];
int profitDp[300001];
int maxDp[300001];

Art* findByHeight(int height);
int getMaxProfit(int start);
int getMaxSubsolution(int start);

Art* findByHeight(int height) {
    Art pivot = { height, 0 };
    return std::lower_bound(arts+1, arts+n+1, pivot);
}

int getMaxProfit(int start) {
    int& result = profitDp[start];
    if (result != undefined) {
        return result;
    }
    
    Art* current = arts + start;
    Art* next = findByHeight(current->height + s);
    result = current->price + getMaxSubsolution(next-arts);

    return result;
}

int getMaxSubsolution(int start) {
    if (n < start) {
        return 0;
    }
    if (maxDp[start] != undefined) {
        return maxDp[start];
    }

    if (start == n) {
        maxDp[start] = getMaxProfit(start);
    } else {
        maxDp[start] = std::max(getMaxProfit(start), getMaxSubsolution(start+1));
    }
    
    return maxDp[start];
}

int main() {
    scanf("%d %d", &n, &s);

    arts[0] = { 0, 0 };
    for (int i = 1; i <= n; ++i) {
        scanf("%d %d", &arts[i].height, &arts[i].price);
    }
    std::sort(arts+1, arts+n+1);
    std::fill(profitDp, profitDp+n+1, undefined);
    std::fill(maxDp, maxDp+n+1, undefined);

    printf("%d", getMaxProfit(0));

    return 0;
}