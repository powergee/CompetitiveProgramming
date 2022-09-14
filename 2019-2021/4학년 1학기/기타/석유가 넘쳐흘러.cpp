#include <iostream>
#include <vector>
#include <map>

typedef long long Long;

struct Supply {
    Long speedAdd, constAdd;
};

struct State {
    Long amount, speed;
};

int main() {
    int n;
    scanf("%d", &n);

    std::vector<Long> tanks(n+1), total(n+1), leaves(n+1, 0);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", &tanks[i]);
    }

    for (int i = n; i >= 1; --i) {
        if (2*i+1 <= n) { // non-terminal
            total[i] = tanks[i] + total[2*i] + total[2*i+1];
            leaves[i] = leaves[2*i] + leaves[2*i+1];
        } else { // terminal
            total[i] = tanks[i];
            leaves[i] = 1;
        }
    }

    for (int i = 1; i <= n; ++i) {
        std::map<Long, Supply> supply;

        auto updateSupply = [&](Long toFill, Long speed) {
            Long time = toFill / speed + (toFill % speed ? 1 : 0);
            if (supply.count(time) == 0) {
                supply[time] = {0, 0};
            }
            supply[time].speedAdd += speed;
            supply[time].constAdd += (time*speed) - toFill;
        };

        updateSupply(0, leaves[i]);
        for (int from = i, to = i/2; to != 0; from = to, to = to/2) {
            updateSupply(total[2*to]+total[2*to+1]-total[from], leaves[from]);
        }

        std::vector<std::pair<Long, Supply>> supplyVec(supply.begin(), supply.end());
        auto getNextState = [](State curr, Supply add, Long timeSlices) -> State {
            curr.amount += add.constAdd + curr.speed;
            curr.speed += add.speedAdd;
            curr.amount += curr.speed * (timeSlices-1);
            return curr;
        };

        int found;
        State curr = {0, 0};
        for (found = 0; found+1 < supplyVec.size(); ++found) {
            auto [t1, add] = supplyVec[found];
            Long t2 = supplyVec[found+1].first;
            State next = getNextState(curr, add, t2-t1);
            if (total[i] <= next.amount) {
                break;
            }
            curr = next;
        }

        Long left = supplyVec[found].first;
        Long right = total[i] / leaves[i] + (total[i] % leaves[i] ? 1 : 0);
        while (left < right) {
            Long mid = (left+right)/2;
            State test = getNextState(curr, supplyVec[found].second, (mid+1)-supplyVec[found].first);
            if (test.amount < total[i]) {
                left = mid+1;
            } else {
                right = mid;
            }
        }

        printf("%lld ", left);
    }

    return 0;
}