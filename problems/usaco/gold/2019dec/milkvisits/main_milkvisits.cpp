/*
 * Problem milkvisits (usaco/gold/2019dec/milkvisits)
 * Create time: Sat 08 Aug 2020 @ 11:29 (PDT)
 * Accept time: [!meta:end!]
 *
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <array>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <cmath>
#include <random>
#include <chrono>
#include <utility>
#include <algorithm>
#include <functional>

#define ll long long
#define dl double

#define pii pair<int, int>
#define pb push_back
#define mp make_pair
#define f first
#define s second

using namespace std;
const ll MX = 131072;
int N, M, type[MX];
vector<int> head[MX];

int st[18][MX<<1], occ[MX], par[MX], stsz=1;  // TODO: might be MX<<1
int D, rt[MX], alc=1, lc[MX<<6], rc[MX<<6], tsum[MX<<6];
void dumpseg(int i)
{
    printf("seg %d:", i);
    queue<int> q;
    q.push(rt[i]);
    int d = D-1;
    for (int i=1; i<D<<1; ++i)
    {
        int k = q.front(); q.pop();
        q.push(lc[k]); q.push(rc[k]);
        if (__builtin_popcount(i) == 1) { d>>=1; printf("\n"); }
        printf("%3d @ %-2d", tsum[k], k);
        for (int i=1; i<d; ++i) printf("        ");
    }
    printf("\n");
}
void dupe(int &k)
{
    lc[alc] = lc[k];
    rc[alc] = rc[k];
    tsum[alc] = tsum[k];
    k = alc++;
}
void su(int q, int v, int &k, int tl=1, int tr=D) // FIX: args--&k for pst
{
    //if (q < tl || q > tr) return;
    dupe(k);
    if (tl == tr) { tsum[k] += v; return; }
    int mid = tl + (tr-tl>>1);
    if (q <= mid) su(q, v, lc[k], tl, mid);
    else su(q, v, rc[k], mid+1, tr);
    //tsum[k] = tsum[lc[k]] + tsum[rc[k]]; // not needed
}
int sq(int q, int ku, int kv, int klca, int kslca, int tl=1, int tr=D)
{
    //printf("query %d @ %d %d %d %d (%d..%d)\n", q, ku, kv, klca, kslca, tl, tr);
    if (tl == tr) return tsum[ku] + tsum[kv] - tsum[klca] - tsum[kslca];
    int mid = tl + (tr-tl>>1);
    if (q <= mid) return sq(q, lc[ku], lc[kv], lc[klca], lc[kslca], tl, mid);
    else return sq(q, rc[ku], rc[kv], rc[klca], rc[kslca], mid+1, tr);
}

void dfs(int cur, int pre=0)
{
    par[cur] = pre;
    rt[cur] = rt[pre];
    su(type[cur], 1, rt[cur]);  // FIX: typo--update type[cur] not cur
    for (int nxt : head[cur])
        if (nxt != pre)
        {
            st[0][stsz++] = cur;
            dfs(nxt, cur);
        }
    occ[cur] = stsz;
    st[0][stsz++] = cur;
}
void klca()
{
    dfs(1);
    //for (int i=1; i<=N; ++i) printf("%3d", occ[i]); printf("\n");
    //for (int i=1; i<N<<1; ++i) printf("%3d", st[0][i]); printf("\n");
    for (int j=1; 1<<j < N<<1; ++j)
        for (int i=1; i+(1<<j) <= N<<1; ++i)
            st[j][i] = min(st[j-1][i], st[j-1][i+(1<<j-1)]);
    //for (int j=0; 1<<j < N<<1; ++j)
    //{
    //    for (int i=1; i<= N<<1; ++i)
    //        printf("%3d", st[j][i]);
    //    printf("\n");
    //}
}
int rmq(int l, int r)
{
    if (l > r) swap(l, r);
    ++r;
    int j; for (j=0; 2<<j <= r-l; ++j);
    //printf("j = %d, min(%d,%d;   %d,%d)\n", j, l, st[j][l], r-(1<<j), st[j][r-(1<<j)]);
    return min(st[j][l], st[j][r-(1<<j)]);
}

int main()
{
    freopen("milkvisits.in", "r", stdin);
    freopen("milkvisits.out", "w+", stdout);
    scanf("%d%d", &N, &M);
    for (D=1; D<N; D<<=1);
    for (int i=1; i<=N; ++i) scanf("%d", type+i);
    for (int i=2; i<=N; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        head[u].pb(v);
        head[v].pb(u);
    }

    klca();
    //for (int i=1; i<=N; ++i) dumpseg(i);
    for (int i=1; i<=M; ++i)
    {
        int u, v, t; scanf("%d%d%d", &u, &v, &t);
        int lca = rmq(occ[u], occ[v]);
        printf("%d", (bool)sq(t, rt[u], rt[v], rt[lca], rt[par[lca]]));
        //printf("lca: %d\n", rmq(occ[u], occ[v]));
    }
    printf("\n");

	return 0;
}

