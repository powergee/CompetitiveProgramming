#include <iostream>
#include <string>
#include <functional>

typedef long long Long;

const std::vector<int> PRIMES { 2, 3, 5, 7 };

Long countCases(Long bound) {
	if (bound == 0) {
		return 0;
	}
	std::vector<Long> dp(13*109*109*2*2, -1);
	std::string boundStr = std::to_string(bound);
	int boundLength = boundStr.size();

	std::function<Long(int, int, int, int, int)> countCases = [&](int pos, int sum, int remainingMult, int alreadySmall, int started) -> Long {
		if (pos == boundLength) {
			if (sum == 0 && remainingMult == 1) {
				return 1;
			} else {
				return 0;
			}
		}

		int sign = 109*109*2*2*pos + 109*2*2*sum + 2*2*remainingMult + 2*alreadySmall + started;
		Long& result = dp[sign];
		if (result != -1) {
			return result;
		}

		int currMax = std::min((alreadySmall ? 9 : (boundStr[pos]-'0')), sum);
		result = 0;
		for (int d = 0; d <= currMax; ++d) {
			int newMult, newSmall, newStarted;
			
			if (d == 0) {
				if (started) {
					newMult = 1;
				} else {
					newMult = remainingMult;
				}
			} else {
				int dCopy = d;
				newMult = remainingMult;
				for (int p : PRIMES) {
					while (newMult % p == 0 && dCopy % p == 0) {
						newMult /= p;
						dCopy /= p;
					}
				}
			}

			if (alreadySmall || d < (boundStr[pos]-'0')) {
				newSmall = 1;
			} else {
				newSmall = 0;
			}

			if (started || d >= 1) {
				newStarted = 1;
			} else {
				newStarted = 0;
			}

			result += countCases(pos+1, sum-d, newMult, newSmall, newStarted);
		}

		return result;
	};
	
	Long result = 0;
	for (int sum = 1; sum <= 108; ++sum) {
		result += countCases(0, sum, sum, 0, 0);
	}
	return result;
}

int main() {
    int T;
    scanf("%d", &T);

    for (int t = 1; t <= T; ++t) {
        Long a, b;
        scanf("%lld %lld", &a, &b);
        printf("Case #%d: %lld\n", t, countCases(b) - countCases(a-1));
    }

    return 0;
}