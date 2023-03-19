Virtual_Tree
```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
inline int read() {
	int x = 0; bool f = 0; char ch = getchar();
	while (!isdigit(ch)) f |= ch == '-', ch = getchar();
	while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}
void write(ll x) {
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) write(x / 10);
	putchar(x % 10 ^ 48);
}
const int MAXN = 2.5e5 + 6;
int n, m, k, a[MAXN], mk[MAXN]; ll dp[MAXN];
int f[MAXN][21], dep[MAXN], mn[MAXN][21];
int hd[MAXN], cnte, dfn[MAXN], idx, stk[MAXN], top;
struct tEdge { int to, nxt, wei; } e[MAXN << 1];
inline void link(int u, int v, int w) {
	e[++cnte] = {v, hd[u], w};
	hd[u] = cnte;
}
void misaki(int u, int p) {
	f[u][0] = p; dep[u] = dep[p] + 1;
	dfn[u] = ++idx;
	for (int i = hd[u], v; i; i = e[i].nxt) {
		if ((v = e[i].to) == p) continue;
		misaki(v, u); mn[v][0] = e[i].wei;
	}
}
void init() {
	for (int j = 1; j <= 20; ++j)
		for (int i = 1; i <= n; ++i) {
			f[i][j] = f[f[i][j - 1]][j - 1];
			mn[i][j] = min(mn[i][j - 1], mn[f[i][j - 1]][j - 1]);
		}
}
inline int lca(int u, int v) {
	if (dep[u] < dep[v]) swap(u, v);
	for (int i = 20; ~i; --i)
		if (dep[f[u][i]] >= dep[v])
			u = f[u][i];
	if (u == v) return u;
	for (int i = 20; ~i; --i)
		if (f[u][i] != f[v][i])
			u = f[u][i], v = f[v][i];
	return f[u][0];
}
inline int calc(int u, int v) {
	if (dep[u] < dep[v]) swap(u, v);
	int ret = INT_MAX;
	for (int i = 20; ~i; --i)
		if (dep[f[u][i]] >= dep[v]) {
			ret = min(ret, mn[u][i]);
			u = f[u][i];
		}
	return ret;
}
inline bool cmp(int u, int v) { return dfn[u] < dfn[v]; }
inline void build() {
	sort(a + 1, a + k + 1, cmp);
	cnte = 0; hd[1] = 0;
	stk[top = 1] = 1;
	for (int i = 1; i <= k; ++i) {
		int g = lca(stk[top], a[i]);
		if (g != stk[top]) {
			while (dfn[g] < dfn[stk[top - 1]]) {
				int w = calc(stk[top], stk[top - 1]);
				link(stk[top], stk[top - 1], w);
				link(stk[top - 1], stk[top], w);
				--top;
			}
			int w = calc(stk[top], g);
			if (stk[top - 1] != g) {
				hd[g] = 0;
				link(stk[top], g, w);
				link(g, stk[top], w);
				stk[top] = g;
			} else {
				link(stk[top], g, w);
				link(g, stk[top], w);
				--top;
			}
		}
		hd[a[i]] = 0;
		stk[++top] = a[i];
	}
	while (top > 1) {
		int w = calc(stk[top], stk[top - 1]);
		link(stk[top], stk[top - 1], w);
		link(stk[top - 1], stk[top], w);
		--top;
	}
}
void misaka(int u, int p) {
	dp[u] = 0;
	for (int i = hd[u], v; i; i = e[i].nxt) {
		if ((v = e[i].to) == p) continue;
		misaka(v, u);
		if (mk[v]) dp[u] += e[i].wei;
		else dp[u] += min(dp[v], 1ll * e[i].wei);
	}
}
int main() {
	n = read();
	for (int i = 1; i < n; ++i) {
		int u = read(), v = read(), w = read();
		link(u, v, w); link(v, u, w);
	}
	memset(f, 0, sizeof f);
	memset(mn, 0x3f, sizeof mn);
	misaki(1, 0); init();
	m = read();
	while (m--) {
		k = read();
		for (int i = 1; i <= k; ++i) {
			a[i] = read();
			mk[a[i]] = 1;
		}
		build(); misaka(1, 0);
		write(dp[1]); putchar('\n');
		for (int i = 1; i <= k; ++i)
			mk[a[i]] = 0;
	}
	return 0;
}
```
