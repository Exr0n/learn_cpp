/*
 * Problem lca_2 (spoj/lca_2)
 * Create time: Sat 23 Jan 2021 @ 21:02 (PST)
 * Accept time: Sat 23 Jan 2021 @ 21:42 (PST)
 *
 */
#include <bits/stdc++.h>
#define ll long long
#define mt make_tuple
#define F(i, N) for (int i=1; i<=N; ++i)
#define db(...)
using namespace std;

const ll MX = 1e3+10;
ll T, N, M;
ll par[MX][32];
ll dep[MX];

ll kdep(ll c)
{
	if (par[c][0] && !dep[c])
		dep[c] = kdep(par[c][0])+1;
	return dep[c];
}

void lca()
{
	ll u, v; scanf("%lld%lld", &u, &v);
	if (u == v) { printf("%lld\n", u); return; } // FIX: print a newline smah
	if (dep[u] < dep[v]) swap(u, v); // u is deeper
	for (ll i=19; i--;) {
		db("i = %d\n", i);
		if (dep[par[u][i]] >= dep[v])
			u = par[u][i];      // FIX: typo -- u=par[u][i] not i=par[u][i]
	}
	// db("u = %d, v = %d, common dep = %d\n", u, v, dep[u]);
	for (ll i=19; i--;) {
		if (par[u][i] != par[v][i])
			u = par[u][i], v = par[v][i];
	}
	if (u == v) { printf("%lld\n", u); return; }
	printf("%lld\n", par[u][0]);
}
// void lca()
// {
// 	ll u, v; scanf("%lld%lld", &u, &v);
//     if (dep[u] < dep[v]) swap(u, v); // u is lower
//     //printf("u %d dep %d       v %d dep %d\n", u, dep[u], v, dep[v]);
//     for (int i=15; ~i; --i)
//         if (dep[par[u][i]] >= dep[v])    // FIX: lower down is >= not <=
//             u = par[u][i];
//     //printf("u %d dep %d       v %d dep %d\n", u, dep[u], v, dep[v]);
//     for (int i=15; ~i; --i)
//         if (par[u][i] != par[v][i])
//             u = par[u][i], v = par[v][i];
//     //printf("u %d v %d\n", u, v);
//     if (u != v) u = par[u][0];   // FIX: don't take parent if already equal (one was ancestor of another)
//     printf("%lld\n", u);
// }


int main()
{
	scanf("%lld", &T);
	F(tt, T) {
		scanf("%lld", &N);
		F(i, N) {
			scanf("%lld", &M);
			F(j, M) {
				ll x; scanf("%lld", &x);
				par[x][0] = i;
				// eg[ecnt] = { x, hd[i] }; hd[i] = ecnt++;
			}
		}

		ll rt;
		F(i, N) if (!par[i][0]) rt = i;

		F(j, 19) F(i, N) {
			par[i][j] = par[par[i][j-1]][j-1];
		}
		dep[rt] = 1;
		F(i, N) kdep(i);

		F(i, N) { for (int j=0; j<20; ++j) db("%3d", par[i][j]); db("\n"); }

		ll Q; scanf("%lld", &Q);
		printf("Case %d:\n", tt);
		F(i, Q) lca();
	}
}
