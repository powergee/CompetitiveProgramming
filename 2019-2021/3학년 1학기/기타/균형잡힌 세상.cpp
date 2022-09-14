#include <iostream>
#include <string>
#include <stack>

int main() {
    std::string line;

    while (true) {
        std::getline(std::cin, line);
        if ((int)line.size() == 1 && line[0] == '.') {
            break;
        }
        std::stack<char> par;
        bool yes = true;
        for (char ch : line) {
            if (ch == '(' || ch == '[') {
                par.push(ch);
            } else if (ch == ')') {
                if (par.empty() || par.top() != '(') {
                    yes = false;
                    break;
                } else {
                    par.pop();
                }
            } else if (ch == ']') {
                if (par.empty() || par.top() != '[') {
                    yes = false;
                    break;
                } else {
                    par.pop();
                }
            }
        }

        if (!par.empty()) {
            yes = false;
        }

        if (yes) {
            printf("yes\n");
        } else {
            printf("no\n");
        }
    }

    return 0;
}