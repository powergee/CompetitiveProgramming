#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <cmath>

void PopTwo(std::stack<double>& st, double& a, double& b)
{
    a = st.top();
    st.pop();
    b = st.top();
    st.pop();
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::string exp;
    std::map<char, double> var;
    std::cin >> n >> exp;

    for (int i = 0; i < n; ++i)
    {
        double val;
        std::cin >> val;
        var['A'+i] = val;
    }
    
    std::stack<double> calcStack;
    for (char ch : exp)
    {
        double a, b;
        switch (ch)
        {
        case '+':
            PopTwo(calcStack, a, b);
            calcStack.push(a+b);
            break;
        case '-':
            PopTwo(calcStack, a, b);
            calcStack.push(b-a);
            break;
        case '*':
            PopTwo(calcStack, a, b);
            calcStack.push(b*a);
            break;
        case '/':
            PopTwo(calcStack, a, b);
            calcStack.push(b/a);
            break;
        default:
            calcStack.push(var[ch]);
        }
    }

    printf("%.2lf", std::floor(calcStack.top() * 100) / 100);

    return 0;
}