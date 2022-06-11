#include <iostream>
#include <vector>
#include <set>

int choice[200000];
int answer[200000];

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        int fulfilled = 0;
        std::set<int, std::greater<int>> available;

        for (int i = 0; i < n; ++i) {
            scanf("%d", choice+i);
            answer[i] = 0;
            available.insert(i+1);
        }

        for (int i = 0; i < n; ++i) {
            if (available.find(choice[i]) != available.end()) {
                fulfilled++;
                answer[i] = choice[i];
                available.erase(available.find(choice[i]));
            }
        }

        for (int i = 0; i < n; ++i) {
            if (answer[i] == 0) {
                auto found = available.find(i+1);
                if (found != available.end()) {
                    answer[i] = i+1;
                    available.erase(found);
                }
            }
        }

        for (int i = 0; i < n; ++i) {
            if (answer[i] == 0) {
                answer[i] = *available.begin();
                available.erase(available.begin());
            }
        }

        std::vector<int> same;
        for (int i = 0; i < n; ++i) {
            if (i+1 == answer[i]) {
                same.push_back(i);
            }
        }

        if ((int)same.size() == 1) {
            for (int i = 0; i < n; ++i) {
                if (i != same.front() && choice[i] == choice[same.front()] && answer[i] != same.front()+1) {
                    std::swap(answer[i], answer[same.front()]);
                    break;
                }
            }
        } else if ((int)same.size() > 1) {
            for (int i = 0; i < (int)same.size()-1; ++i) {
                std::swap(answer[same[i]], answer[same[i+1]]);
            }
        }

        printf("%d\n", fulfilled);
        for (int i = 0; i < n; ++i) {
            printf("%d ", answer[i]);
        }
        printf("\n");
    }

    return 0;
}