/*
ID: spoytie2
TASK: 156
LANG: C++14
*/

/*
 * Problem 156 ([!meta:srcpath!])
 * Create time: Mon 17 Feb 2020 @ 09:53 (PST)
 * Accept time: [!meta:end!]
 *
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

#define FOR_(i, b, e) for (int i = (b); i < (e); ++i)
#define FOR(i, e) FOR_(i, 0, (e))
#define FORR_(i, b, e) for (int i = (e)-1; i >= (b); --i)
#define FORR(i, e) FORR_(i, 0, e)
#define SORT(a, n) std::sort((a), (a) + (n))
#define TRAV(a, x) for (auto &a : x)
#define TRAVE(e, s) for (int e = head[s]; e; e = edges[e].n)
#define SORTV(v) std::sort((v).begin(), (v).end())

void setIO(const std::string &name = "156");

using namespace std;
const int MX = -1;
map<string, int> id_count;
map<string, string> id_original;

string normalize(const string word)
{
    string ret = word;
    TRAV(c, ret) c = tolower(c);
    sort(ret.begin(), ret.end());
    return ret;
}

int main()
{
    setIO();
    string s;
    while (cin >> s)
    {
        if (s[0] == '#') break;
        string repr = normalize(s);
        //printf("%s\n", repr.c_str());
        ++ id_count[repr];
        id_original[repr] = s;
    }

    set<string> ret;
    TRAV(p, id_count)
    {
        if (p.S == 1) // only one of id
        {
            ret.insert(id_original[p.F]);
        }
    }
    TRAV(str, ret) printf("%s\n", str.c_str());

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
