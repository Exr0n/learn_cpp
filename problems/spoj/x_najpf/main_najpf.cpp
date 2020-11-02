/*
 * Problem najpf (spoj/najpf)
 * Create time: Mon 02 Nov 2020 @ 11:25 (PST)
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

void setIO(const std::string &name = "najpf")
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
const int MX = 1e6+11;

char buf[MX], pat[MX];
int T, N, P, pi[MX], q[MX];

void kpi()
{
    pi[0] = -1;
    for (int i=1; i<P; ++i)
    {
        for (pi[i] = pi[i-1]; ~pi[i] && pat[pi[i]+1] != pat[i];
                pi[i] = pi[pi[i]]);
        if (pat[pi[i]+1] == pat[i]) ++pi[i];
    }
}

int main()
{
    sc(T);
    while (T--)
    {
        scanf("%s%s", buf, pat);
        N = strlen(buf);
        P = strlen(pat);
        kpi();
        //for (int i=0; i<P; ++i) printf("%3d", pi[i]); printf("\n");
        int p=-1, ql=0, qr=0;
        for (int p=-1, i=0; i<N; ++i)
        {
            for (; ~p && pat[p+1] != buf[i]; p=pi[p]);
            if (pat[p+1] == buf[i]) ++p;
            if (p+1 == P) q[qr] = i-P, qr = (qr+1)%N;
        }
        if (qr-ql)
        {
            printf("%d\n", qr-ql);
            for (; ql!=qr; ql = (ql+1)%N)
                printf("%d ", q[ql]+2);
            printf("\n");
        }
        else printf("Not Found\n\n");
    }
}

