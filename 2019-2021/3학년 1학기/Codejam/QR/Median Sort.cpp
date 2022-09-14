#include <iostream>
#include <algorithm>
#include <vector>

int cache[51][51][51];

int query(int x, int y, int z) {
    if (cache[x][y][z]) {
        return cache[x][y][z];
    }

    printf("%d %d %d\n", x, y, z);
    fflush(stdout);
    int respond;
    scanf("%d", &respond);
    if (respond == -1) {
        exit(1);
    }
    return cache[x][y][z] = respond;
}

int findPosition(std::vector<int>& sol, int left, int right, int val) {
    if (right - left == 1) {
        int res = query(sol[left], sol[right], val);
        if (res == sol[left]) {
            return left;
        } else if (res == sol[right]) {
            return right+1;
        } else {
            return right;
        }
    } else {
        int med = (left+right) / 2;
        int res = query(sol[left], sol[med], val);

        if (res == sol[left]) {
            return left;
        } else if (res == sol[med]) {
            return findPosition(sol, med, right, val);
        } else {
            return findPosition(sol, left, med, val);
        }
    }
}

int main() {
    int T, N, Q;
    scanf("%d %d %d", &T, &N, &Q);

    for (int t = 1; t <= T; ++t) {
        std::fill(&cache[0][0][0], &cache[0][0][0] + sizeof(cache) / sizeof(int), 0);
        int med = query(1, 2, 3);
        std::vector<int> sol;
        for (int i = 1; i <= 3; ++i) {
            if (i != med) {
                sol.push_back(i);
            }
        }
        sol.insert(std::next(sol.begin()), med);
        
        for (int i = 4; i <= N; ++i) {
            int pos = findPosition(sol, 0, (int)sol.size()-1, i);
            sol.insert(sol.begin()+pos, i);
        }

        for (int v : sol) {
            printf("%d ", v);
        }
        printf("\n");
        fflush(stdout);

        int res;
        scanf("%d", &res);
        if (res != 1) {
            exit(1);
        }
    }
}