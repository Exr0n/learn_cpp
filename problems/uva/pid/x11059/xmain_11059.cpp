/*
ID: spoytie2
TASK: 11059
LANG: C++14
*/

/*
 * Problem 11059 (onlinejudge/pid/11059)
 * Create time: Sun 26 Jan 2020 @ 14:22 (PST)
 * Accept time: Sun 26 Jan 2020 @ 16:21 (PST)
 * 
 * This is wrong answer somehow??
 */

#include <iostream>
#include <cstdio>
#include <tuple>
#include <vector>
#include <string>
#include <cstring>
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
#include <exception>
#include <algorithm>
#include <functional>

#define cn const int
#define ll long long
#define cl const long long
#define ca const auto &

#define vi vector<int>
#define pii pair<int, int>
#define vii vector<pii>

#define MP make_pair
#define PB push_back
#define F first
#define S second
#define INF 0x7FFFFFFF

// for macro overloading, see https://stackoverflow.com/questions/11761703/overloading-macro-on-number-of-arguments
// this set is designed for one indexed collections
#define FOR_(i, b, e) for (int i = (b); i < (e); ++i)
#define FOR(i, e) FOR_(i, 0, (e))
#define FORR_(i, b, e) for (int i = (e)-1; i >= (b); --i)
#define FORR(i, e) FORR_(i, 0, e)
#define SORT(a, n) std::sort((a), (a) + (n))
#define TRAV(a, x) for (auto &a : x)
#define SORTV(v) std::sort((v).begin(), (v).end())

void setIO(const std::string &name = "11059");

typedef struct
{
  int f, t, w, n;
} Edge;
#define TRAVE(s, e) for (int e = head[s]; e; e = edges[e].n)

const int MX = 20;
//#define __USING_EDGELIST
//void addEdge(cn a, cn b, cn w=1);
//Edge edges[MX*MX];
//int ect=1, head[MX];

using namespace std;
int N;
int seq[MX];

int main()
{

  for (int cs = 1; cin >> N; ++cs)
  {

    FOR(i, N)
    scanf("%d", &seq[i]);

    ll ret = 0;
    FOR(i, N)
    {
      ll prod = seq[i];
      FOR_(j, i+1, N+1) // N+1 to update ret for j=N
      {
        ret = max(ret, prod);
        prod *= seq[j];
      }
    }
    printf("Case #%d: The maximum product is %lld.\n\n", cs, ret);
  }

  return 0;
}

// boilerplate functions
void setIO(const string &name)
{
  ios_base::sync_with_stdio(0);
  cin.tie(0); // fast cin/cout
  if (fopen((name + ".in").c_str(), "r") != nullptr)
  {
    freopen((name + ".in").c_str(), "r", stdin);
    freopen((name + ".out").c_str(), "w+", stdout);
  }
}
