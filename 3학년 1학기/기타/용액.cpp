#include <iostream>
#include <set>

std::multiset<int>::iterator findClosest(std::multiset<int>& sol, int target) {
    auto found = sol.lower_bound(target);
    if (found == sol.begin()) {
        return found;
    } else {
        auto prev = std::prev(found);
        if (found != sol.end() && std::abs(target-*found) < std::abs(target-*prev)) {
            return found;
        } else {
            return prev;
        }
    }
}

void updateAnswer(std::pair<int, int>& answer, int s1, int s2) {
    int da = std::abs(answer.first + answer.second);
    int ds = std::abs(s1 + s2);

    if (ds < da) {
        answer.first = std::min(s1, s2);
        answer.second = std::max(s1, s2);
    }
}

int main() {
    int n;
    scanf("%d", &n);

    int zero = 0;
    std::multiset<int> pos, neg;
    for (int i = 0; i < n; ++i) {
        int s;
        scanf("%d", &s);
        if (s == 0) {
            ++zero;
        } else if (s > 0) {
            pos.insert(s);
        } else {
            neg.insert(s);
        }
    }

    std::pair<int, int> answer = {1000000001, 1000000001};

    for (int p : pos) {
        if (!neg.empty()) {
            int n = *findClosest(neg, -p);
            updateAnswer(answer, p, n);
        }
        if (zero) {
            updateAnswer(answer, p, 0);
        }
    }
    if (pos.size() >= 2) {
        updateAnswer(answer, *pos.begin(), *std::next(pos.begin()));
    }

    for (int n : neg) {
        if (!pos.empty()) {
            int p = *findClosest(pos, -n);
            updateAnswer(answer, p, n);
        }
        if (zero) {
            updateAnswer(answer, n, 0);
        }
    }
    if (neg.size() >= 2) {
        updateAnswer(answer, *std::prev(neg.end()), *std::prev(std::prev(neg.end())));
    }

    printf("%d %d\n", answer.first, answer.second);

    return 0;
}