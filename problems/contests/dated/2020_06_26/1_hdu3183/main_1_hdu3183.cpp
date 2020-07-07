/*
 * Problem 1_hdu3183 (contests/dated/2020_06_26/1_hdu3183)
 * Create time: Mon 29 Jun 2020 @ 21:54 (PDT)
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
const ll MX = 1011;
ll N, M;
char buf[MX];
bool del[MX];

bool input()
{
    memset(buf, 0, sizeof buf);
    memset(del, 0, sizeof del);
    return ~scanf("%1010s%lld", buf, &M);
    //for (N=0; ; ++N)
    //{
    //    //char c = getchar();
    //    char c; scanf("%c", &c);
    //    printf("got '%c'\n", c);
    //    if (c == EOF) return false;
    //    if (c == '\n') continue;
    //    if (c == ' ') break;
    //    buf[N] = c;
    //}
    //printf("got '%s', awaiting m...\n", buf);
    //if (scanf("%lld\n", &M) < 0) return false;
    //scanf("%lld\n", &M);
    //return true;
}

int main()
{
    bool isfirst = 1;
    while (input())
    {
        N = strlen(buf);
        //if (isfirst) isfirst=0;
        //else --N;
        //printf("N %d M %d\n", N, M);

        for (ll i=0; i<N; ++i)
        {
            if (buf[i+1] < buf[i])
            {
                for (ll j=i; j>=0 && M; --j)    // FIX: equ--don't stop if del[j], since might be at very end and have extra to delete
                {
                    if (buf[j] <= buf[i+1])     // FIX: equ--break backtracking even if le not lt, cuz multiple of same num is ok
                        break;
                    //printf("del %d\n", j);
                    if (!del[j]) --M;
                    del[j] = 1;
                }
            }
        }
        bool gone=0;
        for (ll i=0; i<N; ++i)
        {
            if (!del[i] && (gone || buf[i] > '0'))
            {
                printf("%c", buf[i]);
                gone=1;
            }
        }
        //printf("gone? %d\n", gone);
        if (!gone) printf("0");
        printf("\n");
    }


	return 0;
}

