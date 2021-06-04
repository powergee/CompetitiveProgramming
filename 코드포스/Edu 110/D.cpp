#include <iostream>
#include <vector>
#include <queue>

struct Node {
    char label;
    int num;
    int count;
    Node* parent;
    Node* left;
    Node* right;
    std::pair<int, int> range;

    void updateCount() {
        switch (label)
        {
        case '?':
            count = left == nullptr ? 2 : left->count + right->count;
            break;

        case '1':
            count = right == nullptr ? 1 : right->count;
            break;

        case '0':
            count = left == nullptr ? 1 : left->count;
            break;
        }

        if (parent) {
            parent->updateCount();
        }
    }

    Node(char l, int n) {
        label = l;
        num = n;
        parent = nullptr;
        left = nullptr;
        right = nullptr;
        range = {n, n};
        updateCount();
    }

    Node(char l, int n, Node* left, Node* right) {
        label = l;
        num = n;
        parent = nullptr;
        this->left = left;
        this->right = right;
        range = {left->range.first, right->range.second};
        updateCount();
    }
};

char init[2<<19];
Node* nodeTable[2<<19];

int main() {
    int k;
    scanf("%d", &k);
    scanf("%s", init);
    int initIdx = 0;
    int nodeNum = 1;

    std::vector<Node*> nodes;
    for (int i = 0; i < 1<<(k-1); ++i) {
        Node* node = new Node(init[initIdx++], nodeNum);
        nodeTable[nodeNum++] = node;
        nodes.push_back(node);
    }

    while (nodes.size() > 1) {
        std::vector<Node*> upper;
        for (int i = 0; i < nodes.size(); i += 2) {
            Node* parent = new Node(init[initIdx++], nodeNum, nodes[i], nodes[i+1]);
            nodeTable[nodeNum++] = parent;
            nodes[i]->parent = nodes[i+1]->parent = parent;
            upper.push_back(parent);
        }
        nodes = upper;
    }

    Node* root = nodes.front();

    int q;
    scanf("%d", &q);

    while (q--) {
        int num;
        char labelStr[2];
        scanf("%d %s", &num, labelStr);
        char label = labelStr[0];

        nodeTable[num]->label = label;
        nodeTable[num]->updateCount();
        printf("%d\n", root->count);
    }

    return 0;
}