/*
 * Problem lasers (usaco/gold/2016dec/lasers)
 * Create time: Sun 06 Dec 2020 @ 11:50 (PST)
 * Accept time: Sun 06 Dec 2020 @ 12:15 (PST)
 *
 */

#include <set>
#include <map>
#include <tuple>
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
#define N(e,c) for (int e=hd[c]; e; e=eg[e].n)
#define TN(e,c,p) N(e,c) if (eg[e].t != p)

inline ll pow(ll b, ll e, ll m)
{
    ll ret=1;
    for (; e; e>>=1, (b*=b)%=m)
        if (e&1) (ret *= b)%=m;
    return ret;
}

void setIO(const std::string &name = "lasers")
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
ll gcd(ll a, ll b) { while (b^=a^=b^=a%=b); return a; }

//struct Edge { int t, n; } eg[MX*MX]; int hd[MX], ecnt=2;
using namespace std;
const int MX = 1e5+11;

int N;
int pos[MX][2];
map<int, vector<int> > ax[2];
int dist[MX];

int main()
{
    setIO();
    sc(N);
    F(i, N+2)
    {
        F(d, 2) sc(pos[i][d-1]);
        F(d, 2) ax[d&1][pos[i][d-1]].pb(i);
    }

    //printf("x:\n"); for (auto m : ax[0]) { printf("    %d:", m.f); for (auto n : m.s) printf("%3d", n); printf("\n"); }
    //printf("y:\n"); for (auto m : ax[1]) { printf("    %d:", m.f); for (auto n : m.s) printf("%3d", n); printf("\n"); }

    memset(dist, 0x3f, sizeof dist);
    dist[1] = -1;
    queue<pair<int, bool> > q;
    q.push(mp(1, 0)); q.push(mp(1, 1));
    while (q.size())
    {
        int c; bool dir;
        tie(c, dir) = q.front(); q.pop();
        //printf("%d: at %d dir %d\n", dist[c], c, dir);
        if (c == 2) { printf("%d\n", dist[c]); return 0; }
        for (auto n : ax[dir][pos[c][!dir]])
            if (dist[n] > 1e9)
                //printf("    going to %d\n", n),
                dist[n] = min(dist[n], dist[c]+1),
                q.push(mp(n, !dir));
    }
    printf("IMPOSSIBLE\n");
}

