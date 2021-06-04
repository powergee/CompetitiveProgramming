#include <iostream>
#include <vector>
#include <queue>
#include <string>

typedef struct Node {
    int num;
    int depth;
    Node* parent;
    struct std::vector<Node*> next;
    bool visited;
} Node;

Node* insertValue(Node* node, int value) {
    if (node->visited) {
        return nullptr;
    }

    for (auto nextNode : node->next) {
        Node* result = insertValue(nextNode, value);
        if (result) {
            return result;
        }
    }

    if (node->next.empty() && value == 1) {
        Node* append = new Node;
        append->depth = node->depth+1;
        append->num = value;
        append->parent = node;
        append->visited = false;
        node->next.push_back(append);
        return append;
    }

    if (!node->next.empty() && node->next.back()->num == value-1) {
        Node* append = new Node;
        append->depth = node->depth+1;
        append->num = value;
        append->parent = node;
        append->visited = false;
        node->next.push_back(append);
        return append;
    }

    node->visited = true;
    return nullptr;
}

void printTree(Node* node, std::vector<int>& path) {
    path.push_back(node->num);

    std::string pathStr;
    for (int i = 0; i < path.size()-1; ++i) {
        pathStr += std::to_string(path[i]) + ".";
    }
    pathStr += std::to_string(path.back());
    std::cout << pathStr << "\n";

    for (auto nextNode : node->next) {
        printTree(nextNode, path);
    }

    delete node;
    path.pop_back();
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        Node* root = new Node;
        root->depth = 0;
        root->num = 0;
        root->parent = nullptr;
        root->visited = false;

        Node* node = root;

        for (int i = 0; i < n; ++i) {
            int val;
            scanf("%d", &val);

            Node* pos = nullptr;
            while (pos == nullptr) {
                pos = insertValue(node, val);
                if (pos == nullptr) {
                    node = node->parent;
                }
            }
            node = pos;
        }
        std::vector<int> path;
        for (auto nextNode : root->next) {
            printTree(nextNode, path);
        }

        delete root;
    }

    return 0;
}