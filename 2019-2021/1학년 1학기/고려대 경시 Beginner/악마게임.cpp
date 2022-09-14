#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

string original;
int oriSize;
vector<pair<double, int>> merits;
vector<string> wordList;
int meritsSize = 0;

int main()
{
    int count;
    cin >> original >> count;
    oriSize = original.size();

    for (int i = 0; i < count; ++i)
    {
        string word;
        int effect;
        cin >> word >> effect;

        int wordSize = word.size();
        int oriIndex = 0;
        for (int j = 0; j < wordSize && oriIndex < oriSize; ++j)
        {
            if (original[oriIndex] == word[j])
                ++oriIndex;
        }

        if (oriIndex == oriSize)
        {
            merits.push_back(make_pair(-(double)effect / (double)(wordSize - oriSize), i));
            ++meritsSize;
        }
        wordList.push_back(word);
    }

    sort(merits.begin(), merits.end());

    if (merits.empty())
    {
        printf("No Jam");
    }
    else
    {
        cout << wordList[merits[0].second];
    }
    

    return 0;
}