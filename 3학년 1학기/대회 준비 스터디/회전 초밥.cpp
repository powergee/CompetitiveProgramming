#include <iostream>
#include <algorithm>

class SushiSet {
private:
    int* count;
    int setSize = 0;

public:
    SushiSet(int d) {
        count = new int[d+1];
        std::fill(count, count+d+1, 0);
    }

    void addSushi(int num) {
        count[num]++;
        if (count[num] == 1) {
            setSize++;
        }
    }

    void removeSushi(int num) {
        count[num]--;
        if (count[num] == 0) {
            setSize--;
        }
    }

    int getSize() {
        return setSize;
    }
};

int sushi[30000];

int main() {
    int n, d, k, c;
    scanf("%d %d %d %d", &n, &d, &k, &c);

    for (int i = 0; i < n; ++i) {
        scanf("%d", sushi+i);
    }

    SushiSet set(d);
    for (int i = 0; i < k; ++i) {
        set.addSushi(sushi[i]);
    }

    int answer = 0;
    for (int i = 0; i < n; ++i) {
        set.addSushi(c);
        answer = std::max(answer, set.getSize());
        set.removeSushi(c);

        set.removeSushi(sushi[i]);
        set.addSushi(sushi[(i+k) % n]);
    }

    printf("%d", answer);

    return 0;
}