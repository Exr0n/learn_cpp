/*
TASK: k
LANG: C++14
*/

/*
 * Problem k (contests/hpi2020/k)
 * Create time: Sat 07 Mar 2020 @ 09:43 (PST)
 * Accept time: [!meta:end!]
 *
 */

#include <iostream>
#include <sstream>
#include <cstdio>
#include <tuple>
#include <vector>
#include <string>
#include <cstring>
#include <list>
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

#define ll long long
#define dl double
#define ca const auto &

#define vi vector<int>
#define pii pair<int, int>
#define vii vector<pii>

#define MP make_pair
#define PB push_back
#define EB emplace_back
#define F first
#define S second

#define FOR_(i, b, e) for (long long i = (b); i < (e); ++i)
#define FOR(i, e) FOR_(i, 0, (e))
#define FORR_(i, b, e) for (long long i = (e)-1; i >= (b); --i)
#define FORR(i, e) FORR_(i, 0, e)
#define TRAV(a, x) for (auto &a : x)

void setIO(const std::string &name = "k");

using namespace std;
const int MX = 100010;
ll N, K;
map<ll, ll> cnt;
set<ll> nums;
vector<ll> order;
//ll order[MX];

int main()
{
    setIO();
    scanf("%lld%lld", &N, &K);
    FOR(i, N)
    {
        ll t;
        scanf("%lld", &t);
        nums.insert(t);
        ++cnt[t];
    }

    TRAV(n, nums) order.PB(n);
    sort(order.begin(), order.end(), [](ll l, ll r){ return cnt[l] > cnt[r]; });
    ll sum=0;
    TRAV(i, order)
    {
        if (!K) break;
        --K;
        sum += cnt[i];
    }

    printf("%lld\n", sum);

    return 0;
}

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