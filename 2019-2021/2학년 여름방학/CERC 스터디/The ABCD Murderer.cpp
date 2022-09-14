#include <iostream>
#include <string>
#include <algorithm>
#include <queue>
#include <vector>

std::vector<std::string> words;
std::string goal;

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

bool isAbleToFill(std::vector<std::pair<int, int>>& coverages)
{
    if (coverages.empty())
        return false;

    std::pair<int, int> covUnion = coverages.back();
    for (int i = coverages.size()-2; i >= 0; --i)
    {
        if (covUnion.first-1 <= coverages[i].second)
            covUnion.first = std::min(covUnion.first, coverages[i].first);
        else
            return false;
    }

    return covUnion.first == 0 && covUnion.second == (int)goal.size()-1;
}

bool findLeftmost(std::vector<std::pair<int, int>>& coverages, int& lastIndex, std::pair<int, int>& interval)
{
    int leftmost = -1;
    for (int i = lastIndex; i >= 0; --i)
    {
        if (coverages[i].second < interval.first-1)
        {
            lastIndex = i;
            break;
        }

        if (leftmost == -1 && coverages[i].first < interval.first ||
            leftmost != -1 && coverages[i].first < coverages[leftmost].first)
            leftmost = i;
    }

    interval = coverages[leftmost];
    return leftmost != -1;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int count;
    Trie root;
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
            int start = i - words[current->output].size() + 1;
            coverages.emplace_back(start, i);
            std::cout << start << ", " << i << "\n";
        }
    }

    if (isAbleToFill(coverages))
    {
        if (coverages.size() == 1)
            std::cout << 1;
        else
        {
            int answer = 1, lastIndex = (int)coverages.size()-2;
            std::pair<int, int> interval = coverages.back();

            while (findLeftmost(coverages, lastIndex, interval))
                ++answer;

            std::cout << answer;
        }
    }
    else
        std::cout << -1;

    return 0;
}