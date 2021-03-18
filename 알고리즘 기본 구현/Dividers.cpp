#include <algorithm>
#include <map>
#include <set>
#include <vector>

typedef long long Long;

Long intPow(Long x, int e) {
    Long result = 1;
    for (int i = 0; i < e; ++i) {
        result *= x;
    }
    return result;
}

void fillDividers(int start, Long before,
    std::vector<Long>& primes,
    std::map<Long, int>& count,
    std::set<Long>& dividers) {

    if ((int)count.size() <= start) {
        dividers.insert(before);
        return;
    }

    Long p = primes[start];
    for (int i = 0; i <= count[p]; ++i) {
        fillDividers(start + 1, before * intPow(p, i), primes, count, dividers);
    }
}

std::set<Long> getDividers(Long x) {
    std::set<Long> dividers;
    std::vector<Long> primes;
    std::map<Long, int> count;

    Long xCopy = x;
    Long div = 2;
    std::set<Long> primeSet;
    while (xCopy > 1 && div*div <= xCopy) {
        if (xCopy % div == 0) {
            xCopy /= div;
            count[div]++;
            primeSet.insert(div);
        } else {
            div++;
        }
    }
    
    if (xCopy > 1) {
        count[xCopy]++;
        primeSet.insert(xCopy);
    }
    
    for (Long p : primeSet) {
        primes.push_back(p);
    }
    
    fillDividers(0, 1, primes, count, dividers);
    return dividers;
}