/*
 * Problem 3729 (poj/3729)
 * Create time: Mon 10 Aug 2020 @ 11:05 (PDT)
 * Accept time: [!meta:end!]
 *
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

#define ll long long
#define dl double

#define pii pair<int, int>
#define pb push_back
#define mp make_pair
#define f first
#define s second

using namespace std;
const ll MX = 500101<<1;
const int MXV = 10010;
int N, M, K, inp[MX];

int sa[MX], rk[MX], tmp[MX], pos[MXV], lcp[MX];
void klcp()
{
    int mx = MXV;
    for (int i=1; i<=N; ++i)
        rk[i] = inp[i], sa[i] = i;
    for (int i=1; i>>1<N; i<<=1)    // FIX: typo--main loop in suffarray is i<<=1
    {
        int k=i>>1, p=k;
        for (int i=1; i<=k; ++i) tmp[i] = N-i+1;
        for (int i=1; i<=N; ++i) if (sa[i] > k) tmp[++p] = sa[i]-k;
        memset(pos, 0, 1+mx<<2);
        for (int i=1; i<=N; ++i) ++pos[rk[i]];
        for (int i=1; i<=mx; ++i) pos[i] += pos[i-1];
        for (int i=N; i; --i) sa[pos[ rk[tmp[i]] ]--] = tmp[i];
        for (int i=1; i<=N; ++i)
            tmp[sa[i]] = tmp[sa[i-1]] + (rk[sa[i]] != rk[sa[i-1]] || rk[sa[i]+k] != rk[sa[i-1]+k]);
        memcpy(rk, tmp, 1+N<<2);
    }
    for (int i=1; i<=N; ++i)
    {
        lcp[rk[i]] = max(lcp[rk[i-1]]-1, 0);
        if (rk[i] > 1)
            while (inp[i+lcp[rk[i]]] == inp[sa[rk[i]-1]+lcp[rk[i]]])
                ++lcp[rk[i]];
    }
}

int main()
{
    while (~scanf("%d%d%d", &N, &M, &K))
    {
        int i=1;
        for (; i<=N; ++i)
            scanf("%d", inp+i);
        inp[i] = MXV-5;
        N += M+1;
        M = N-M-1; // store string boundary for later
        for (++i; i<=N; ++i)
            scanf("%d", inp+i);
        //for (int i=1; i<=N; ++i) printf("%d ", inp[i]); printf("\n");
        klcp();

        //for (int i=1; i<=N; ++i) printf("%3d", sa[i]);  printf("\n");
        //for (int i=1; i<=N; ++i) printf("%3d", lcp[i]); printf("\n");

        int tot=0;
        for (int i=1; i<N; ++i)
        {
            //printf("i %d: ", i);
            int j=i+1;
            while (lcp[j] > K) ++j;
            //printf("j %d..", j);
            if (lcp[j] < K) continue;   // FIX: continue not break
            for (; lcp[j] > K-1; ++j)
            {
                if (min(sa[i], sa[j]) < M && max(sa[i], sa[j]) > M)
                {
                    //printf("%d..", j);
                    ++tot;
                }
            }
            //printf("%d\n", j);
        }
        printf("%d\n", tot);
    }

	return 0;
}

