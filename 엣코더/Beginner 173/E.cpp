#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#define MOD 1000000007

typedef long long Long;

std::set<Long, std::less<Long>> neg;
std::set<Long, std::greater<Long>> pos;
bool hasZero = false;

int main()
{
    int n, k;
    scanf("%d %d", &n, &k);

    for (int i = 0; i < n; ++i)
    {
        Long val;
        scanf("%lld", &val);

        if (val == 0)
            hasZero = true;
        else if (val < 0)
            neg.insert(val);
        else
            pos.insert(val);
    }

    if (k > (int)(neg.size() + pos.size()))
        printf("0");
    else
    {
        Long answer = 1;
        while (k > 0)
        {
            if (k > 1)
            {
                if ((int)pos.size() > 1 && (int)neg.size() > 1)
                {
                    Long posCase = (*pos.begin() * *(std::next(pos.begin()))) % MOD;
                    Long negCase = (*neg.begin() * *(std::next(neg.begin()))) % MOD;

                    if (posCase > negCase)
                    {
                        answer = (answer * posCase) % MOD;
                        pos.erase(pos.begin());
                        pos.erase(pos.begin());
                    }
                    else
                    {
                        answer = (answer * negCase) % MOD;
                        neg.erase(neg.begin());
                        neg.erase(neg.begin());
                    }
                    k -= 2;
                }
                else if ((int)pos.size() > 1)
                {
                    answer = (*pos.begin() * answer) % MOD;
                    pos.erase(pos.begin());
                    --k;
                }
                else if ((int)neg.size() > 1)
                {
                    Long negCase = (*neg.begin() * *(std::next(neg.begin()))) % MOD;
                    answer = (answer * negCase) % MOD;;
                    neg.erase(neg.begin());
                    neg.erase(neg.begin());
                    --k;
                }
                else
                {
                    answer = (*pos.begin() * answer) % MOD;
                    pos.erase(pos.begin());
                    --k;
                }
            }
            else
            {
                Long posCase = LLONG_MIN, negCase = LLONG_MIN, zeroCase = LLONG_MIN;

                if (!pos.empty())
                    posCase = (answer * *pos.begin()) % MOD;
                if (!neg.empty())
                    negCase = (answer * *std::prev(neg.end())) % MOD;
                if (hasZero)
                    zeroCase = 0;

                answer = std::max(posCase, std::max(negCase, zeroCase));
                --k;
            }
        }
        std::cout << answer;
    }

    return 0;
}