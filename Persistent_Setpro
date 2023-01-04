Persistent_Setpro
```cpp
#include <bits/stdc++.h>
using namespace std;
#define mid (l + r >> 1)
const int MAXN = 2e5 + 6;
int fa[MAXN * 30], dep[MAXN * 30], lson[MAXN * 30], rson[MAXN * 30];
int n, m, ed[MAXN], tot;
inline int read() {
	int x = 0; bool f = 0; char ch = getchar();
	while (!isdigit(ch)) f |= ch == '-', ch = getchar();
	while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}
void build(int &rt, int l, int r) {
	rt = ++tot;
	if (l == r) {
		fa[rt] = l;
		dep[rt] = 1;
		return;
	}
	build(lson[rt], l, mid);
	build(rson[rt], mid + 1, r);
}
void update(int &rt, int last, int l, int r, int p, int f) {
	rt = ++tot;
	if (l == r) {
		fa[rt] = f;
		dep[rt] = dep[last];
		return;
	}
	lson[rt] = lson[last];
	rson[rt] = rson[last];
	if (p <= mid) update(lson[rt], lson[last], l, mid, p, f);
	else update(rson[rt], rson[last], mid + 1, r, p, f);
}
int query(int rt, int l, int r, int p) {
	if (l == r) return rt;
	if (p <= mid) return query(lson[rt], l, mid, p);
	else return query(rson[rt], mid + 1, r, p);
}
void add(int rt, int l, int r, int p, int v) {
	if (l == r) { dep[rt] += v; return; }
	if (p <= mid) add(lson[rt], l, mid, p, v);
	else add(rson[rt], mid + 1, r, p, v);
}
int find(int ed, int x) {
	int f = query(ed, 1, n, x);
	if (x == fa[f]) return f;
	return find(ed, fa[f]);
}
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
			if (fa[fx] == fa[fy]) continue;
			if (dep[fx] > dep[fy]) swap(fx, fy);
			update(ed[i], ed[i - 1], 1, n, fa[fx], fa[fy]);
			add(ed[i], 1, n, fa[fy], dep[fx]);
		} else if (op == 2) {
			int k = read();
			ed[i] = ed[k];
		} else {
			ed[i] = ed[i - 1];
			int x = read(), y = read();
			int fx = find(ed[i], x);
			int fy = find(ed[i], y);
			if (fa[fx] == fa[fy]) puts("1");
			else puts("0");
		}
	}
}
```
