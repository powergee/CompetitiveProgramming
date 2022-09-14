#include <algorithm>
#include <vector>
#include <queue>
#include <string>
#include <iostream>

struct Trie
{
    Trie *next[26];
    Trie *fail;
    bool matched = false;

    Trie()
    {
        std::fill(next, next + 26, nullptr);
    }

    ~Trie()
    {
        for (int i = 0; i < 26; i++)
            if (next[i])
                delete next[i];
    }
    void insert(std::string &str, int start)
    {
        if ((int)str.size() <= start)
        {
            matched = true;
            return;
        }
        int nextIdx = str[start] - 'a';
        if (!next[nextIdx])
        {
            next[nextIdx] = new Trie;
        }
        next[nextIdx]->insert(str, start + 1);
    }
};

void buildFail(Trie *root)
{
    std::queue<Trie *> q;
    root->fail = root;
    q.push(root);
    while (!q.empty())
    {
        Trie *current = q.front();
        q.pop();

        for (int i = 0; i < 26; i++)
        {
            Trie *next = current->next[i];

            if (!next)
                continue;
            if (current == root)
                next->fail = root;
            else
            {
                Trie *dest = current->fail;

                while (dest != root && !dest->next[i])
                    dest = dest->fail;

                if (dest->next[i])
                    dest = dest->next[i];
                next->fail = dest;
            }

            if (next->fail->matched)
                next->matched = true;

            q.push(next);
        }
    }
}

bool find(Trie *root, std::string &query)
{
    Trie *current = root;
    bool result = false;

    for (int c = 0; c < (int)query.size(); c++)
    {
        int nextIdx = query[c] - 'a';

        while (current != root && !current->next[nextIdx])
            current = current->fail;

        if (current->next[nextIdx])
            current = current->next[nextIdx];

        if (current->matched)
        {
            result = true;
            break;
        }
    }

    return result;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    Trie trie;
    for (int i = 0; i < n; ++i) {
        std::string word;
        std::cin >> word;
        trie.insert(word, 0);
    }

    buildFail(&trie);

    int q;
    std::cin >> q;
    for (int i = 0; i < q; ++i) {
        std::string para;
        std::cin >> para;
        if (find(&trie, para)) {
            std::cout << "YES\n";
        } else {
            std::cout << "NO\n";
        }
    }
}