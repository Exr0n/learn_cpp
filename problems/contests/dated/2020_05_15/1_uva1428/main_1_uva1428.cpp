/*
TASK: 1_uva1428
LANG: C++14
*/

/*
 * Problem 1_uva1428 (contests/dated/2020_05_15/1_uva1428)
 * Create time: Sun 24 May 2020 @ 11:32 (PDT)
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

#define pb push_back
#define eb emplace_back
#define mp make_pair
#define f first
#define s second

#define FOR_(i, b, e) for (long long i = (b); i < (e); ++i)
#define FOR(i, e) FOR_(i, 0, (e))
#define FORR_(i, b, e) for (long long i = (e)-1; i >= (b); --i)
#define FORR(i, e) FORR_(i, 0, e)
#define TRAV(a, x) for (auto &a : x)

void setIO(const std::string &name = "1_uva1428");

using namespace std;
const int MX = 20111;
int N, skill[MX];
struct Node
{
	int d, w, x=1, s=1;
	Node *c[2] = {};
	Node(int d): d(d), w(rand()) {}
} *root = nullptr;
void setSize(Node *cur)
{
	cur->s = cur->x;
	if (cur->c[0]) cur->s += cur->c[0]->s;
	if (cur->c[1]) cur->s += cur->c[1]->s;
}
void rotate(Node *&cur, bool dir)
{
	if (!cur || !cur->c[dir]) return;
	Node *thn = cur->c[dir];
	cur->c[dir] = thn->c[!dir];
	setSize(cur);
	thn->c[!dir] = cur;
	setSize(thn);
	cur = thn;
}
Node *insert(Node *&cur, int d)
{
	if (!cur) return cur = new Node(d);
	if (cur->d == d) { ++cur->x; ++cur->s; return cur; }
	Node *&stp = cur->c[cur->d < d];
	Node *ins = insert(stp, d);
	if (cur->w < stp->w) rotate(cur, cur->d < d);
	setSize(cur);
	return ins;
}
ll getRank(Node *cur, int d)
{
	if (!cur) return 0;
	const int lsz = cur->c[0] ? cur->c[0]->s : 0;
	if (d < cur->d) return getRank(cur->c[0], d); 
	if (cur->d == d) return lsz;
	return lsz + cur->s + getRank(cur->c[1], d);
}
void dump(Node *cur, int lay=1)
{
	dump(cur->c[1], lay+1);
	for (int i=0; i<lay; ++i) printf("    ");
	printf("%d x%d w%d s%d\n", cur->d, cur->x, cur->w, cur->s);
	dump(cur->c[0], lay+1);
}

ll solve()
{
	scanf("%d", &N);
	// TODO
}

int main()
{
	int N;
	scanf("%d", &N);
	for (int i=0; i<N; ++i)
	{
		int t; scanf("%d", &t); insert(root, t);
	}
	while (1)
	{
		int d; scanf("%d", &d);
		printf("%d\n", getRank(root, d));
		dump(root);
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
