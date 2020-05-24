#include <iostream>
#define HEAP_MAX_SIZE 100001

typedef int HeapType;

HeapType heap[HEAP_MAX_SIZE];
int size = 0;

bool Compare(const HeapType& h1, const HeapType& h2)
{
    return h1 < h2;
}

bool IsEmpty()
{
    return size <= 0;
}

void MoveToTop(int index)
{
    if (index == 1)
        return;

    int parent = index / 2;
    if (Compare(heap[parent], heap[index]))
    {
        std::swap(heap[parent], heap[index]);
        MoveToTop(parent);
    }
}

void MoveToBottom(int index)
{
    int left = index * 2;
    int right = index * 2 + 1;
    int child = -1;

    if (left > size)
        return;
    else if (right > size)
        child = left;
    else
        child = Compare(heap[left], heap[right]) ? right : left;

    if (Compare(heap[index], heap[child]))
    {
        std::swap(heap[index], heap[child]);
        MoveToBottom(child);
    }
}

void Push(const HeapType& ele)
{
    heap[++size] = ele;
    MoveToTop(size);
}

HeapType Pop()
{
    if (size <= 0)
        return HeapType();

    HeapType result = heap[1];
    heap[1] = heap[size--];

    if (size > 0)
        MoveToBottom(1);

    return result;
}

int main()
{
    int n;
    scanf("%d", &n);

    while (n--)
    {
        int comm;
        scanf("%d", &comm);

        if (comm)
            Push(comm);

        else
        {
            if (IsEmpty())
                printf("0\n");
            else
                printf("%d\n", Pop());
        }
    }

    return 0;
}