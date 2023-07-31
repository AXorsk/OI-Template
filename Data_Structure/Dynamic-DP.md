Dynamic-DP

Normal [Segment_Tree for __chain__] (P4719) 

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
int n, m, idx, cnte;
int a[MAXN], fa[MAXN], sz[MAXN], dep[MAXN], wson[MAXN];
int top[MAXN], id[MAXN], dfn[MAXN], ed[MAXN], f[MAXN][2], hd[MAXN];
// f[u][0]: non-choose u, choose/non-choose v
// f[u][1]: choose u, non-choose v
// g[u][0]: choose/non-choose v(light)
// g[u][1]: choose u'a, non-choose v(light)
/* Transfer: f
f[i][0] = g[i][0] + max(f[wson][0], f[wson][1]);
f[i][1] = g[i][1] + f[wson][0];
*/
/* Matrix: G
G: | g[i][0]   g[i][0] |   ---in fact--->   | f[i][0]   f[i][0] |
   | g[i][1]      -INF |                    | f[i][1]      -INF |
*/
struct tEdge { int to, nxt; } e[MAXN << 1];
inline void link(int u, int v) {
	e[++cnte] = {v, hd[u]};
	hd[u] = cnte;
}
struct Matrix {
	int mat[2][2];
	Matrix() { memset(mat, -0x3f, sizeof mat); }
	inline Matrix operator * (const Matrix &o) const {
		Matrix ans;
		for (int i = 0; i < 2; ++i)
			for (int j = 0; j < 2; ++j)
				for (int k = 0; k < 2; ++k)
					ans.mat[i][j] = max(ans.mat[i][j], mat[i][k] + o.mat[k][j]);
		return ans;
	}
} G[MAXN];
struct Segtree {
#define lson k << 1
#define rson k << 1 | 1
#define mid (l + r >> 1)
	Matrix tree[MAXN << 2];
	inline void pushup(int k) {
		tree[k] = tree[lson] * tree[rson];
	}
	void build(int k, int l, int r) {
		if (l == r) return tree[k] = G[dfn[l]], void();
		build(lson, l, mid);
		build(rson, mid + 1, r);
		pushup(k);
	}
	void modify(int k, int l, int r, int x) {
		if (l == r) return tree[k] = G[dfn[x]], void();
		if (x <= mid) modify(lson, l, mid, x);
		else modify(rson, mid + 1, r, x);
		pushup(k);
	}
	Matrix query(int k, int l, int r, int x, int y) {
		if (x <= l && y >= r) return tree[k];
		if (y <= mid) return query(lson, l, mid, x, y);
		else if (x > mid) return query(rson, mid + 1, r, x, y);
		else return query(lson, l, mid, x, y) * query(rson, mid + 1, r, x, y);
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
// at the begining we still have to use f[]
// to calculate the G and later we don't need f[]
// G[i].mat[0][0/1] -> f[i][0], G[i].mat[1][0] -> f[i][1]
void accelerator(int u, int tp) {
	id[u] = ++idx; dfn[idx] = u;
	top[u] = tp; ed[tp] = max(ed[tp], idx);
	// initialize the f, G
	f[u][0] = 0; f[u][1] = a[u];
	G[u].mat[0][0] = G[u].mat[0][1] = 0;
	G[u].mat[1][0] = a[u];
	if (wson[u]) {
		accelerator(wson[u], tp);
		// update the f
		f[u][0] += max(f[wson[u]][0], f[wson[u]][1]);
		f[u][1] += f[wson[u]][0];
	}
	for (int i = hd[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if (v == fa[u] || v == wson[u]) continue;
		accelerator(v, v);
		// update the f
		f[u][0] += max(f[v][0], f[v][1]);
		f[u][1] += f[v][0];
		// update the G 
		// only on the father of a light-vertex needs updating
		G[u].mat[0][0] += max(f[v][0], f[v][1]);
		G[u].mat[0][1] = G[u].mat[0][0];
		G[u].mat[1][0] += f[v][0];
	}
}
void update(int u, int w) {
	G[u].mat[1][0] += w - a[u]; a[u] = w;
	while (u) {
		// here is different from the normal chain-update
		Matrix last = T.query(1, 1, n, id[top[u]], ed[top[u]]);
		T.modify(1, 1, n, id[u]);
		Matrix now = T.query(1, 1, n, id[top[u]], ed[top[u]]);
		u = fa[top[u]];
		// here we need to update the real value of the chain-top-vertex
		// so we must use a ed[] to record the end of the chain
		G[u].mat[0][0] += max(now.mat[0][0], now.mat[1][0]) - max(last.mat[0][0], last.mat[1][0]);
		G[u].mat[0][1] = G[u].mat[0][0];
		G[u].mat[1][0] += now.mat[0][0] - last.mat[0][0];
	}
}
int main() {
	n = read(), m = read();
	for (int i = 1; i <= n; ++i) a[i] = read();
	for (int i = 1; i < n; ++i) {
		int u = read(), v = read();
		link(u, v); link(v, u);
	}
	misaka(1, 0);
	accelerator(1, 1);
	T.build(1, 1, n);
	while (m--) {
		int u = read(), w = read();
		update(u, w);
		Matrix ans = T.query(1, 1, n, id[1], ed[1]);
		write(max(ans.mat[0][0], ans.mat[1][0])); putchar('\n');
	}
	return 0;
}
```

Globally Balanced Binary Tree [non-splay_BST for __chain__] (P4751) 

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
const int MAXN = 1e6 + 6;
int n, m, idx, cnte, last;
int a[MAXN], fa[MAXN], sz[MAXN], dep[MAXN], wson[MAXN];
int top[MAXN], id[MAXN], dfn[MAXN], ed[MAXN], f[MAXN][2], hd[MAXN];
int wt[MAXN], rt[MAXN]; // only chain-top has the value of rt[]
struct tEdge { int to, nxt; } e[MAXN << 1];
inline void link(int u, int v) {
	e[++cnte] = {v, hd[u]};
	hd[u] = cnte;
}
struct Matrix {
	int mat[2][2];
	Matrix() { mat[0][0] = mat[0][1] = mat[1][0] = mat[1][1] = -1e7; }
	inline Matrix operator * (const Matrix &o) const {
		Matrix ans;
		for (int i = 0; i < 2; ++i)
			for (int j = 0; j < 2; ++j)
				for (int k = 0; k < 2; ++k)
					ans.mat[i][j] = max(ans.mat[i][j], mat[i][k] + o.mat[k][j]);
		return ans;
	}
} G[MAXN];
// this BST is disable to rotate or splay
// it only use its balanced-height to make sure of O(logn)
struct Balanced_Tree { // node it by dfn !
	int lson[MAXN], rson[MAXN], mo[MAXN];
	Matrix t[MAXN];
	inline void pushup(int k) {
		if (lson[k]) t[k] = t[lson[k]] * G[dfn[k]];
		else t[k] = G[dfn[k]];
		if (rson[k]) t[k] = t[k] * t[rson[k]];
	}
	int build(int l, int r) {
		if (l > r) return 0;
		if (l == r) return t[l] = G[dfn[l]], l;
		int swt = 0;
		for (int i = l; i <= r; ++i) swt += wt[dfn[i]];
		for (int i = l, x = wt[dfn[l]]; i <= r; x += wt[dfn[++i]])
			if ((x << 1) >= swt) {
				lson[i] = build(l, i - 1);
				rson[i] = build(i + 1, r);
				mo[lson[i]] = mo[rson[i]] = i;
				return pushup(i), i;
			}
	}
	void modify(int k, int rt) {
		while (k != rt) pushup(k), k = mo[k];
		pushup(rt);
	}
} BST;
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
	id[u] = ++idx; dfn[idx] = u;
	top[u] = tp; ed[tp] = max(ed[tp], idx);
	f[u][0] = 0; f[u][1] = a[u];
	G[u].mat[0][0] = G[u].mat[0][1] = 0;
	G[u].mat[1][0] = a[u];
	if (wson[u]) {
		accelerator(wson[u], tp);
		f[u][0] += max(f[wson[u]][0], f[wson[u]][1]);
		f[u][1] += f[wson[u]][0];
	}
	wt[u] = 1;
	for (int i = hd[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if (v == fa[u] || v == wson[u]) continue;
		accelerator(v, v); wt[u] += sz[v];
		f[u][0] += max(f[v][0], f[v][1]);
		f[u][1] += f[v][0];
		G[u].mat[0][0] += max(f[v][0], f[v][1]);
		G[u].mat[0][1] = G[u].mat[0][0];
		G[u].mat[1][0] += f[v][0];
	}
}
void update(int u, int w) {
	G[u].mat[1][0] += w - a[u]; a[u] = w;
	while (u) {
		Matrix last = BST.t[rt[top[u]]];
		BST.modify(id[u], rt[top[u]]);
		Matrix now = BST.t[rt[top[u]]];
		u = fa[top[u]];
		G[u].mat[0][0] += max(now.mat[0][0], now.mat[1][0]) - max(last.mat[0][0], last.mat[1][0]);
		G[u].mat[0][1] = G[u].mat[0][0];
		G[u].mat[1][0] += now.mat[0][0] - last.mat[0][0];
	}
}
int main() {
	n = read(), m = read();
	for (int i = 1; i <= n; ++i) a[i] = read();
	for (int i = 1; i < n; ++i) {
		int u = read(), v = read();
		link(u, v); link(v, u);
	}
	misaka(1, 0);
	accelerator(1, 1);
	for (int i = 1; i <= n; ++i) {
		if (top[i] ^ i) continue;
		rt[i] = BST.build(id[i], ed[i]);
	}
	while (m--) {
		int u = read() ^ last, w = read();
		update(u, w); Matrix ans = BST.t[rt[1]];
		write(last = max(ans.mat[0][0], ans.mat[1][0])); putchar('\n');
	}
	return 0;
}
```

