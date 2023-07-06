Merge->Segment_Tree (P4556)
```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read() {
	int x = 0; bool f = 0; char ch = getchar();
	while (!isdigit(ch)) f |= ch == '-', ch = getchar();
	while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}
const int MAXD = 1e5, MAXN = MAXD + 6;
int n, m, cnte, hd[MAXN], ans[MAXN];
int rt[MAXN], f[MAXN][21], dep[MAXN];
struct tEdge { int to, nxt; } e[MAXN << 1];
inline void link(int u, int v) {
	e[++cnte] = {v, hd[u]};
	hd[u] = cnte;
}
struct Segment_Tree {
#define mid (l + r >> 1)
	int tot;
	struct tNode { int sum, mx, lc, rc; } t[MAXN * 50];
	inline void pushup(int k) {
		int x = t[t[k].lc].sum >= t[t[k].rc].sum ? t[k].lc : t[k].rc;
		t[k].sum = t[x].sum; t[k].mx = t[x].mx;
	}
	void update(int &k, int l, int r, int x, int v) {
		if (!k) k = ++tot;
		if (l == r) {
			t[k].sum += v;
			t[k].mx = x;
			return;
		}
		if (x <= mid) update(t[k].lc, l, mid, x, v);
		else update(t[k].rc, mid + 1, r, x, v);
		pushup(k);
	}
	int merge(int p, int q, int l, int r) {
		if (!p || !q) return p | q;
		if (l == r) return t[p].sum += t[q].sum, p;
		t[p].lc = merge(t[p].lc, t[q].lc, l, mid);
		t[p].rc = merge(t[p].rc, t[q].rc, mid + 1, r);
		return pushup(p), p;
	}
#undef mid
} T;
void misaka(int u, int p) {
	f[u][0] = p; dep[u] = dep[p] + 1;
	for (int i = 1; i <= 20; ++i)
		f[u][i] = f[f[u][i - 1]][i - 1];
	for (int i = hd[u], v; i; i = e[i].nxt) {
		if ((v = e[i].to) == p) continue;
		misaka(v, u);
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
void misaki(int u, int p) {
	for (int i = hd[u], v; i; i = e[i].nxt) {
		if ((v = e[i].to) == p) continue;
		misaki(v, u);
		rt[u] = T.merge(rt[u], rt[v], 1, MAXD);
	}
	ans[u] = T.t[rt[u]].sum ? T.t[rt[u]].mx : 0;
}
int main() {
	int n = read(), m = read();
	for (int i = 1; i < n; ++i) {
		int u = read(), v = read();
		link(u, v); link(v, u);
	}
	misaka(1, 0);
	while (m--) {
		int u = read(), v = read(), x = read();
		int g = lca(u, v);
		T.update(rt[u], 1, MAXD, x, 1);
		T.update(rt[v], 1, MAXD, x, 1);
		T.update(rt[g], 1, MAXD, x, -1);
		T.update(rt[f[g][0]], 1, MAXD, x, -1);
	}
	misaki(1, 0);
	for (int i = 1; i <= n; ++i)
		printf("%d\n", ans[i]);
	return 0;
}
```
