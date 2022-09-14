#include <iostream>
#include <algorithm>
#include <vector>

class DisjointSet {
private:
    std::vector<int> parent;
public:
    DisjointSet(int count) {
        parent.resize(count);
        for (int i = 0; i < count; ++i) {
            parent[i] = i;
        }
    }

    int findParent(int x) {
        if (x == parent[x]) {
            return x;
        }
        return parent[x] = findParent(parent[x]);
    }

    void unionNodes(int x, int y) {
        int xPar = findParent(x);
        int yPar = findParent(y);

        parent[xPar] = yPar;
    }
};

enum Robot { A, B };

struct BlockOp {
    Robot robot;
    int number;
    std::vector<int> chains;
    BlockOp(Robot r, int n) : robot(r), number(n) {}
};

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n, m;
    std::cin >> n >> m;
    std::vector<BlockOp> blocks;

    DisjointSet dsu(2*n+2);
    for (int i = 0; i < m; ++i) {
        std::string robot, oper;
        int number;
        std::cin >> robot >> oper >> number;
        blocks.emplace_back(robot == "A" ? A : B, number);
        dsu.unionNodes(number, number+1);
    }

    // Basic Checks
    auto basicBlock = std::find_if(blocks.begin(), blocks.end(), [](auto b) { return b.number == 1; });
    if (blocks.front().robot != A || basicBlock == blocks.end()) {
        std::cout << "NO";
        return 0;
    }

    auto addChain = [&](BlockOp& block) -> bool {
        int nextNumber = dsu.findParent(block.number);
        if (nextNumber > 2*n) {
            // std::cout << "addChain failed: " << block.robot << ", BLOCK, " << block.number << "\n";
            return false;
        }
        block.chains.push_back(nextNumber);
        // std::cout << "addChain succeeded: assigned " << nextNumber << " to " <<  block.robot << ", BLOCK, " << block.number << "\n";
        dsu.unionNodes(nextNumber, nextNumber+1);
        return true;
    };

    int operCount = m;
    bool possible = true;
    for (int i = 0; i+1 < m && possible; ++i) {
        if (blocks[i].robot == blocks[i+1].robot) { // 홀수번 Chain
            possible = possible && addChain(blocks[i]);
            operCount++;
        }
    }

    if (!possible || (operCount % 2 == 1 && !addChain(blocks.back()))) {
        std::cout << "NO";
        return 0;
    }

    while (operCount < 2*n) {
        addChain(*basicBlock);
        operCount++;
    }

    std::cout << "YES\n";
    int currRobot = A;
    for (int i = 0; i < m; ++i) {
        std::cout << ((currRobot++) % 2 == A ? "A" : "B") << " BLOCK " << blocks[i].number << "\n";
        for (int chain : blocks[i].chains) {
            std::cout << ((currRobot++) % 2 == A ? "A" : "B") << " CHAIN " << chain << "\n";
        }
    }

    return 0;
}