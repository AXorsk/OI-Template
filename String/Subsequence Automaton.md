Subsequence Automaton
```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read() {
	int x = 0; bool f = 0; char ch = getchar();
	while (!isdigit(ch)) f |= ch == '-', ch = getchar();
	while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}
const int MAXN = 1e5 + 6, MAXL = 1e6 + 6;
int a[MAXN], b[MAXL], rt[MAXN];
struct tNode { int lson, rson, val; };
struct Segment_Tree {
#define mid (l + r >> 1)
	tNode tree[MAXN * 20]; int size;
	inline int build(int l, int r) {
		int k = ++size;
		if (l == r) return tree[k].val = MAXN, k;
		tree[k].lson = build(l, mid);
		tree[k].rson = build(mid + 1, r);
		return k;
	}
	inline int modify(int p, int l, int r, int x, int v) {
		int q = ++size; tree[q] = tree[p];
		if (l == r) return tree[q].val = v, q;
		if (x <= mid) tree[q].lson = modify(tree[p].lson, l, mid, x, v);
		else tree[q].rson = modify(tree[p].rson, mid + 1, r, x, v);
		return q;
	}
	inline int query(int k, int l, int r, int x) {
		if (l == r) return tree[k].val;
		if (x <= mid) return query(tree[k].lson, l, mid, x);
		else return query(tree[k].rson, mid + 1, r, x);
	}
} PT;
int main() {
	int type = read(), n = read(), q = read(), m = read();
	for (int i = 1; i <= n; ++i) a[i] = read();
	rt[n] = PT.build(1, m);
	for (int i = n - 1; ~i; --i)
		rt[i] = PT.modify(rt[i + 1], 1, m, a[i + 1], i + 1);
	while (q--) {
		int t = read();
		for (int i = 1; i <= t; ++i) b[i] = read();
		int last = 0, flag = 0;
		for (int i = 1; i <= t; ++i) {
			last = PT.query(rt[last], 1, m, b[i]);
			if (last == MAXN) { puts("No"); flag = 1; break; }
		}
		if (!flag) puts("Yes");
	}
	return 0;
}
```
