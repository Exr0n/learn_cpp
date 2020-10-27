/*
 * Problem wpuzzles (spoj/wpuzzles)
 * Create time: Mon 26 Oct 2020 @ 18:29 (PDT)
 * Accept time: [!meta:end!]
 * AC Automaton in all the directions
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

void setIO(const std::string &name = "wpuzzles")
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
const int MX = 1e3+10;
const int MXL = 1e6+11;

int T, L, C, W;
int trie[MXL][30], fail[MXL], dep[MXL], isw[MXL], lcnt=1;
//                                      ^^^ isw[i] means this node is the end of word i
bool hasw[MXL];  // has a word in failpointer linkedlist

char grid[MX][MX];

const int delta[] = {-1, 0, 1};

int main()
{
    sc(T);
    while (T--)
    {
        sc(L, C, W);
        for (int i=0; i<L; ++i) scanf("%s", grid[L]);
        // construct trie
        for (int i=1; i<=W; ++i)
        {
            int cur=0, c=_gc()-'A';
            while (true)
            {
                if (c < 0)
                {
                    printf("\n");
                    hasw[cur] = 1, isw[cur] = i;
                    break;
                }
                if (!trie[cur][c])
                    //par[lcnt] = cur,
                    dep[lcnt] = dep[cur]+1,
                    trie[cur][c] = lcnt++;
                printf("got char '%c' -> %d\n", c+'A', trie[cur][c]);
                cur = trie[cur][c], c = _gc() - 'A';
            }
        }
        // construct failpointers
        typedef pair<pair<int, int>, char> QState;
        queue<QState> q;   // cur, pre, char
        //q.push(mp(mp(0, 0), 26));
        for (int i=0; i<26; ++i) if (trie[0][i])    // FIX: push root node manually
            q.push(mp(mp(trie[0][i], 0), 26));  // FIX: first order nodes don't failpoint to themselves
        while (!q.empty())
        {
            QState c = q.front(); q.pop();
            printf("q cur %d <- %d (%c)\n", c.f.f, c.f.s, c.s+'A');
            // construct fail pointer
            for (fail[c.f.f] = fail[c.f.s]; fail[c.f.f] && !trie[fail[c.f.f]][c.s]; // FIX: typo--go while fail[c.f.f], not stop when it
                    fail[c.f.f] = fail[fail[c.f.f]]);   // kmp flashbacks
            if (trie[fail[c.f.f]][c.s]) fail[c.f.f] = trie[fail[c.f.f]][c.s];
            hasw[c.f.f] |= hasw[fail[c.f.f]];
            // bfs
            for (int i=0; i<26; ++i) if (trie[c.f.f][i])
                q.push(mp(mp(trie[c.f.f][i], c.f.f), i));
        }

        printf("    "); for (int i=0; i<26; ++i) printf("%3c", i+'A'); printf("\n");
        for (int i=0; i<lcnt; ++i)
        {
            printf("%-3d ", i);
            for (int j=0; j<26; ++j)
                if (trie[i][j]) printf("%3d", trie[i][j]);
                else printf("  .");
            printf("   ->%3d     isw %3d hasw %d\n", fail[i], isw[i], hasw[i]);
        }

        // check the grid
        for (int i=0; i<L; ++i)
        {
            // start on left side
            // start on right side
        }
        for (int i=0; i<C; ++i)
        {
            // start from the top edge (no diagonals)
            // bottom edge (no diagonals)
        }
    }
}

