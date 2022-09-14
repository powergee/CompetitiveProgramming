#include <iostream>
#include <vector>
#include <numeric>

typedef long long Long;

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    std::vector<Long> arr(n);
    Long sum = 0;
    for (int i = 0; i < n; ++i) {
        Long v;
        scanf("%lld", &v);
        arr[i] = v % k;
        sum += arr[i];
    }

    if (sum % k != 0) {
        printf("blobsad");
        return 0;
    }

    auto getMinCount = [](const std::vector<Long>& window) -> Long {
        std::vector<Long> sum;
        std::partial_sum(window.begin(), window.end(), std::back_inserter(sum));

        Long currCount = 0;
        for (int i = 1; i < window.size(); ++i) {
            currCount += window[i] * i;
        }

        Long result = currCount;
        for (int i = 1; i < window.size(); ++i) {
            currCount -= sum.back() - sum[i-1];
            currCount += sum[i-1];
            result = std::min(result, currCount);
        }
        return result;
    };

    std::vector<Long> window;
    Long inWindow = 0, answer = 0;
    for (int i = 0; i < n; i += (arr[i] ? 0 : 1)) {
        if (k-inWindow <= arr[i]) {
            window.push_back(k-inWindow);
            inWindow += window.back();
            arr[i] -= window.back();

            answer += getMinCount(window);
            window.clear();
            inWindow = 0;
        } else {
            window.push_back(arr[i]);
            inWindow += window.back();
            arr[i] -= window.back();
        }
    }

    if (window.size()) {
        answer += getMinCount(window);
    }
    printf("%lld", answer);

    return 0;
}