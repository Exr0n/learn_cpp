/*
 * Problem 2 (contests/dated/2020_05_31/2)
 * Create time: Sun 31 May 2020 @ 15:32 (PDT)
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

using namespace std;
const int MX = 100111;

int N, M, capa[MX];
vector<pair<int, int> > reqs;
int D, segt[MX], addv[MX];

void dump()
{
	for (int i=1; i<2<<D; ++i)
	{
		if (__builtin_popcount(i) == 1) printf("\n");
		printf("%3d +%3d  ", segt[i], addv[i]);
	}
	printf("\n");
}
void build()
{
	D = log2(N)+1;
	memset(segt, 0, sizeof segt);
	memset(addv, 0, sizeof addv);
	for (int i=0; i<N; ++i)
		segt[(1<<D)+i] = -capa[i];
	for (int i=(1<<D)-1; i>0; --i)
		segt[i] = max(segt[i*2], segt[i*2+1]);
}
void update(int ql, int qr, int v=1, int k=1, int tl=1, int tr=1<<D)
{
	if (qr < tl || tr < ql) return;
	if (ql <= tl && tr <= qr)
	{
		segt[k] += v;
		addv[k] += v;
		return;
	}
	int mid = tl + (tr-tl)/2;
	update(ql, qr, v, k*2, tl, mid);
	update(ql, qr, v, k*2+1, mid+1, tr);
	segt[k] = max(segt[k*2], segt[k*2+1]);
}
int query(int ql, int qr, int k=1, int tl=1, int tr=1<<D, int acc=0)
{
	if (qr < tl || tr < ql) return 0;
	if (ql <= tl && tr <= qr) return segt[k] + acc;
	acc += addv[k];
	int mid = tl + (tr-tl)/2;
	return max(query(ql, qr, k*2, tl, mid, acc), query(ql, qr, k*2+1, mid+1, tr, acc));
}

bool cmp(const pair<int, int> &lhs, const pair<int, int> &rhs)
{	// compare by range then start index
	if (lhs.s - lhs.f == rhs.s - rhs.f) return lhs < rhs;
	return lhs.s - lhs.f < rhs.s - rhs.f;
}

int main()
{
	scanf("%d%d", &N, &M);
	for (int i=0; i<N; ++i)
		scanf("%d", &capa[i]);
	build();

	//dump();
	//while (true)
	//{
	//    char c=' '; while (c<'a'||c>'z') scanf("%c", &c);
	//    int a, b; scanf("%d%d", &a, &b);
	//    if (c == 'q') printf("%d\n", query(a, b));
	//    if (c == 'u') update(a, b);
	//    printf("finished processing command %c\n", c);
	//    dump();
	//}

	for (int i=0; i<M; ++i)
	{
		int l, r;
		scanf("%d%d", &l, &r);
		reqs.eb(l, r);
	}
	sort(reqs.begin(), reqs.end(), cmp);

	ll tot=0;
	for (int i=0; i<M; ++i)
	{
		int l = reqs[i].f;
		int r = reqs[i].s;

		update(l, r);
		int q = query(1, N);
		//printf("%d (%d %d): %d\n", i, l, r, q);
		if (q > 0)
			update(l, r, -1); // undo that
		else
			++tot;
	}
	printf("%lld\n", tot);

	return 0;
}

