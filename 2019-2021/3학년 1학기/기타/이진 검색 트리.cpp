#include <iostream>

struct Node {
    int value;
    Node* left;
    Node* right;

    Node() {
        value = 0;
        left = nullptr;
        right = nullptr;
    }
};

void addNode(Node* start, int val) {
    if (val < start->value) {
        if (start->left) {
            addNode(start->left, val);
        } else {
            Node* appending = new Node();
            appending->value = val;
            start->left = appending;
        }
    } else {
        if (start->right) {
            addNode(start->right, val);
        } else {
            Node* appending = new Node();
            appending->value = val;
            start->right = appending;
        }
    }
}

void postfix(Node* start) {
    if (start->left) {
        postfix(start->left);
    }

    if (start->right) {
        postfix(start->right);
    }

    std::cout << start->value << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    Node root;
    std::cin >> root.value;

    int val;
    while (std::cin >> val) {
        addNode(&root, val);
    }

    postfix(&root);
}