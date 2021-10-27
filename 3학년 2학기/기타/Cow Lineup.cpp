#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <algorithm>

struct Cow {
    int pos, breed;

    Cow(int pos, int breed) {
        this->pos = pos;
        this->breed = breed;
    }

    bool operator<(const Cow& c) const {
        return pos < c.pos;
    }
};

int main() {
    int n;
    scanf("%d", &n);

    std::set<int> totalBreeds;
    std::vector<Cow> cows;
    for (int i = 0; i < n; ++i) {
        int x, b;
        scanf("%d %d", &x, &b);
        cows.emplace_back(x, b);
        totalBreeds.insert(b);
    }
    std::sort(cows.begin(), cows.end());
    
    int right;
    std::map<int, int> count;
    for (right = 0; right < n && count.size() < totalBreeds.size(); ++right) {
        count[cows[right].breed]++;
    }

    int answer = cows[right-1].pos - cows[0].pos;
    for (int left = 0; left < n; ++left) {
        if (count.size() == totalBreeds.size()) {
            answer = std::min(answer, cows[right-1].pos - cows[left].pos);
        }
        
        --count[cows[left].breed];
        if (count[cows[left].breed] == 0) {
            count.erase(cows[left].breed);
        }

        while (right < n && count.size() < totalBreeds.size()) {
            ++count[cows[right++].breed];
        }
    }

    printf("%d", answer);

    return 0;
}