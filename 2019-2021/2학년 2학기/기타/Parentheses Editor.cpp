#include <iostream>
#include <vector>

typedef long long Long;

enum OperType { Pushed, MadeBackZeror, Popped, IncBack, IncAnswer };

struct Operation
{
    int time;
    OperType type;
    int arg;

    Operation(int time, OperType type, int arg)
    {
        this->time = time;
        this->type = type;
        this->arg = arg;
    }
};

int main()
{
    std::string input;
    std::cin >> input;
    std::vector<Long> st;
    std::vector<Operation> history;
    Long answer = 0;
    int time = 0;
    st.push_back(0);

    for (char ch : input)
    {
        switch (ch)
        {
        case '(':
            history.emplace_back(time, Pushed, 0);
            st.push_back(0);
            break;
        
        case ')':
            if (st.size() == 1)
            {
                history.emplace_back(time, MadeBackZeror, st.back());
                st.back() = 0;
            }
            else
            {
                Long poppedVal = st.back();
                history.emplace_back(time, Popped, poppedVal);
                st.pop_back();
                history.emplace_back(time, IncBack, 1);
                st.back() += 1;
                history.emplace_back(time, IncAnswer, st.back());
                answer += st.back();
            }
            break;

        case '-':
            int prevTime = history.back().time;
            while (!history.empty() && prevTime == history.back().time)
            {
                Operation op = history.back();
                history.pop_back();

                switch (op.type)
                {
                case Pushed:
                    st.pop_back();
                    break;
                
                case MadeBackZeror:
                    st.back() = op.arg;
                    break;
                
                case Popped:
                    st.push_back(op.arg);
                    break;
                
                case IncBack:
                    st.back() -= op.arg;
                    break;
                
                case IncAnswer:
                    answer -= op.arg;
                    break;
                }
            }
            break;
        }

        std::cout << answer << "\n";
        ++time;
    }

    return 0;
}