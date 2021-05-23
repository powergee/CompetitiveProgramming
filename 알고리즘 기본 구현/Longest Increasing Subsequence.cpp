#include <algorithm>
#include <vector>
#include <stack>

// 결과 LIS가 필요 없다면 result에 null.
int getLIS(std::vector<int>& arr, std::vector<int>* result) {
    std::vector<int> lis(arr.size(), __INT32_MAX__);
    std::vector<int> pos(arr.size());

    int length = 0;
    for (int i = 0; i < arr.size(); ++i) {
        auto found = std::lower_bound(lis.begin(), lis.end(), arr[i]);
        *found = arr[i];
        pos[i] = found - lis.begin();
        length = std::max(length, pos[i]+1);
    }

    if (result) {
        std::stack<int> s;
        int target = length-1;
        for (int i = arr.size()-1; i >= 0; --i) {
            if (target == pos[i]) {
                --target;
                s.push(arr[i]);
            }
        }

        while (!s.empty()) {
            result->push_back(s.top());
            s.pop();
        }
    }

    return length;
}