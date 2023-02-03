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
int n, m, rt[MAXN];
struct Segment_Tree {
#define mid (l + r >> 1)
	int tot;
	struct tNode { int lc, rc, sum; } t[MAXN * 30];
	void build(int k, int l, int r) {
		if (l == r) return t[k].sum = read(), void();
		t[k].lc = ++tot; t[k].rc = ++tot;
		build(t[k].lc, l, mid);
		build(t[k].rc, mid + 1, r);
	}
	void modify(int lk, int k, int l, int r, int x, int v) {
		if (l == r) return t[k].sum = v, void();
		t[k] = t[lk];
		if (x <= mid) t[k].lc = ++tot, modify(t[lk].lc, t[k].lc, l, mid, x, v);
		else t[k].rc = ++tot, modify(t[lk].rc, t[k].rc, mid + 1, r, x, v);
	}
	int query(int k, int l, int r, int x) {
		if (l == r) return t[k].sum;
		if (x <= mid) return query(t[k].lc, l, mid, x);
		else return query(t[k].rc, mid + 1, r, x);
	}
#undef mid
} PT;
int main() {
	n = read(), m = read();
	PT.build(rt[0] = ++PT.tot, 1, n);
	for (int i = 1; i <= m; ++i) {
		int vs = read(), op = read(), x = read();
		if (op == 1) {
			int v = read();
			PT.modify(rt[vs], rt[i] = ++PT.tot, 1, n, x, v);
		} else {
			rt[i] = rt[vs];
			write(PT.query(rt[vs], 1, n, x)), putchar('\n');
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
