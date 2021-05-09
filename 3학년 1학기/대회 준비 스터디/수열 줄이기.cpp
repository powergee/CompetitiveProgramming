#include <iostream>
#include <vector>

int main() {
    int n;
    long long answer = 0;
    scanf("%d", &n);
    std::vector<int> st;

    for (int i = 0; i < n; ++i) {
        int val;
        scanf("%d", &val);

        if (st.empty()) {
            st.push_back(val);
            continue;
        }

        bool mustPush = true;
        while (!st.empty() && st.back() <= val) {
            if (st.size() > 1) {
                if (st[st.size()-2] < val) {
                    answer += st[st.size()-2];
                    st.pop_back();
                } else {
                    answer += val;
                    st.back() = val;
                    mustPush = false;
                    break;
                }
            } else {
                answer += val;
                st.back() = val;
                mustPush = false;
                break;
            }
        }

        if (mustPush) {
            st.push_back(val);
        }
    }

    for (int i = 0; i < (int)st.size()-1; ++i) {
        answer += st[i];
    }
    printf("%lld", answer);
}