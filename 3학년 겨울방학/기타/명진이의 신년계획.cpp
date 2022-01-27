#include <iostream>
#include <algorithm>
#include <vector>
#define Undefined -1
#define UnableToMake -2

struct Disease {
    int red, blue, danger;
};

struct Student {
    int num, red, blue;
};

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    std::vector<Disease> diseases(m);
    std::vector<std::vector<std::vector<int>>> dp(m, std::vector<std::vector<int>>(51, std::vector<int>(51, Undefined)));

    for (int i = 0; i < m; ++i) {
        scanf("%d %d %d", &diseases[i].red, &diseases[i].blue, &diseases[i].danger);
    }

    std::function<int(int, int, int)> getDanger = [&](int dIdx, int red, int blue) -> int {
        if (dIdx == m) {
            return UnableToMake;
        }
        int& result = dp[dIdx][red][blue];
        if (result != Undefined) {
            return result;
        }

        result = UnableToMake;
        for (int i = dIdx; i < m; ++i) {
            auto dis = diseases[i];
            if (dis.red == red && dis.blue == blue) {
                result = std::max(result, dis.danger);
            } else if (dis.red <= red && dis.blue <= blue) {
                int sub = getDanger(i+1, red-dis.red, blue-dis.blue);
                if (sub != UnableToMake) {
                    result = std::max(result, sub+dis.danger);
                }
            }
        }
        return result;
    };

    std::vector<Student> students(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &students[i].red, &students[i].blue);
        students[i].num = i+1;
    }

    std::sort(students.begin(), students.end(), [&](const Student& s1, const Student& s2) -> bool {
        int d1 = getDanger(0, s1.red, s1.blue);
        int d2 = getDanger(0, s2.red, s2.blue);

        if (d1 == UnableToMake) {
            d1 = 0;
        }
        if (d2 == UnableToMake) {
            d2 = 0;
        }

        if (d1 != d2) {
            return d1 < d2;
        }
        return s1.num < s2.num;
    });

    for (Student s : students) {
        int danger = getDanger(0, s.red, s.blue);
        printf("%d %d\n", s.num, danger == UnableToMake ? 0 : danger);
    }

    return 0;
}