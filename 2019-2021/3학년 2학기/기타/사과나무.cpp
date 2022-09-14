#include <iostream>
#include <vector>
#include <string>
#define PARENT_EXP 12

struct Node {
    std::pair<int, int> index;
    std::vector<Node*> next;
    Node* parent[PARENT_EXP];
    int depth;

    Node(Node* root, int depth) {
        std::fill(parent, parent+PARENT_EXP, root);
        this->depth = depth;
        index = { 0, 0 };
    }
    Node() : Node(this, 0) { }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, x, y;
    Node* xNode, *yNode;
    std::string rep;

    std::cin >> n;
    std::cin >> rep;
    std::cin >> x >> y;

    Node* root = new Node;
    Node* curr = root;
    std::vector<Node*> nodes = { root };
    int depth = 0;

    if (x == 1) {
        xNode = root;
    }
    if (y == 1) {
        yNode = root;
    }

    for (int i = 1; i < rep.size(); ++i) {
        Node* captured;
        if (rep[i] == '0') {
            Node* next = new Node(root, ++depth);
            captured = next;
            next->index.first = i;
            next->parent[0] = curr;
            curr->next.push_back(next);
            curr = next;
            nodes.push_back(next);
        } else {
            captured = curr;
            curr->index.second = i;
            curr = curr->parent[0];
            --depth;
        }

        if (i == x-1) {
            xNode = captured;
        }
        if (i == y-1) {
            yNode = captured;
        }
    }

    for (int e = 1; e < PARENT_EXP; ++e) {
        for (Node* node : nodes) {
            node->parent[e] = node->parent[e-1]->parent[e-1];
        }
    }

    for (int e = PARENT_EXP-1; e >= 0; --e) {
        while (xNode->depth-yNode->depth >= (1<<e)) {
            xNode = xNode->parent[e];
        }
        while (yNode->depth-xNode->depth >= (1<<e)) {
            yNode = yNode->parent[e];
        }
    }

    if (xNode != yNode) {
        for (int e = PARENT_EXP-1; e >= 0; --e) {
            if (xNode->parent[e] != yNode->parent[e]) {
                xNode = xNode->parent[e];
                yNode = yNode->parent[e];
            }
        }
        xNode = xNode->parent[0];
        yNode = yNode->parent[0];
    }

    std::cout << xNode->index.first+1 << " " << xNode->index.second+1;
    return 0;
}