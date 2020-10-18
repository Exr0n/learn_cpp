/*
 * Problem dinic3 (../algorithms/graphs/network_flow/dinic3)
 * Create time: Fri 16 Oct 2020 @ 06:50 (PDT)
 * Accept time: [!meta:end!]
 *
 */

#include <iostream>
#include <cstring>
#include <algorithm>
#include <utility>
#include <queue>

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

void setIO(const std::string &name = "dinic3")
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
inline ll sc() { ll x; sc(x); return x; }
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
const int MX = 8e3+11;

ll N, M, S, T, dep[MX];

struct Edge { ll t, w, n; } eg[60000<<2]; ll hd[MX], aug_ptr[MX], ecnt=2;

void addEdge(ll u, ll v, ll w)
{
    eg[ecnt].t = v;
    eg[ecnt].w = w;
    eg[ecnt].n = hd[u];
    hd[u] = ecnt++;
}

ll q[MX];
bool kdep()
{
    memset(dep, 0, sizeof dep);
    memcpy(aug_ptr, hd, N+1<<2);
    int qr=0;
    q[qr++] = S;
    dep[S] = 1;
    for (int ql=0; ql<qr; ++ql)
    {
        //ll c = q.front(); q.pop();
        if (q[ql] == T) return 1;
        for (ll e=hd[q[ql]]; e; e=eg[e].n)
            if (!dep[eg[e].t] && eg[e].w)
                dep[eg[e].t] = dep[q[ql]]+1, q[qr++] = eg[e].t;
    }
    return 0;
}

#define ag aug_ptr
ll aug(ll c, ll mn)
{
    if (!mn || c == T) return mn;
    ll flo=0;
    //for (ll e=aug_ptr[c]; e; e=eg[e].n)
    for (; mn && ag[c];)
    {
        if (dep[eg[ag[c]].t] == dep[c]+1)
            if (ll g = aug(eg[ag[c]].t, min(mn, eg[ag[c]].w)))
            {
                flo += g;
                eg[ag[c]].w -= g;
                eg[ag[c]^1].w += g;
                mn -= g;
            }
        if (mn) aug_ptr[c] = eg[aug_ptr[c]].n;
    }
    return flo;
}

int main()
{
    //sc(N, M, S, T);
    sc(N, M);
    S = 1, T = N;
    for (ll i=1; i<=M; ++i)
        addEdge(sc(), sc(), sc());

    ll flo=0;
    while (kdep())
        flo += aug(S, 1e9);
    printf("%lld\n", flo);
}

