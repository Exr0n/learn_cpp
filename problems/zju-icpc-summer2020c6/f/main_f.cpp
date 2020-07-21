/*
 * Problem f (zju-icpc-summer2020c6/f)
 * Create time: Mon 20 Jul 2020 @ 19:33 (PDT)
 * Accept time: [!meta:end!]
 *
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
#include <algorithm>
using namespace std;
const int MX = 1e5+100;
const int MXK = 20;

int N, K, gift[MX], fav[MX], val[MXK], dps[5100][MXK];

int main()
{
    scanf("%d%d", &N, &K);
    for (int i=0; i<N*K; ++i)
    {
        int d; scanf("%d", &d);
        ++gift[d];
    }
    for (int i=0; i<N; ++i)
    {
        int d; scanf("%d", &d);
        ++fav[d];
    }
    for (int i=1; i<=K; ++i)
        scanf("%d", &val[i]);

    for (int i=1; i<=N; ++i)
        for (int j=0; j<=N*K; ++j)
            for (int k=0; k<=K && k<=j; ++k)
                dps[i][j] = max(dps[i][j], val[k] + dps[i-1][j-k]);

    int sum=0;
    for (int f=0; f<=1e5+10; ++f)
    {
        //printf("fav %d: %d, %d => %d\n", f, gift[f], fav[f], dps[gift[f]][fav[f]]);
        sum += dps[fav[f]][gift[f]];
    }
    printf("%d\n", sum);

	return 0;
}



