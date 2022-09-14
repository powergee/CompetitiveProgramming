#include <iostream>

std::pair<int, int> answer;

// depth는 1부터 시작
bool Find(int depth, int& index)
{
    if (index > depth)
    {
        index -= depth;
        return false;
    }

    if (depth % 2 == 1)
        answer = {depth - index + 1, index};
    else
        answer = {index, depth - index + 1};
        
    return true;
}

int main()
{
    int x;
    scanf("%d", &x);

    for (int depth = 1; !Find(depth, x); ++depth);
    printf("%d/%d", answer.first, answer.second);

    return 0;
}