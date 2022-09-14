#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

typedef long long Long;

struct Trie
{
    Trie* next[26];
    int count = 0;

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

    void insert(const char* key)
    {
        ++count;

        if (*key == '\0')
            return;
        else
        {
            int index = *key - 'a';
            if (!next[index])
                next[index] = new Trie;
            next[index]->insert(key + 1);
        }
    }
};

Trie words;
std::string sentence;
Long dp[200000];
int n;

const Long MOD = 1000000007;

Long countCases(int start)
{
    if (start >= (int)sentence.size())
        return 1;

    Long& result = dp[start];
    if (result != -1)
        return result;

    result = 0;
    int trieDepth = 0;
    for (Trie* t = words.next[sentence[start] - 'a']; (t != nullptr) && (t->count > 0); t = t->next[sentence[start + trieDepth] - 'a'])
    {
        result += t->count * countCases(start + trieDepth + 1);
        result %= MOD;
        ++trieDepth;
        if (start + trieDepth >= (int)sentence.size())
            break;
    }

    return result;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::cin >> n;
    for (int i = 0; i < n; ++i)
    {
        std::string word;
        std::cin >> word;
        words.insert(word.c_str());
    }
    std::cin >> sentence;
    std::fill(dp, dp + sentence.size(), -1);

    std::cout << countCases(0);

    return 0;
}