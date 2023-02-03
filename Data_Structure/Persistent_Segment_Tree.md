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
	if (x < 0) putchar('-');
	if (x > 9) write(x / 10);
	putchar(x % 10 ^ 48);
}
const int MAXN = 2e5 + 6;
int n, m, k, a[MAXN], b[MAXN], rt[MAXN];
struct Segment_Tree {
#define mid (l + r >> 1)
	int tot;
	struct tNode { int lc, rc, sum; } t[MAXN * 20];
	inline void pushup(int k) { t[k].sum = t[t[k].lc].sum + t[t[k].rc].sum; }
	int modify(int p, int l, int r, int x) {
		int q = ++tot; t[q] = t[p];
		if (l == r) return ++t[q].sum, q;
		if (x <= mid) t[q].lc = modify(t[p].lc, l, mid, x);
		else t[q].rc = modify(t[p].rc, mid + 1, r, x);
		return pushup(q), q;
	}
	int query(int p, int q, int l, int r, int x) {
		if (l == r) return l;
		int lsum = t[t[q].lc].sum - t[t[p].lc].sum;
		if (lsum >= x) return query(t[p].lc, t[q].lc, l, mid, x);
		else return query(t[p].rc, t[q].rc, mid + 1, r, x - lsum);
	}
#undef mid
} PT;
int main() {
	n = read(), m = read();
	for (int i = 1; i <= n; ++i)
		b[i] = a[i] = read();
	sort(b + 1, b + n + 1);
	k = unique(b + 1, b + n + 1) - (b + 1);
	for (int i = 1; i <= n; ++i) {
		a[i] = lower_bound(b + 1, b + k + 1, a[i]) - b;
		rt[i] = PT.modify(rt[i - 1], 1, k, a[i]);
	}
	while (m--) {
		int l = read(), r = read(), x = read();
		write(b[PT.query(rt[l - 1], rt[r], 1, k, x)]); putchar('\n');
	}
	return 0;
}
```
