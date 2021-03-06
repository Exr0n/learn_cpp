/*
TASK: threesum
LANG: C++14
*/

/*
 * Problem threesum (usaco/gold/2020jan/threesum)
 * Create time: Mon 13 Apr 2020 @ 12:00 (PDT)
 * Accept time: [!meta:end!]
 *
 */

#include <iostream>
#include <sstream>
#include <cstdio>
#include <cassert>
#include <tuple>
#include <vector>
#include <string>
#include <cstring>
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
#include <iterator>
#include <exception>
#include <algorithm>
#include <functional>

#define ll long long
#define dl double
#define ca const auto &

#define vi vector<int>
#define pii pair<int, int>
#define vii vector<pii>

#define pb push_back
#define eb emplace_back
#define mp make_pair
#define F first
#define S second
#define g(t, i) get<i>(t)
#define mt make_tuple

#define FOR_(i, b, e) for (long long i = (b); i < (e); ++i)
#define FOR(i, e) FOR_(i, 0, (e))
#define FORR_(i, b, e) for (long long i = (e)-1; i >= (b); --i)
#define FORR(i, e) FORR_(i, 0, e)
#define TRAV(a, x) for (auto &a : x)

void setIO(const std::string &name = "threesum");

using namespace std;
const int MX = 5111;
// TODO: ll?
map<pair<int, int>, unordered_multiset<int> > twosum;
int N, Q, arr[MX];

int main()
{
    setIO();
    scanf("%d%d", &N, &Q);
    FOR(i, N) scanf("%d", &arr[i]);

    /*
1 100
1
1 4
1 5
2 1
2 2
2 3
2 4
    * /
    twosum[mp(1, 2)];
    twosum[mp(1, 3)];
    twosum[mp(1, 4)];
    twosum[mp(2, 2)];
    twosum[mp(2, 3)];
    */

    FOR(q, Q)
    {
	int l, r;
	scanf("%d%d", &l, &r);
	--l; --r;

	if (r - l +1 < 3) continue;

	twosum[mp(l, l)]; // create empty base set in case nothing is suitable
	pair<pair<int, int>, unordered_multiset<int> > twosum_set = *(prev(twosum.upper_bound(mp(l, r))));

	// construct
	while (twosum_set.F.S < r)				// while we haven't gotten the right range yet
	{
	    for (int i=twosum_set.F.F; i<=twosum_set.F.S; ++i)		// for each item in the set
		twosum_set.S.insert(arr[twosum_set.F.S+1] + arr[i]);	// 	insert it paired with new
	    twosum_set.F.S += 1;					// increment the right side two match new set
	    if ((twosum_set.F.S - twosum_set.F.F)%100 == 0) 
		twosum[twosum_set.F] = twosum_set.S;			// save for future branching
	}

	/*
10 100
1 2 3 4 5 6 7 8 9 10
... test data
	* /
	printf("best set: %d %d (", twosum_set.F.F, twosum_set.F.S);
	TRAV(n, twosum_set.S) printf("%3d", n); printf("  )\n");
	*/

	// check
/*
5 100
0 -2 -1 2 3
1 4
2 4
2 5
*/
	ll sum=0;
	FOR_(c, l, r+1)
	{
	    if (arr[c] == 0)
		sum += twosum_set.S.count(0);
	    else
	    {
		sum += twosum_set.S.count(-1*arr[c]);
		// sum -= twosum_set.S.count(-2*arr[c]);
		// printf("    c %d, sum %d\n", c, sum);
	    }
	}
	printf("%lld\n", sum/3);
    }

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
