#include <iostream>
#include <vector>

typedef long long Long;

struct Expression {
    Long constant, coeff;

    Expression operator-(const Expression& exp) const {
        return { constant - exp.constant, coeff - exp.coeff };
    }
};

int main() {
    int n;
    scanf("%d", &n);

    std::vector<Long> sum(n);
    for (int i = 1; i <= n-1; ++i) {
        scanf("%lld", &sum[i]);
    }

    if (n == 2) {
        printf("%lld\n", sum[1]-1);
        return 0;
    }

    std::vector<Expression> exp(n+1);
    Long posMin = INT64_MAX, negMin= INT64_MAX;
    exp[1] = { 0, 1 };
    for (int i = 2; i <= n; ++i) {
        Expression rhs = { sum[i-1], 0 };
        exp[i] = rhs - exp[i-1];

        if (exp[i].coeff > 0) {
            posMin = std::min(posMin, exp[i].constant);
        } else {
            negMin = std::min(negMin, exp[i].constant);
        }
    }

    Long left = std::max(1-posMin, 1LL);
    Long right = negMin-1;
    
    printf("%lld\n", std::max(0LL, right-left+1));

    return 0;
}