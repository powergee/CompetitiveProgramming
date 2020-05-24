#include <iostream>
#include <stack>
#include <vector>

int main()
{
    int n;
    scanf("%d", &n);
    std::vector<int> nge(n + 1, -1);
    std::stack<std::pair<int, int>> st;

    for (int i = 1; i <= n; ++i)
    {
        int val;
        scanf("%d", &val);
        while (!st.empty() && st.top().first < val)
        {
            auto now = st.top();
            st.pop();
            nge[now.second] = val;
        }
        st.push({val, i});
    }

    for (int i = 1; i <= n; ++i)
        printf("%d ", nge[i]);

    return 0;
}