Tree Divide (P6329)
```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read() {
	int x = 0; bool f = 0; char ch = getchar();
	while (!isdigit(ch)) f |= ch == '-', ch = getchar();
	while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}
void write(int x) {
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) write(x / 10);
	putchar(x % 10 ^ 48);
}
const int MAXN = 1e5 + 6;
int n, m, lans, cnte, hd[MAXN], a[MAXN];
int mxp[MAXN], vis[MAXN], sz[MAXN], rt, fa[MAXN];
unordered_map <int, int> dis[MAXN];
struct tEdge { int to, nxt; } e[MAXN << 1];
inline void link(int u, int v) {
	e[++cnte] = {v, hd[u]};
	hd[u] = cnte;
}
struct Fenwick_Tree {
	vector <int> f[MAXN]; int sz[MAXN];
	inline int lowbit(int x) { return x & -x; }
	inline void add(int u, int x, int v) {
		for (++x; x < sz[u]; x += lowbit(x))
			f[u][x] += v;
	}
	inline int ask(int u, int x) {
		int ret = 0;
		for (x = min(++x, sz[u] - 1); x; x -= lowbit(x))
			ret += f[u][x];
		return ret;
	}
} B1, B2;
inline void init(int rt, int sz) {
	for (int i = 0; i < sz + 6; ++i)
		B1.f[rt].emplace_back(0);
	B1.sz[rt] = sz + 6;
	for (int i = 0; i < sz + 6; ++i)
		B2.f[rt].emplace_back(0);
	B2.sz[rt] = sz + 6;
}
void updsize(int u, int p) {
	sz[u] = 1;
	for (int i = hd[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if (v == p || vis[v]) continue;
		updsize(v, u); sz[u] += sz[v];
	}
}
void getroot(int u, int p, int all) {
	mxp[u] = 0;
	for (int i = hd[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if (v == p || vis[v]) continue;
		getroot(v, u, all);
		mxp[u] = max(mxp[u], sz[v]);
	}
	mxp[u] = max(mxp[u], all - sz[u]);
	if (mxp[u] < mxp[rt]) rt = u;
}
void getdis(int u, int p, int r) {
	dis[r][u] = dis[r][p] + 1;
	for (int i = hd[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if (v == p || vis[v]) continue;
		getdis(v, u, r);
	}
}
void solve(int u, int p) {
	vis[u] = 1;
	dis[u][0] = -1; getdis(u, 0, u);
	for (int i = hd[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if (v == p || vis[v]) continue;
		updsize(v, u);
		mxp[rt = 0] = INT_MAX; getroot(v, 0, sz[v]);
		init(rt, sz[v]); fa[rt] = u; solve(rt, u);
	}
}
inline void modify(int u, int v) {
	int x = u;
	while (x) {
		int f = fa[x];
		B1.add(x, dis[x][u], v);
		if (f) B2.add(x, dis[f][u], v);
		x = f;
	}
}
inline int query(int u, int k) {
	int l = 0, x = u, ans = 0;
	while (x) {
		int d = dis[x][u];
		if (d > k) {
			l = x; x = fa[x];
			continue;
		}
		ans += B1.ask(x, k - d);
		if (l) ans -= B2.ask(l, k - d);
		l = x; x = fa[x];
	}
	return ans;
}
int main() {
	n = read(), m = read();
	for (int i = 1; i <= n; ++i) a[i] = read();
	for (int i = 1; i < n; ++i) {
		int u = read(), v = read();
		link(u, v); link(v, u);
	}
	updsize(1, 0);
	mxp[rt = 0] = INT_MAX; getroot(1, 0, n);
	init(rt, n); fa[rt] = 0; solve(rt, 0);
	for (int i = 1; i <= n; ++i)
		modify(i, a[i]);
	while (m--) {
		int op = read(), x = read() ^ lans, y = read() ^ lans;
		if (!op) write(lans = query(x, y)), putchar('\n');
		else modify(x, y - a[x]), a[x] = y;
	}
	return 0;
}
```
