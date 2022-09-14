#include <iostream>
#include <string>
#include <stack>

int main()
{
    std::string exp;
    std::stack<char> st;
    std::cin >> exp;
    
    for (char ch : exp)
    {
        if (ch == '+' || ch == '-')
        {
            while (!st.empty() && st.top() != '(')
            {
                putchar(st.top());
                st.pop();
            }
            st.push(ch);
        }
        else if (ch == '*' || ch == '/')
        {
            while (!st.empty() && st.top() != '(' && (st.top() == '*' || st.top() == '/'))
            {
                putchar(st.top());
                st.pop();
            }
            st.push(ch);
        }
        else if (ch == '(')
        {
            st.push(ch);
        }
        else if (ch == ')')
        {
            while (st.top() != '(')
            {
                putchar(st.top());
                st.pop();
            }
            st.pop();
        }
        else putchar(ch);
    }

    while (!st.empty())
    {
        putchar(st.top());
        st.pop();
    }

    return 0;
}