#include <iostream>
#include <string>
#include <algorithm>
#include <queue>
#include <vector>

std::vector<std::string> words;

struct Trie
{
    Trie* next[26];
    Trie* fail;
    int output = -1;

    Trie()
    {
        std::fill(next, next + 26, nullptr);
        fail = nullptr;
    }

    ~Trie()
    {
        for (int i = 0; i < 26; i++)
            if (next[i])
                delete next[i];
    }

    void insert(const char *key, int wordIndex)
    {
        if (*key == '\0')
            output = wordIndex;
        else
        {
            int index = *key - 'a';
            if (!next[index])
                next[index] = new Trie;
            next[index]->insert(key + 1, wordIndex);
        }
    }

    void insert(int wordIndex)
    {
        insert(words[wordIndex].c_str(), wordIndex);
    }
};

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int count;
    Trie root;
    std::string goal;
    std::cin >> count >> goal;

    words.resize(count);
    for (int i = 0; i < count; ++i)
        std::cin >> words[i];

    std::sort(words.begin(), words.end());
    words.erase(std::unique(words.begin(), words.end()), words.end());

    count = (int)words.size();
    for (int i = 0; i < count; ++i)
        root.insert(i);

    std::queue<Trie*> q;
    root.fail = &root;
    q.push(&root);

    while (!q.empty())
    {
        Trie* current = q.front();
        q.pop();

        for (int i = 0; i < 26; ++i)
        {
            Trie* next = current->next[i];

            if (!next)
                continue;

            if (current == &root)
                next->fail = &root;
            else
            {
                Trie* dest = current->fail;
                while (dest != &root && !dest->next[i])
                    dest = dest->fail;

                if (dest->next[i])
                    dest = dest->next[i];
                
                next->fail = dest;
            }

            q.push(next);
        }
    }

    std::vector<std::pair<int, int>> coverages;
    Trie* current = &root;
    for (int i = 0; i < (int)goal.size(); ++i)
    {
        int nextIndex = goal[i] - 'a';
        while (current != &root && !current->next[nextIndex])
            current = current->fail;
        
        if (current->next[nextIndex])
            current = current->next[nextIndex];
        
        if (current->output != -1)
        {
            std::pair<int, int> currCover = {i-(int)words[current->output].size()+1, i};
            while (!coverages.empty() && (
                currCover.first <= coverages.back().first && coverages.back().second <= currCover.second ||
                coverages.size() > 1 && currCover.first <= coverages[coverages.size()-2].second+1))
                coverages.pop_back();

            coverages.push_back(currCover);
        }
    }

    if (coverages.empty())
        std::cout << -1;
    else
    {
        int initSize = (int)coverages.size();
        bool success = true;
        std::pair<int, int> covUnion = coverages.back();
        coverages.pop_back();

        while (!coverages.empty() && success)
        {
            std::pair<int, int> current = coverages.back();
            coverages.pop_back();
            
            if (current.second+1 < covUnion.first)
                success = false;
            else
                covUnion.first = current.first;
        }

        if (covUnion.first != 0 || covUnion.second != (int)goal.size()-1)
            success = false;
        
        if (success)
            std::cout << initSize;
        else
            std::cout << -1;
    }

    return 0;
}