/*
TASK: uva1626
LANG: C++14
*/

/*
 * Problem uva1626 (contests/dated/2020_04_27/uva1626)
 * Create time: Wed 29 Apr 2020 @ 12:42 (PDT)
 * Accept time: [!meta:end!]
 *  RE on test case `))`
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
#define ca const auto &

#define vi vector<int>
#define pii pair<int, int>
#define vii vector<pii>

#define pb push_back
#define eb emplace_back
#define mp make_pair
#define f first
#define s second
#define g(t, i) get<i>(t)
#define mt make_tuple

#define FOR_(i, b, e) for (long long i = (b); i < (e); ++i)
#define FOR(i, e) FOR_(i, 0, (e))
#define FORR_(i, b, e) for (long long i = (e)-1; i >= (b); --i)
#define FORR(i, e) FORR_(i, 0, e)
#define TRAV(a, x) for (auto &a : x)

using namespace std;
const int MX = 2011;
stack<char> opened;
char out[MX];
int kase;

char op(char c)
{
	const char pairs[2][2] = { {'(', ')'}, {'[', ']'} };
	for (int i=0; i<2; ++i)
		for (int j=0; j<2; ++j)
			if (c == pairs[i][j])
				return pairs[i][1-j];
    printf("uh oh spaghetio\n");
    return 0;
}

int main()
{
	scanf("%d\n", &kase);
	kase *= 2;
	while (kase --)
	{
		memset(out, 0, sizeof out);
		int ptr=0;
		char c;
		while (scanf("%c", &c))
		{
            //printf("hrm '%c'\n", c); fflush(stdout);
			if (c == '\n') break;
			if (c == '(' || c == '[')
				opened.push(c);
			else
			{
				//printf("char: %c, top: %c\n", c, opened.empty() ? 0 : opened.top()); fflush(stdout);
				if (!opened.empty())
				{
					while (op(c) != opened.top())
					{
						out[ptr++] = op(opened.top());
						opened.pop();
					}
					opened.pop();
				}
				else
					out[ptr++] = op(c);
			}
			out[ptr++] = c;
		}
		while (!opened.empty())
		{
			out[ptr++] = op(opened.top());
			opened.pop();
		}
		printf("%s\n", out);
	}

    return 0;
}

