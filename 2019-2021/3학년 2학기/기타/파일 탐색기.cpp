#include <cctype>
#include <algorithm>
#include <vector>
#include <iostream>
#include <string>
#include <map>

int charToIndex(char ch) {
    if ('A' <= ch && ch <= 'Z') {
        return (ch-'A')*2;
    }
    return (ch-'a')*2+1;
}

class Atom {
private:
    std::string contents;
    std::string inner;
    bool isChar;
public:
    Atom(std::string& str, int& start) {
        if (std::isdigit(str[start])) {
            isChar = false;
            int end;
            for (end = start; end < str.size() && std::isdigit(str[end]); ++end);
            contents = str.substr(start, end-start);
            int innerStart = str.find_first_not_of('0', start);
            if (innerStart != std::string::npos && innerStart < end) {
                inner = str.substr(innerStart, end-innerStart);
            }
            start = end;
        } else {
            isChar = true;
            contents = str[start++];
        }
    }

    bool operator<(const Atom& atom) const {
        if (isChar && atom.isChar) {
            return charToIndex(contents[0]) < charToIndex(atom.contents[0]);
        } else if (!isChar && !atom.isChar) {
            if (inner.size() != atom.inner.size()) {
                return inner.size() < atom.inner.size();
            } else if (inner != atom.inner) {
                return inner < atom.inner;
            }
            return contents.size() < atom.contents.size();
        } else {
            return !isChar;
        }
    }
};

class FileName {
private:
    std::string origin;
    std::vector<Atom> atoms;
public:
    FileName(std::string& str) {
        origin = str;
        int start = 0;
        while (start < str.size()) {
            atoms.emplace_back(Atom(str, start));
        }
    }

    bool operator<(const FileName& fn) const {
        int minSize = std::min(atoms.size(), fn.atoms.size());
        for (int i = 0; i < minSize; ++i) {
            if (atoms[i] < fn.atoms[i]) {
                return true;
            } else if (fn.atoms[i] < atoms[i]) {
                return false;
            }
        }

        if (atoms.size() != fn.atoms.size()) {
            return atoms.size() < fn.atoms.size();
        }
        return false;
    }

    std::string toString() const {
        return origin;
    }
};

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    std::cin >> n;
    std::vector<FileName> names;
    for (int i = 0; i < n; ++i) {
        std::string str;
        std::cin >> str;
        names.emplace_back(str);
    }

    std::sort(names.begin(), names.end());
    for (int i = 0; i < n; ++i) {
        std::cout << names[i].toString() << "\n";
    }

    return 0;
}

