#include <iostream>
#include <algorithm>
#include <set>

struct Domino {
    char name;
    bool isHorizontal;

    Domino(char pname, bool pisHor) {
        name = pname;
        isHorizontal = pisHor;
    }
};

int r, c, k;
Domino* map[100][100];

void checkCell(std::set<char>& currUsing, int i, int j) {
    if (0 <= i && i < r && 0 <= j && j < c) {
        currUsing.insert(map[i][j]->name);
    }
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        scanf("%d %d %d", &r, &c, &k);
        
        if (r % 2 == 0) {
            int capacity = (c/2) * r;
            if (k % 2 == 1 || capacity < k) {
                printf("NO\n");
                continue;
            }

            for (int i = 0; i < r; i += 2) {
                for (int j = 0; j < c; ++j) {
                    Domino* dom = new Domino('\0', false);
                    map[i][j] = map[i+1][j] = dom;
                }
            }
            for (int i = 0; i < r && i+1 < r && k > 0; i += 2) {
                for (int j = 0; j < c && j+1 < c && k > 0; j += 2) {
                    Domino* upper = new Domino('\0', true);
                    Domino* lower = new Domino('\0', true);
                    delete map[i][j];
                    delete map[i][j+1];
                    map[i][j] = map[i][j+1] = upper;
                    map[i+1][j] = map[i+1][j+1] = lower;
                    k -= 2;
                }
            }
        } else {
            k = (r*c/2) - k;
            int capacity = (r/2) * c;
            if (k % 2 == 1 || capacity < k) {
                printf("NO\n");
                continue;
            }
            
            for (int i = 0; i < r; ++i) {
                for (int j = 0; j < c; j += 2) {
                    Domino* dom = new Domino('\0', true);
                    map[i][j] = map[i][j+1] = dom;
                }
            }
            for (int i = 0; i < r && i+1 < r && k > 0; i += 2) {
                for (int j = 0; j < c && j+1 < c && k > 0; j += 2) {
                    Domino* left = new Domino('\0', false);
                    Domino* right = new Domino('\0', false);
                    delete map[i][j];
                    delete map[i+1][j];
                    map[i][j] = map[i+1][j] = left;
                    map[i][j+1] = map[i+1][j+1] = right;
                    k -= 2;
                }
            }
        }

        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                if (map[i][j]->name == '\0') {
                    std::set<char> currUsing;
                    if (map[i][j]->isHorizontal) {
                        checkCell(currUsing, i-1, j);
                        checkCell(currUsing, i-1, j+1);
                        checkCell(currUsing, i, j-1);
                        checkCell(currUsing, i, j+2);
                        checkCell(currUsing, i+1, j);
                        checkCell(currUsing, i+1, j+1);
                    } else {
                        checkCell(currUsing, i-1, j);
                        checkCell(currUsing, i, j-1);
                        checkCell(currUsing, i, j+1);
                        checkCell(currUsing, i+1, j-1);
                        checkCell(currUsing, i+1, j+1);
                        checkCell(currUsing, i+2, j);
                    }
                    for (char ch = 'a'; ch <= 'z'; ++ch) {
                        if (currUsing.find(ch) == currUsing.end()) {
                            map[i][j]->name = ch;
                            break;
                        }
                    }
                }
            }
        }

        printf("YES\n");
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                putchar(map[i][j]->name);
            }
            putchar('\n');
        }
    }

    return 0;
}