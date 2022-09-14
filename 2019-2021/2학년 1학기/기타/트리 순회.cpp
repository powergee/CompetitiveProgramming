#include <iostream>
#include <algorithm>

struct Node
{
    char name;
    int left = -1;
    int right = -1;
};

int n;
Node nodes[26];

void Preorder(int start)
{
    printf("%c", nodes[start].name);
    if (nodes[start].left != -1)
        Preorder(nodes[start].left);
    if (nodes[start].right != -1)
        Preorder(nodes[start].right);
}

void Inorder(int start)
{
    if (nodes[start].left != -1)
        Inorder(nodes[start].left);
    printf("%c", nodes[start].name);
    if (nodes[start].right != -1)
        Inorder(nodes[start].right);
}

void Postorder(int start)
{
    if (nodes[start].left != -1)
        Postorder(nodes[start].left);
    if (nodes[start].right != -1)
        Postorder(nodes[start].right);
    printf("%c", nodes[start].name);
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        char input[3][2];
        scanf("%s %s %s", input[0], input[1], input[2]);
        Node& parent = nodes[input[0][0] - 'A'];
        parent.name = input[0][0];
        if (input[1][0] != '.')
            parent.left = input[1][0] - 'A';
        if (input[2][0] != '.')
            parent.right = input[2][0] - 'A';
    }

    Preorder(0);
    printf("\n");
    Inorder(0);
    printf("\n");
    Postorder(0);

    return 0;
}