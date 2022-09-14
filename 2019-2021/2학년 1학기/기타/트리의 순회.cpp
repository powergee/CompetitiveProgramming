#include <iostream>
#include <vector>

std::pair<int, int> graph[100001];

int BuildTree(int* in, int* post, int length)
{
    if (length == 1)
        return in[0];

    for (int* i = in; i != in + length; ++i)
    {
        if (*i != *(post + length - 1))
            continue;
        
        int lenA = i - in;
        int lenB = length - lenA - 1;
        int* inA = in;
        int* inB = i + 1;
        int* postA = post;
        int* postB = post + lenA;
        
        int aNum = (lenA == 0 ? 0 : BuildTree(inA, postA, lenA));
        int bNum = (lenB == 0 ? 0 : BuildTree(inB, postB, lenB));
        graph[*i].first = aNum;
        graph[*i].second = bNum;
        
        return *i;
    }

    return -1;
}

void PrintPre(int start)
{
    if (start == 0)
        return;

    printf("%d ", start);
    PrintPre(graph[start].first);
    PrintPre(graph[start].second);
}

int main()
{
    int n;
    scanf("%d", &n);

    int* inOrder = new int[n];
    int* postOrder = new int[n];

    for (int i = 0; i < n; ++i)
        scanf("%d", inOrder + i);

    for (int i = 0; i < n; ++i)
        scanf("%d", postOrder + i);

    int root = BuildTree(inOrder, postOrder, n);
    PrintPre(root);

    delete[] inOrder;
    delete[] postOrder;

    return 0;
}