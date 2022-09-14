#include <iostream>
#include <algorithm>
#include <vector>

template<typename T>
struct Node
{
    int leftIndex, rightIndex;
    Node<T>* left, right;
    std::vector<T> subArray;
};

template<typename T>
Node<T> CreateNode(int left, int right)
{
    Node<T>* node = new Node<T>;
    node->leftIndex = left;
    node->rightIndex = right;
    node->subArray.resize(right - left + 1);
    return node;
}

template<typename T>
class MergeSortTree
{
private:
    Node<T>* top;

    Node<T>* MergeSort(std::vector<T>& arr, int left, int right)
    {
        if (left == right)
        {
            Node<T>* leaf = CreateNode<T>(left, right);
            leaf->subArray[0] = arr[left];
            return leaf;
        }

        int length = right - left + 1;
        int med = (left + right) / 2;
        Node<T>* leftNode = MergeSort(arr, left, med);
        Node<T>* rightNode = MergeSort(arr, med + 1, right);
        Node<T>* currNode = CreateNode<T>(left, right);

        currNode->left = leftNode;
        currNode->right = rightNode;

        int i = 0, j = 0, pos = 0;
        while (pos < length)
        {
            if (arr[i] < arr[j])
                currNode->subArray[pos++] = leftNode->subArray[i++];
            else
                currNode->subArray[pos++] = rightNode->subArray[j++];

            if (i >= (int)leftNode->size())
                while (j < (int)rightNode->size())
                    currNode->subArray[pos++] = rightNode->subArray[j++];

            else if (j >= (int)rightNode->size())
                while (i < (int)leftNode->size())
                    currNode->subArray[pos++] = leftNode->subArray[i++];
        }

        return currNode;
    }
public:
    MergeSortTree(std::vector<T>& arr)
    {
        top = MergeSort(arr, 0, (int)arr.size() - 1);
    }
};

int main()
{
    std::vector<int> arr = { 6, 3, 1, 8, 9, 2 };

    MergeSortTree<int> tree(arr);

    return 0;
}