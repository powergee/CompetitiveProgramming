#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>

struct Trie
{
    Trie *next[26];
    Trie *fail;
    // 실제 매칭된 문자열이 필요하다면 아래 정의 사용
    // std::vector<std::string> outputs;
    // 매칭 여부만 필요하다면
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
            //outputs.push_back(str);
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

            /*if(next->fail->outputs.size() > 0) 
                next->outputs.insert(next->outputs.end(), current->outputs.begin(), current->outputs.end());*/
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

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;
    Trie root;

    for (int i = 0; i < n; ++i)
    {
        std::string element;
        std::cin >> element;
        root.insert(element, 0);
    }

    buildFail(&root);
    int q;
    std::cin >> q;

    for (int i = 0; i < q; ++i)
    {
        std::string query;
        std::cin >> query;
        std::cout << (find(&root, query) ? "YES\n" : "NO\n");
    }
}