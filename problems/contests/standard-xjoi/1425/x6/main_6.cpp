/*
 * Problem 6 (contests/standard-xjoi/1425/6)
 * Create time: Tue 09 Jun 2020 @ 08:21 (PDT)
 * Accept time: [!meta:end!]
 *
 */

#include <iostream>
#include <cstring>
#include <sstream>
#include <cstdio>
#include <tuple>
#include <vector>
#include <string>
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
const int MX = 10111;

typedef pair<int, int> val;

int N, M, coeff[MX][3], counter[MX];

bool cmp(val lhs, val rhs)
{
	return lhs < rhs;
}

val heap[MX];
int alloc=1;
void heapup(int cur)
{
	if (cur == 1) return;
	if (cmp(heap[cur], heap[cur/2]))
	{
		swap(heap[cur], heap[cur/2]);
		heapup(cur/2);
	}
}
//void heapdown(int cur)
//{
//    printf("heapdown %d\n", cur);
//    if (!cur) return;
//    if (cur*2 >= alloc) return;
//    printf("but what?\n");
//    if (cur*2+1 == alloc)
//    {
//        if (cmp(heap[2*cur], heap[cur]))
//        {
//            swap(heap[cur], heap[cur*2]);
//            heapdown(cur*2);
//        }
//    }
//    else
//    {
//        printf("so either is possible\n");
//        int lo = cur*2 + heap[cur*2] > heap[cur*2+1];
//        if (cmp(heap[lo], heap[cur]))
//        {
//            swap(heap[cur], heap[lo]);
//            heapdown(lo);
//        }
//    }
//}

// copied from problem 2
void heapdo(int cur)
{
	if (cur * 2 >= alloc) return;
	if (cur * 2 + 1 == alloc)
	{
		if (cmp(heap[cur*2], heap[cur]))
			swap(heap[cur], heap[cur*2]);
	}
	else if (heap[cur] > min(heap[cur*2], heap[cur*2+1]))
	{
		int lo = cur*2 + (!cmp(heap[cur*2], heap[cur*2+1]));
		swap(heap[cur], heap[lo]);
		heapdo(lo);
	}
}

void insert(val d)
{
	heap[alloc] = d;
	heapup(alloc++);
}
val pop()
{
	if (alloc == 1) return mp(0, 0);
	swap(heap[1], heap[--alloc]);
	heapdo(1);
	return heap[alloc];
}

void ins_next(int cur)
{
	int x = ++counter[cur];
	insert(mp(coeff[cur][0] *x*x + coeff[cur][1]*x + coeff[cur][2], cur));
}

int main()
{
	//while (true)
	//{
	//    int c, d; scanf("%d", &c);
	//    if (c == 1) { scanf("%d", &d); insert(d); }
	//    if (c == 2) printf("%d\n", pop());
	//}

	scanf("%d%d", &N, &M);
	for (int i=0; i<N; ++i)
		for (int j=0; j<3; ++j)
			scanf("%d", &coeff[i][j]);

	for (int i=0; i<N; ++i) ins_next(i);
	for (int i=0; i<M; ++i)
	{
		pair<int, int> top = pop();
		ins_next(top.s);
		printf("%d ", top.f);
	}
	printf("\n");

	return 0;
}

