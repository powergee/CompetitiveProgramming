#include <iostream>

template <typename T>
struct Node
{
    T Value;
    Node<T>* Front, Back;
};

template <typename T>
class Deque
{
private:
    Node<T>* front = nullptr, back = nullptr;
    int size = 0;

public:
    void PushFront(T val)
    {
        Node<T>* node = new Node<T>;
        if (front == nullptr)
        {
            front = node;
            back = node;
        }
        else
        {
            node->Value = val;
            node->Back = front;
            node->Front = nullptr;
            front->Front = node;
            front = node;
        }

        ++size;
    }

    void PushBack(T val)
    {
        Node<T>* node = new Node<T>;
        if (back == nullptr)
        {
            front = node;
            back = node;
        }
        else
        {
            node->Value = val;
            node->Front = back;
            node->Back = nullptr;
            back->Back = node;
            back = node;
        }

        ++size;
    }

    T PopFront()
    {
        if (front == nullptr)
            return -1;

        T val = front->Value;
        if (front->Back == nullptr)
        {
            
        }

        Node<T>* toPop = front;
        front = toPop->Back;
        front->Front = nullptr;
        delete toPop;
        --size;

        return val;
    }

    T PopBack()
    {
        if (back == nullptr)
            return -1;
        
        T val = back->Value;
        Node<T>* toPop = back;
        back = toPop->Front;
        back->Back = nullptr;
        delete toPop;
        --size;

        return val;
    }
};

int main()
{


    return 0;
}