#include <iostream>
#include <queue>
#include <functional>
#include <map>

typedef long long Long;

struct Node {
    std::vector<int> subArr;
    int left, right;
    Node* leftChild = nullptr;
    Node* rightChild = nullptr;
};

void mergeSubArray(std::vector<int> &v1, std::vector<int> &v2, std::vector<int> &dest) {
    dest.resize(v1.size() + v2.size());
    size_t i1 = 0, i2 = 0, pos = 0;

    while (i1 < v1.size() && i2 < v2.size())
    {
        if (v1[i1] <= v2[i2])
            dest[pos++] = v1[i1++];
        else
            dest[pos++] = v2[i2++];
    }

    while (i1 < v1.size())
        dest[pos++] = v1[i1++];
    while (i2 < v2.size())
        dest[pos++] = v2[i2++];
}

Node* buildNode(int left, int right, std::vector<int>& arr) {
    Node *current = new Node;
    current->left = left;
    current->right = right;

    if (left == right)
        current->subArr.push_back(arr[left]);
    
    else 
    {
        int mid = (left+right)/2;
        Node* leftChild = buildNode(left, mid, arr);
        Node* rightChild = buildNode(mid+1, right, arr);
        mergeSubArray(leftChild->subArr, rightChild->subArr, current->subArr);
        current->leftChild = leftChild;
        current->rightChild = rightChild;
    }

    return current;
}

int countBigger(Node* current, int threshold, int left, int right) {
    if (current->right < left || right < current->left)
        return 0;

    if (left <= current->left && current->right <= right)
    {
        auto found = std::upper_bound(current->subArr.begin(), current->subArr.end(), threshold);
        return current->subArr.end() - found;
    }

    return countBigger(current->leftChild, threshold, left, right)
        + countBigger(current->rightChild, threshold, left, right);
}

int main() {
    int n, m, c;
    scanf("%d %d %d", &n, &m, &c);

    std::vector<int> colors(n+1);
    for (int i = 1; i <= n; ++i) {
        int p;
        scanf("%d", &p);
        colors[i] = p;
    }

    std::vector<std::vector<int>> graph(n+1);
    for (int i = 0; i < n-1; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    std::vector<std::pair<int, int>> ranges(n+1, { -1, -1 });
    std::vector<int> dfsNumber(n+1, 0);
    std::vector<int> treeSize(n+1, 0);
    int dfsCount = 0;
    std::function<void(int)> getRange = [&](int start) {
        treeSize[start] = 1;
        dfsNumber[start] = ++dfsCount;
        int left = dfsNumber[start];
        int right = dfsNumber[start];

        for (int next : graph[start]) {
            if (dfsNumber[next] == 0) {
                getRange(next);
                treeSize[start] += treeSize[next];
                left = std::min(left, ranges[next].first);
                right = std::max(right, ranges[next].second);
            }
        }
        ranges[start] = { left, right };
    };
    getRange(1);

    std::vector<int> colorRearranged(n+1, 0);
    for (int i = 1; i <= n; ++i) {
        colorRearranged[dfsNumber[i]] = colors[i];
    }
    
    Long answer = 0;
    auto root = buildNode(0, n, colorRearranged);
    for (int i = 0; i < m; ++i) {
        int vertex, color;
        scanf("%d %d", &vertex, &color);
        answer += treeSize[vertex]-countBigger(root, color, ranges[vertex].first, ranges[vertex].second);
        answer %= 1000000007LL;
    }

    printf("%lld", answer);

    return 0;
}