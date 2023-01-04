Persistent_Segment_Tree
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
int n, m, root[MAXN];
struct tNode { int lson, rson, val; };
struct Segment_Tree {
#define mid (l + r >> 1)
	tNode tree[MAXN * 100]; int size;
	inline void build(int k, int l, int r) {
		if (l == r) return tree[k].val = read(), void();
		tree[k].lson = ++size; tree[k].rson = ++size;
		build(tree[k].lson, l, mid);
		build(tree[k].rson, mid + 1, r);
	}
	inline void modify(int lk, int k, int l, int r, int x, int v) {
		if (l == r) return tree[k].val = v, void();
		tree[k] = tree[lk];
		if (x <= mid) tree[k].lson = ++size, modify(tree[lk].lson, tree[k].lson, l, mid, x, v);
		else tree[k].rson = ++size, modify(tree[lk].rson, tree[k].rson, mid + 1, r, x, v);
	}
	inline int query(int k, int l, int r, int x) {
		if (l == r) return tree[k].val;
		if (x <= mid) return query(tree[k].lson, l, mid, x);
		else return query(tree[k].rson, mid + 1, r, x);
	}
} T;
int main() {
	n = read(), m = read();
	T.build(root[0] = ++T.size, 1, n);
	for (int i = 1; i <= m; ++i) {
		int vs = read(), op = read(), x = read();
		if (op == 1) {
			int v = read();
			T.modify(root[vs], root[i] = ++T.size, 1, n, x, v);
		} else {
			root[i] = root[vs];
			write(T.query(root[vs], 1, n, x)), putchar('\n');
		}
	}
	return 0;
}
```
"nth_element"
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
const int MAXN = 2e5 + 6;
int n, m, q, a[MAXN], b[MAXN], root[MAXN];
struct tNode { int lson, rson, val; };
struct Segment_Tree {
#define mid (l + r >> 1)
	tNode tree[MAXN * 50]; int size;
	inline void pushup(int k) {
		tree[k].val = tree[tree[k].lson].val + tree[tree[k].rson].val;
	}
	inline int build(int l, int r) {
		int k = ++size;
		if (l == r) return k;
		tree[k].lson = build(l, mid);
		tree[k].rson = build(mid + 1, r);
		return pushup(k), k;
	}
	inline int modify(int p, int l, int r, int x) {
		int q = ++size; tree[q] = tree[p];
		if (l == r) return ++tree[q].val, q;
		if (x <= mid) tree[q].lson = modify(tree[p].lson, l, mid, x);
		else tree[q].rson = modify(tree[p].rson, mid + 1, r, x);
		return pushup(q), q;
	}
	inline int query(int p, int q, int l, int r, int k) {
		if (l == r) return l;
		int lsum = tree[tree[q].lson].val - tree[tree[p].lson].val;
		if (k <= lsum) return query(tree[p].lson, tree[q].lson, l, mid, k);
		else return query(tree[p].rson, tree[q].rson, mid + 1, r, k - lsum);
	}
} T;
int main() {
	n = read(), q = read();
	for (int i = 1; i <= n; ++i) a[i] = b[i] = read();
	sort(b + 1, b + n + 1);
	m = unique(b + 1, b + n + 1) - (b + 1);
	root[0] = T.build(1, m);
	for (int i = 1; i <= n; ++i) {
		int x = lower_bound(b + 1, b + m + 1, a[i]) - b;
		root[i] = T.modify(root[i - 1], 1, m, x);
	}
	while (q--) {
		int l = read(), r = read(), k = read();
		write(b[T.query(root[l - 1], root[r], 1, m, k)]); putchar('\n');
	}
	return 0;
}
```
