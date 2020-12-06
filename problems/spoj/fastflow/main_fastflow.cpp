/*
 * Problem fastflow (spoj/fastflow)
 * Create time: Tue 06 Oct 2020 @ 17:06 (PDT)
 * Accept time: [!meta:end!]
 *
 */

#include <iostream>
#include <cstring>
#include <algorithm>
#include <utility>

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

void setIO(const std::string &name = "fastflow")
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
const int MX = 5011;
const int MXM = 3e4+10;

int N, M, S, T;
int dep[MX], eid[MX][MX];

struct Edge { ll f, t, w, n; } eg[MXM << 1]; int hd[MX], thd[MX], ecnt=2;
void addEdge(int u, int v, ll w, bool b=1)
{
    //if (eid[u][v]) eg[eid[u][v]].w += w;
    //else {
        eg[ecnt] = { u, v, w, hd[u] };
        //eid[u][v] = ecnt;
        hd[u] = ecnt++;
    //}
    if (b) addEdge(v, u, w, 0);
}

bool kdep()
{
    memset(dep, 0, sizeof dep); // FIX: clears-- clear dinic dep arrary each bfs
    memcpy(thd, hd, sizeof hd);
    int q[MX], ql=1, qr=0;
    dep[S] = 1, q[++qr] = S;
    for (;ql <= qr; ++ql)
    {
        //printf("q[%d] = %d\n", ql, q[ql]);
        if (q[ql] == T) return 1;
        for (int e=hd[q[ql]]; e; e=eg[e].n)
            if (!dep[eg[e].t] && eg[e].w > 0)
                dep[eg[e].t] = dep[q[ql]]+1,
                    q[++qr] = eg[e].t;
    }
    return 0;
}

ll aug(int c, ll mn)
{
    //printf("aug %d with %d\n", c, mn);
    if (c == T || !mn) return mn;
    //printf("epic\n");
    ll flo=0;
    //for (int e=hd[c]; e && mn; e=eg[e].n)
    for (; thd[c] && mn; thd[c]=eg[thd[c]].n)
    {
        //printf("    %d trying to go to %d (%d should %d)\n", c, eg[e].t, dep[eg[e].t], dep[c]+1);
        if (dep[eg[thd[c]].t] == dep[c]+1)
        {
            ll g = aug(eg[thd[c]].t, min(mn, eg[thd[c]].w));
            eg[thd[c]].w -= g;
            eg[thd[c]^1].w += g;
            flo += g;
            mn -= g; // ????
            if (!mn) break;
        }
    }
    if (!flo) dep[c] = 0;
    return flo;
}

int main()
{
    sc(N, M, S, T);
    //F(i, M) addEdge(sc(), sc(), sc());
    F(i, M)
    {
        int u, v, w; sc(u, v, w);
        addEdge(u, v, w);
    }
    ll ans = 0;
    while (kdep())
        ans += aug(S, 1e9);
    printf("%lld\n", ans);
}

