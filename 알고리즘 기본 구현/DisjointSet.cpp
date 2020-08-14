#include <vector>

class DisjointSet
{
private:
    std::vector<int> parent;
public:
    DisjointSet(int count)
    {
        parent.resize(count);
        for (int i = 0; i < count; ++i)
            parent[i] = i;
    }

    int findParent(int x)
    {
        if (x == parent[x])
            return x;
        
        return parent[x] = findParent(parent[x]);
    }

    void unionNodes(int x, int y)
    {
        int xPar = findParent(x);
        int yPar = findParent(y);

        parent[xPar] = yPar;
    }
};