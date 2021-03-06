/*
 * Problem high_score_spfa4 (cses/graph/high_score_spfa4)
 * Create time: Fri 22 Jan 2021 @ 12:00 (PST)
 * Accept time: Fri 22 Jan 2021 @ 12:13 (PST)
 *
 */
#include <bits/stdc++.h>
#define ll long long
#define mt make_tuple
#define F(i, N) for (int i=1; i<=N; ++i)
#define db(...) fprintf(stderr, __VA_ARGS__)
using namespace std;

const ll MX = 5e3+10;
ll N, M;
ll ds[MX], vs[MX], inq[MX];
ll q[MX], ql=1, qr=0;
struct Edge { ll t, w, n; } eg[MX<<1]; ll hd[MX], ecnt=2;
void addEdge()
{
	ll u, v, w; scanf("%lld%lld%lld", &u, &v, &w);
	eg[ecnt] = { v, -w, hd[u] }; hd[u] = ecnt++;
}

ll ok = 1;
ll dvs[MX];
void dfs(ll c)
{
	if (dvs[c] || !ok) return;
	dvs[c] = 1;
	if (c == N) { ok = 0; return; }
	for (int e=hd[c]; e; e=eg[e].n)
		dfs(eg[e].t);
}

int main()
{
	scanf("%lld%lld", &N, &M);
	F(i, M) addEdge();
	memset(ds, 0x3f, sizeof ds);
	// memset(vs, 0, sizeof vs);
	// memset(inq, 0, sizeof inq);
	// memset(eg, 0, sizeof eg);
	// memset(hd, 0, sizeof hd);
	// ecnt = 2;
	ds[1] = 0; // FIX: spfa/bellman ford base case
	for (q[++qr] = 1; ql-1 != qr; ++ql%=MX) {
		inq[q[ql]] = 0;
		if (vs[q[ql]]++ > N) { dfs(q[ql]); continue; } // FIX: logic/flow-- don't continue relaxing inf loop, need to continue
		for (int e=hd[q[ql]]; e; e=eg[e].n)
			if (ds[eg[e].t] > ds[q[ql]] + eg[e].w) { // FIX: typo -- ds[n] > ds[c]+w, not ds[n] < ds[c]+w
				ds[eg[e].t] = ds[q[ql]] + eg[e].w;
				if (!inq[eg[e].t]) q[++qr%=MX] = eg[e].t, inq[eg[e].t] = 1;
			}
	}
	if (ok) printf("%lld\n", -ds[N]);
	else printf("-1\n");
}
