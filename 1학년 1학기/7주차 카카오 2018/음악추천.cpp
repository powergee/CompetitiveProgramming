#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <hash_set>
using namespace std;

int N, K, J;
vector<int> tree[100001];
vector<int> singerMusics[100001];
// J * Count of musics of the singer
int singerGoals[100001];
// Sum of scores
int singerScores[100001];
vector<tuple<int, int, int>> calcs;
hash_set<int> singersOfSub[100001];

int main()
{
    scanf("%d %d %d", &N, &K, &J);

    for (int i = 2; i <= N; ++i)
    {
        int parent;
        scanf("%d", &parent);
        tree[parent].push_back(i);
    }

    for (int i = 0; i < N; ++i)
    {
        int singerNum;
        scanf("%d", &singerNum);
        singerMusics[singerNum].push_back(i);
    }

    for (int i = 0; i < K; ++i)
    {
        int T, P, S;
        scanf("%d %d %d", &T, &P, &S);
        calcs.push_back(make_tuple(T, P, S));
    }
    sort(calcs.begin(), calcs.end());

    
}