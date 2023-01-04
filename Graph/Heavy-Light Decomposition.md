Heavy-Light Decomposition
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
int N, M, R, P, cnte, hd[MAXN], a[MAXN];
struct tEdge { int to, nxt; } e[MAXN << 1];
int fa[MAXN], dep[MAXN], sz[MAXN], top[MAXN];
int idx, id[MAXN], rk[MAXN], wson[MAXN];
inline void link(int u, int v) {
	e[++cnte] = {v, hd[u]};
	hd[u] = cnte;
}
struct Segment_Tree {
#define lson k << 1
#define rson k << 1 | 1
#define mid (l + r >> 1)
	int tree[MAXN << 2], tag[MAXN << 2];
	inline void pushup(int k) {
		tree[k] = tree[lson] + tree[rson];
	}
	inline void pushdown(int k, int l, int r) {
		if (!tag[k]) return;
		tag[lson] = (1ll * tag[lson] + tag[k]) % P;
		tag[rson] = (1ll * tag[rson] + tag[k]) % P;
		tree[lson] = (tree[lson] + (mid - l + 1ll) * tag[k]) % P;
		tree[rson] = (tree[rson] + (1ll * r - mid) * tag[k]) % P;
		tag[k] = 0;
	}
	void build(int k, int l, int r) {
		if (l == r) return tree[k] = a[rk[l]] % P, void();
		build(lson, l, mid);
		build(rson, mid + 1, r);
		pushup(k);
	}
	void modify(int k, int l, int r, int x, int y, int v) {
		if (x <= l && y >= r) {
			tree[k] = (tree[k] + (r - l + 1ll) * v) % P;
			tag[k] = (tag[k] + v * 1ll) % P;
			return;
		}
		pushdown(k, l, r);
		if (x <= mid) modify(lson, l, mid, x, y, v);
		if (y > mid) modify(rson, mid + 1, r, x, y, v);
		pushup(k);
	}
	int query(int k, int l, int r, int x, int y) {
		if (x <= l && y >= r) return tree[k] % P;
		pushdown(k, l, r);
		int ans = 0;
		if (x <= mid) ans = (1ll * ans + query(lson, l, mid, x, y)) % P;
		if (y > mid) ans = (1ll * ans + query(rson, mid + 1, r, x, y)) % P;
		return ans;
	}
} T;
void misaka(int u, int p) {
	fa[u] = p; dep[u] = dep[p] + 1; sz[u] = 1;
	for (int i = hd[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if (v == p) continue;
		misaka(v, u);
		sz[u] += sz[v];
		if (sz[v] > sz[wson[u]]) wson[u] = v;
	}
}
void accelerator(int u, int tp) {
	top[u] = tp; id[u] = ++idx; rk[idx] = u;
	if (!wson[u]) return;
	accelerator(wson[u], tp);
	for (int i = hd[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if (v != fa[u] && v != wson[u])
			accelerator(v, v);
	}
}
inline void updateR(int u, int v, int x) {
	while (top[u] != top[v]) {
		if (dep[top[u]] < dep[top[v]]) swap(u, v);
		T.modify(1, 1, N, id[top[u]], id[u], x);
		u = fa[top[u]];
	}
	if (dep[u] > dep[v]) swap(u, v);
	T.modify(1, 1, N, id[u], id[v], x);
}
inline int queryR(int u, int v) {
	int ans = 0;
	while (top[u] != top[v]) {
		if (dep[top[u]] < dep[top[v]]) swap(u, v);
		ans = (ans + T.query(1, 1, N, id[top[u]], id[u])) % P;
		u = fa[top[u]];
	}
	if (dep[u] > dep[v]) swap(u, v);
	ans = (1ll * ans + T.query(1, 1, N, id[u], id[v])) % P;
	return ans;
}
inline void updateS(int u, int x) {
	T.modify(1, 1, N, id[u], id[u] + sz[u] - 1, x);
}
inline int queryS(int u) {
	return T.query(1, 1, N, id[u], id[u] + sz[u] - 1);
}
int main() {
	N = read(), M = read(), R = read(), P = read();
	for (int i = 1; i <= N; ++i) a[i] = read();
	for (int i = 1; i < N; ++i) {
		int u = read(), v = read();
		link(u, v); link(v, u);
	}
	misaka(R, 0);
	accelerator(R, R);
	T.build(1, 1, N);
	while (M--) {
		int op = read();
		if (op == 1) {
			int x = read(), y = read(), z = read();
			updateR(x, y, z);
		}
		if (op == 2) {
			int x = read(), y = read();
			write(queryR(x, y)); putchar('\n');
		}
		if (op == 3) {
			int x = read(), z = read();
			updateS(x, z);
		}
		if (op == 4) {
			int x = read();
			write(queryS(x)); putchar('\n');
		}
	}
	return 0;
}
```
