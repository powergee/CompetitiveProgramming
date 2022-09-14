#include <iostream>
#include <string>
#include <map>
#include <cmath>

int main() {
    std::map<std::string, int> table {
        { "A+", 43 },
        { "A0", 40 },
        { "A-", 37 },
        { "B+", 33 },
        { "B0", 30 },
        { "B-", 27 },
        { "C+", 23 },
        { "C0", 20 },
        { "C-", 17 },
        { "D+", 13 },
        { "D0", 10 },
        { "D-", 7 },
        { "F", 0 },
    };
    int n;
    std::cin >> n;
    int totalPoints = 0;
    int totalGrades = 0;

    for (int i = 0; i < n; ++i) {
        std::string title;
        int points;
        std::string grade;
        std::cin >> title >> points >> grade;
        totalPoints += points;
        totalGrades += table[grade] * points;
    }

    int result = (totalGrades*100) / totalPoints;
    if ((result % 10) >= 5) {
        result += 10 - (result % 10);
    } else {
        result -= (result % 10);
    }

    printf("%d.%02d", result/1000, (result%1000)/10);

    return 0;
}