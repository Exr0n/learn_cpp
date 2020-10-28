/*
 * Problem high_score (cses/graph/high_score)
 * Create time: Tue 27 Oct 2020 @ 19:17 (PDT)
 * Accept time: [!meta:end!]
 *
 */

#include <set>
#include <queue>
#include <cstdio>
#include <cstdlib>
#include <utility>
#include <cstring>
#include <iostream>
#include <algorithm>


#define ll long long
#define dl double

#define gpq(T) priority_queue<T, deque<T>, greater<T> >
#define CMA , // https://stackoverflow.com/q/13842468/10372825
#define pii pair<int, int>
#define pb push_back
#define mp make_pair
#define f first
#define s second
#define lb(x) ((x)&-(x))

#define F(i,b) for (ll i=1; i<=(b); ++i)
#define R(i,b) for (ll i=(b); i>=1; --i)
//struct Edge { int u, v, n; } eg[MX]; int hd[MX], ecnt=0;

inline ll pow(ll b, ll e, ll m)
{
    ll ret=1;
    for (; e; e>>=1, (b*=b)%=m)
        if (e&1) (ret *= b)%=m;
    return ret;
}

void setIO(const std::string &name = "high_score")
{
    //ios_base::sync_with_stdio(0); cin.tie(0);
    if (fopen((name + ".in").c_str(), "r") != 0)
        freopen((name + ".in").c_str(), "r", stdin),
        freopen((name + ".out").c_str(), "w+", stdout);
}
#define _gc getchar_unlocked
inline bool sc(ll &n)
{
    int neg = 1;
    register char c;
    do c = _gc(); while (isspace(c));
    if (c == '-') neg = -1, c = _gc();
    for (n=0; c >= '0' && c <= '9'; c=_gc())
        (n *= 10) += (c-'0');
    n *= neg;
    return c != EOF;
}
inline int sc() { ll x; sc(x); return x; }
#define _ilb inline bool
_ilb sc(int&a){ll x;bool b=sc(x);a=x;return b;}
_ilb sc(int&a,int&b){return sc(a)&&sc(b);}
_ilb sc(int&a,int&b,int&c){return sc(a,b)&&sc(c);}
_ilb sc(int&a,int&b,int&c,int&d){return sc(a,b)&&sc(c,d);}
_ilb sc(ll&a,ll&b){return sc(a)&&sc(b);}
_ilb sc(ll&a,ll&b,ll&c){return sc(a,b)&&sc(c);}
_ilb sc(ll&a,ll&b,ll&c,ll&d){return sc(a,b)&&sc(c,d);}
#define gcd(_a, _b) ({auto a=_a;auto\
    b=_b;while(b)(a)%=(b),(a)^=(b)^=(a)^=(b);a;})

using namespace std;
const int MX = 2511;
const int MXE = 5010;

ll N, M, dist[MX];
//struct Edge { ll f, t, w; } eg[MXE];
struct Edge { int f, t, w, n; } eg[MX]; int hd[MX], ecnt=2;
void addEdge()
{
    int a = sc();
    eg[ecnt].f = a;
    eg[ecnt].t = sc();
    eg[ecnt].w = sc();
    eg[ecnt].n = hd[a];
    hd[a] = ecnt++;
}

bool vis[MX], die=0;

void dfs(int c)
{
    printf("brick at %d\n", c);
    if (vis[c]) return;
    vis[c] = 1;
    if (c == N) { die=1; return; }
    for (int e=hd[c]; e; e=eg[e].n)
        dfs(eg[e].t);
}

int main()
{
    sc(N, M);
    //for (int i=1; i<=M; ++i) eg[i] = { sc(), sc(), -sc() };
    //for (int i=1; i<=M; ++i)
    //    eg[i].f = sc(),
    //    eg[i].t = sc(),
    //    eg[i].w = -sc();
    for (int i=1; i<=M; ++i) addEdge();
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;    // FIX: base case
    for (int i=1; i<=N; ++i)
        for (int j=1; j<=N; ++j) for (int e=hd[j]; e; e=eg[e].n)
            dist[eg[e].t] = min(dist[eg[e].t], dist[eg[e].f] + eg[e].w);

    for (int j=1; j<=N; ++j) for (int e=hd[j]; e; e=eg[e].n)
        if (dist[eg[e].t] > dist[eg[e].f] + eg[e].w)
            dfs(eg[e].t);

    if (die) printf("-1\n");
    else printf("%lld\n", dist[N]);

    //ll tmp = dist[N];
    //for (int i=1; i<=N; ++i) for (int e=1; e<=M; ++e)
    //    dist[eg[e].t] = min(dist[eg[e].t], dist[eg[e].f] + eg[e].w);
    //if (dist[N] != tmp) printf("-1\n");
    //else printf("%lld\n", -dist[N]);
        //if (dist[eg[e].t] > dist[eg[e].f] + eg[e].w)
            //dist[eg[e].t] = dist[eg[e].f] + eg[e].w;

    //for (int i=1; i<=N; ++i) for (int e=1; e<=M; ++e)
    //    if (dist[eg[e].t] > dist[eg[e].f] + eg[e].w)
    //    { printf("-1\n"); return 0; }
}

