Persistent_UFS (P3402)
```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read() {
	int x = 0; bool f = 0; char ch = getchar();
	while (!isdigit(ch)) f |= ch == '-', ch = getchar();
	while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}
const int MAXN = 2e5 + 6;
#define mid (l + r >> 1)
int fa[MAXN * 30], sz[MAXN * 30], lson[MAXN * 30], rson[MAXN * 30];
int n, m, ed[MAXN], tot;
void build(int &k, int l, int r) {
	k = ++tot;
	if (l == r) return fa[k] = l, sz[k] = 1, void();
	build(lson[k], l, mid);
	build(rson[k], mid + 1, r);
}
void update(int &k, int _k, int l, int r, int x, int f) {
	k = ++tot;
	if (l == r) return fa[k] = f, sz[k] = sz[_k], void();
	lson[k] = lson[_k]; rson[k] = rson[_k];
	if (x <= mid) update(lson[k], lson[_k], l, mid, x, f);
	else update(rson[k], rson[_k], mid + 1, r, x, f);
}
int query(int k, int l, int r, int x) {
	if (l == r) return k;
	if (x <= mid) return query(lson[k], l, mid, x);
	else return query(rson[k], mid + 1, r, x);
}
void add(int k, int l, int r, int x, int v) {
	if (l == r) { sz[k] += v; return; }
	if (x <= mid) add(lson[k], l, mid, x, v);
	else add(rson[k], mid + 1, r, x, v);
}
int find(int ed, int x) {
	int id = query(ed, 1, n, x);
	if (x == fa[id]) return id;
	return find(ed, fa[id]);
}
#undef mid
int main() {
	n = read(), m = read();
	build(ed[0], 1, n);
	for (int i = 1; i <= m; ++i) {
		int op = read();
		if (op == 1) {
			ed[i] = ed[i - 1];
			int x = read(), y = read();
			int fx = find(ed[i], x);
			int fy = find(ed[i], y);
			// fx, fy is their id on the Tree
			// fa[fx], fa[fy] is their real value
			if (fa[fx] == fa[fy]) continue;
			if (sz[fx] > sz[fy]) swap(fx, fy);
			update(ed[i], ed[i - 1], 1, n, fa[fx], fa[fy]);
			add(ed[i], 1, n, fa[fy], sz[fx]);
		} else if (op == 2) {
			int k = read();
			ed[i] = ed[k];
		} else {
			ed[i] = ed[i - 1];
			int x = read(), y = read();
			int fx = find(ed[i], x);
			int fy = find(ed[i], y);
			puts(fa[fx] == fa[fy] ? "1" : "0");
		}
	}
	return 0;
}
```
