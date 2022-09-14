#include <iostream>
#include <string>

template <typename T>
class Stack
{
private:
    int size = 0;
    T arr[10000];

public:
    void Push(int x)
    {
        arr[size++] = x;
    }

    T Pop()
    {
        if (size == 0)
            return -1;
        return arr[--size];
    }

    int GetSize()
    {
        return size;
    }

    bool IsEmpty()
    {
        return size == 0;
    }

    int GetTop()
    {
        if (size == 0)
            return -1;
        return arr[size - 1];
    }
};

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    Stack<int> s;
    std::cin >> n;

    while (n--)
    {
        std::string comm;
        std::cin >> comm;

        if (comm == "push")
        {
            int num;
            std::cin >> num;
            s.Push(num);
        }
        else if (comm == "pop")
        {
            std::cout << s.Pop() << '\n';
        }
        else if (comm == "size")
        {
            std::cout << s.GetSize() << '\n';
        }
        else if (comm == "empty")
        {
            std::cout << (s.IsEmpty() ? 1 : 0) << '\n';
        }
        else if (comm == "top")
        {
            std::cout << s.GetTop() << '\n';
        }
    }

    return 0;
}