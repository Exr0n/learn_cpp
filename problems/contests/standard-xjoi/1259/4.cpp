// after test rewrite of problem #4
// using pasted code from tutuuxy

#include <bits/stdc++.h>
#define cn const int
using namespace std;
cn MAXSZ = 1010;
typedef pair<int, int> edge;
vector<pair<int, edge>> G; // graph
int parent[MAXSZ];         // disjoint set
int retn = 0, retc = 0;

void AddWeightedEdge(int u, int v, int w)
{
    G.push_back(make_pair(w, edge(u, v)));
}

int find_set(int i)
{
    if (i == parent[i])
        return i;
    else
        return find_set(parent[i]);
}

void union_set(int u, int v)
{
    parent[u] = parent[v];
    // above is from pasted code, but don't we need what is below?
    //parent[find_set(u)] = parent[v];
}

void kruskal()
{
    int i, uRep, vRep;
    sort(G.begin(), G.end()); // increasing weight
    for (i = 0; i < G.size(); i++)
    {
        uRep = find_set(G[i].second.first);
        vRep = find_set(G[i].second.second);
        if (uRep != vRep)
        {
            //d*/     printf("adding %d-%d: %d\n", G[i].second.first, G[i].second.second, G[i].first);
            union_set(uRep, vRep);
            if (G[i].first > 0)
            {
                retc += G[i].first;
                retn++;
            }
        }
    }
}

int main()
{
    int n;
    scanf("%d", &n);

    // disjoint set primer
    for (int i = 1; i <= n; ++i)
    {
        parent[i] = i;
    }

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            int a;
            scanf("%d", &a);
            if (i == j)
                continue;
            //d*/ printf("  input: %d,%d : %d\n", i, j, a);
            AddWeightedEdge(i, j, a);
        }
    }
    kruskal();
    printf("%d\n%d", retn, retc);
    return 0;
}
