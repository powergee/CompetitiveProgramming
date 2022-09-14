#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::string str;
    std::cin >> str;
    str = " " + str;
    
    std::vector<int> points(str.size(), 0);
    std::vector<int> interest(str.size(), 1);

    for (int i = 0; i < str.size(); ++i) {
        if (str[i] == 'S') {
            points[i] = 2;
        } else if (str[i] == 'K') {
            points[i] = -1;
        } else {
            interest[i] = 0;
        }
    }

    std::vector<int> pointSum(str.size()), interestSum(str.size());
    std::partial_sum(points.begin(), points.end(), pointSum.begin());
    std::partial_sum(interest.begin(), interest.end(), interestSum.begin());
    std::map<int, int> valPos;

    int answer = -1;
    for (int i = 0; i < str.size(); ++i) {
        if (valPos.count(pointSum[i]) && interestSum[i] - interestSum[valPos[pointSum[i]]] > 0) {
            answer = std::max(answer, i - valPos[pointSum[i]]);
        }
        if (valPos.count(pointSum[i]) == 0) {
            valPos[pointSum[i]] = i;
        }
    }

    printf("%d", answer);

    return 0;
}