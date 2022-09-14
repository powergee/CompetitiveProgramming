#include <iostream>
#include <queue>

class MidSet {
private:
    std::priority_queue<int, std::vector<int>, std::less<int>> less;
    std::priority_queue<int, std::vector<int>, std::greater<int>> greater;

public:
    MidSet() {
        less.push(INT32_MIN);
        greater.push(INT32_MAX);
    }

    int getSize() {
        return less.size() + greater.size();
    }

    void pushValue(int val) {
        if (less.top() < val) {
            greater.push(val);
        } else {
            less.push(val);
        }

        while (less.size() < greater.size() - (getSize() % 2 == 0 ? 0 : 1)) {
            less.push(greater.top());
            greater.pop();
        }
        while (greater.size() - (getSize() % 2 == 0 ? 0 : 1) < less.size()) {
            greater.push(less.top());
            less.pop();
        }
    }

    int getMid() {
        return greater.top();
    }
};

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        MidSet set;
        std::vector<int> answer;
        for (int i = 0; i < n; ++i) {
            int val;
            scanf("%d", &val);
            set.pushValue(val);
            if (i % 2 == 0) {
                answer.push_back(set.getMid());
            }
        }

        printf("%d\n", (int)answer.size());
        for (int i = 0; i < answer.size(); ++i) {
            printf("%d ", answer[i]);
            if ((i+1) % 10 == 0) {
                printf("\n");
            }
        }
    }

    return 0;
}