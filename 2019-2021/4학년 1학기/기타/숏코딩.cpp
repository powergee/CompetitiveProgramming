#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <set>

class Monomial {
private:
    inline static std::map<std::string, int> strIdMap;
    inline static std::map<int, std::string> idStrMap;

    int id;
    bool variable = true;
    
public:
    static int countVariables() {
        return int(strIdMap.size());
    }

    static std::string idToString(int id) {
        return idStrMap[id];
    }

    Monomial(std::string str) {
        if (strIdMap.count(str) == 0) {
            id = strIdMap.size();
            strIdMap[str] = id;
            idStrMap[id] = str;
        }
        id = strIdMap[str];
        for (char ch : str) {
            if (!isalpha(ch)) {
                variable = false;
                break;
            }
        }
    }

    std::string getString() const {
        return idStrMap[id];
    }

    int getId() const {
        return id;
    }

    bool isVariable() const {
        return variable;
    }
};

enum ExpKind {
    VarVar, // variable = variable
    VarCon, // variable = constant
    ConCon  // constant = constant
};

struct CompareExp {
private:
    Monomial *lhs, *rhs;
    bool neq;

public:
    CompareExp(std::string term) {
        int found;
        if ((found = term.find("!=")) != term.npos) {
            neq = true;
        } else {
            neq = false;
            found = term.find("==");
        }
        lhs = new Monomial(term.substr(0, found));
        rhs = new Monomial(term.substr(found+2));
        if (!lhs->isVariable() && rhs->isVariable()) {
            std::swap(lhs, rhs);
        }
    }

    Monomial getLHS() const {
        return *lhs;
    }

    Monomial getRHS() const {
        return *rhs;
    }

    bool isEqual() const {
        return !neq;
    }

    ExpKind getKind() const {
        if (!lhs->isVariable()) {
            return ConCon;
        } else if (!rhs->isVariable()) {
            return VarCon;
        } else {
            return VarVar;
        }
    }

    std::string getString() {
        return lhs->getString() + (neq ? "!=" : "==") + rhs->getString();
    }
};

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

std::string compress(std::string line) {
    int start = 0;
    std::vector<CompareExp> eqExps[3], neqExps[3];
    while (start < line.size()) {
        auto found = line.find("&&", start);
        std::string currTerm;
        if (found == line.npos) {
            currTerm = line.substr(start);
            start = line.size();
        } else {
            currTerm = line.substr(start, found-start);
            start = found+2;
        }
        CompareExp exp(currTerm);
        (exp.isEqual() ? eqExps : neqExps)[exp.getKind()].push_back(exp);
    }

    std::vector<std::string> answer;

    for (auto& exp : eqExps[ConCon]) {
        if (exp.getLHS().getString() != exp.getRHS().getString()) {
            return "1==0";
        }
    }
    for (auto& exp : neqExps[ConCon]) {
        if (exp.getLHS().getString() == exp.getRHS().getString()) {
            return "1==0";
        }
    }
    
    DisjointSet dsu(Monomial::countVariables());
    for (auto& exp : eqExps[VarVar]) {
        dsu.unionNodes(exp.getLHS().getId(), exp.getRHS().getId());
    }
    for (auto& exp : eqExps[VarCon]) {
        dsu.unionNodes(exp.getLHS().getId(), exp.getRHS().getId());
    }

    std::map<int, int> clusterConst;
    for (auto& exp : eqExps[VarCon]) {
        auto var = exp.getLHS();
        auto con = exp.getRHS();
        int cluId = dsu.findParent(var.getId());
        if (clusterConst.count(cluId) && clusterConst[cluId] != con.getId()) {
            return "1==0";
        }
        clusterConst[cluId] = con.getId();
    }

    std::map<int, std::set<int>> clusterSet;
    std::map<int, std::string> shortestToken;

    auto updateShortestToken = [&](const Monomial& m) {
        auto found = shortestToken.find(dsu.findParent(m.getId()));
        if (found == shortestToken.end()) {
            shortestToken[dsu.findParent(m.getId())] = m.getString();
        } else {
            auto curr = m.getString();
            if (curr.size() < found->second.size()) {
                found->second = curr;
            }
        }
    };

    auto updateClusterInfo = [&](const CompareExp& exp) {
        int lhs = exp.getLHS().getId();
        int rhs = exp.getRHS().getId();
        clusterSet[dsu.findParent(lhs)].insert(lhs);
        clusterSet[dsu.findParent(rhs)].insert(rhs);
        updateShortestToken(exp.getLHS());
        updateShortestToken(exp.getRHS());
    };

    for (auto& exp : eqExps[VarVar]) {
        updateClusterInfo(exp);
    }
    for (auto& exp : eqExps[VarCon]) {
        updateClusterInfo(exp);
    }

    std::set<std::pair<int, int>> neqAdded;
    for (auto& exp : neqExps[VarCon]) {
        auto var = dsu.findParent(exp.getLHS().getId());
        auto con = dsu.findParent(exp.getRHS().getId());
        if (neqAdded.count({var, con})) {
            continue;
        }
        neqAdded.emplace(var, con);
        neqAdded.emplace(con, var);

        if (clusterConst.count(var)) {
            if (clusterConst[var] == con) {
                return "1==0";
            }
        } else {
            std::string varStr = (shortestToken.count(var) ? shortestToken[var] : Monomial::idToString(var));
            std::string conStr = (shortestToken.count(con) ? shortestToken[con] : Monomial::idToString(con));
            answer.push_back(varStr + "!=" + conStr);
        }
    }

    for (auto& exp : neqExps[VarVar]) {
        int lhs = dsu.findParent(exp.getLHS().getId());
        int rhs = dsu.findParent(exp.getRHS().getId());
        if (neqAdded.count({lhs, rhs})) {
            continue;
        }
        neqAdded.emplace(lhs, rhs);
        neqAdded.emplace(rhs, lhs);

        if (clusterConst.count(lhs) && clusterConst.count(rhs)) {
            if (clusterConst[lhs] == clusterConst[rhs]) {
                return "1==0";
            }
        } else if (lhs == rhs) {
            return "1==0";
        } else {
            std::string lhsStr = (shortestToken.count(lhs) ? shortestToken[lhs] : exp.getLHS().getString());
            std::string rhsStr = (shortestToken.count(rhs) ? shortestToken[rhs] : exp.getRHS().getString());
            answer.push_back(lhsStr + "!=" + rhsStr);
        }
    }

    for (auto [cluId, elements] : clusterSet) {
        std::string shortest = shortestToken[cluId];
        for (auto ele : elements) {
            std::string eleStr = Monomial::idToString(ele);
            if (shortest != eleStr) {
                answer.push_back(shortest + "==" + eleStr);
            }
        }
    }

    std::string result;
    if (answer.empty()) {
        result += "1==1";
    } else {
        result += answer[0];
        for (int i = 1; i < answer.size(); ++i) {
            result += "&&" + answer[i];
        }
    }
    return result;
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    while (!std::cin.eof()) {
        std::string line;
        std::cin >> line;
        if (!line.empty()) {
            std::cout << compress(line) << "\n";
        }
    }

    return 0;
}