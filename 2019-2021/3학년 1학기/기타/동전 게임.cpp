#include <iostream>
#include <string>
#include <queue>
#include <vector>

struct State {
    bool kind[3][3];
    int step = 0;

    bool isSame() {
        bool pivot = kind[0][0];
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (pivot != kind[i][j]) {
                    return false;
                }
            }
        }

        return true;
    }

    int getIndex() {
        int result = 0;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                result = (result << 1) | (kind[i][j] ? 1 : 0);
            }
        }

        return result;
    }

    void flipRow(int r) {
        for (int c = 0; c < 3; ++c) {
            kind[r][c] = !kind[r][c];
        }
    }

    void flipCol(int c) {
        for (int r = 0; r < 3; ++r) {
            kind[r][c] = !kind[r][c];
        }
    }

    void flipDiag1() {
        for (int i = 0; i < 3; ++i) {
            kind[i][i] = !kind[i][i];
        }
    }

    void flipDiag2() {
        for (int i = 0; i < 3; ++i) {
            kind[2-i][i] = !kind[2-i][i];
        }
    }

    State* clone() {
        State* s = new State;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                s->kind[i][j] = kind[i][j];
            }
        }

        return s;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;
    while (T--) {
        State* s = new State;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                std::string digit;
                std::cin >> digit;
                s->kind[i][j] = (digit == "H");
            }
        }

        std::queue<State*> q;
        std::vector<bool> visited(512, false);
        q.push(s);

        int answer = -1;

        while (!q.empty()) {
            auto now = q.front();
            q.pop();

            if (visited[now->getIndex()]) {
                continue;
            }
            visited[now->getIndex()] = true;

            if (now->isSame()) {
                answer = now->step;
                break;
            }

            for (int r = 0; r < 3; ++r) {
                State* next = now->clone();
                next->flipRow(r);
                next->step = now->step+1;
                if (!visited[next->getIndex()]) {
                    q.push(next);
                } else {
                    delete next;
                }
            }
            for (int c = 0; c < 3; ++c) {
                State* next = now->clone();
                next->flipCol(c);
                next->step = now->step+1;
                if (!visited[next->getIndex()]) {
                    q.push(next);
                } else {
                    delete next;
                }
            }

            State* next = now->clone();
            next->flipDiag1();
            next->step = now->step+1;
            if (!visited[next->getIndex()]) {
                q.push(next);
            } else {
                delete next;
            }

            next = now->clone();
            next->flipDiag2();
            next->step = now->step+1;
            if (!visited[next->getIndex()]) {
                q.push(next);
            } else {
                delete next;
            }

            delete now;
        }

        while (!q.empty()) {
            auto now = q.front();
            q.pop();
            delete now;
        }

        printf("%d\n", answer);
    }

    return 0;
}