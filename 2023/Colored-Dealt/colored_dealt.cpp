#include <cstdlib>
#include <string>

#include "colored_dealt.h"

std::string guess(int N) {
    std::string litmus = std::string(N, 'R');
    int total = design(litmus);
    std::string answer = "";
    answer.reserve(N);

    for (int i = 0; i < N - 1; ++i) {
        litmus[i] = 'B';
        int next = design(litmus) - 3 * (i + 1);
        int diff = total - next;
        switch (diff) {
            case 1:
                answer += 'R';
                break;
            case 2:
                answer += 'G';
                break;
            case 3:
                answer += 'B';
                break;
            default:
                exit(-1);
        }
        total = next;
    }
    switch (total) {
        case 1:
            answer += 'R';
            break;
        case 2:
            answer += 'G';
            break;
        case 3:
            answer += 'B';
            break;
        default:
            exit(-1);
    }
    return answer;
}
