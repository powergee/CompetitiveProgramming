#include <iostream>
#include <vector>

class ClusterSystem {
private:
    std::vector<std::pair<int, int>> parent;

    std::pair<int, int> findRoot(int comp) {
        if (parent[comp].first == -1) {
            return { comp, 0 };
        }
        auto root = findRoot(parent[comp].first);
        return parent[comp] = { root.first, root.second + parent[comp].second };
    }

public:
    ClusterSystem(int n) {
        parent.resize(n+1, std::make_pair(-1, 0));
    }

    void connect(int center, int comp) {
        parent[center] = { comp, std::abs(comp-center) % 1000 };
    }

    int getDistance(int comp) {
        return findRoot(comp).second;
    }
};

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        ClusterSystem cluster(n);
        bool loop = true;
        while (loop) {
            char comm[2];
            int u, v;
            scanf("%s", comm);
            
            switch (comm[0])
            {
            case 'E':
                scanf("%d", &u);
                printf("%d\n", cluster.getDistance(u));
                break;
            case 'I':
                scanf("%d %d", &u, &v);
                cluster.connect(u, v);
                break;
            default:
                loop = false;
                break;
            }
        }
    }

    return 0;
}