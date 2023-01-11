Split->Segment_Tree
```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
inline int read() {
	int x = 0; bool f = 0; char ch = getchar();
	while (!isdigit(ch)) f |= ch == '-', ch = getchar();
	while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}
void write(ll x) {
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) write(x / 10);
	putchar(x % 10 ^ 48);
}
const int MAXN = 2e5 + 6;
int idx = 1, rt[MAXN];
struct Segment_Tree {
#define mid (l + r >> 1)
	int tot, cntb, bin[MAXN * 50];
	struct tNode { int lc, rc; ll sz; } t[MAXN * 50];
	inline int newnode() { return cntb ? bin[cntb--] : ++tot;}
	inline void erase(int k) { bin[++cntb] = k; t[k] = {0, 0, 0}; }
	void modify(int &k, int l, int r, int x, int v) {
		if (!k) k = newnode(); t[k].sz += v;
		if (l == r) return;
		if (x <= mid) modify(t[k].lc, l, mid, x, v);
		else modify(t[k].rc, mid + 1, r, x, v);
	}
	ll query(int k, int l, int r, int x, int y) {
		if (x <= l && y >= r) return t[k].sz;
		ll ret = 0;
		if (x <= mid) ret += query(t[k].lc, l, mid, x, y);
		if (y > mid) ret += query(t[k].rc, mid + 1, r, x, y);
		return ret;
	}
	int kth(int k, int l, int r, int x) {
		if (l == r) return l;
		if (t[t[k].lc].sz >= x) return kth(t[k].lc, l, mid, x);
		else return kth(t[k].rc, mid + 1, r, x - t[t[k].lc].sz);
	}
	int merge(int p, int q) {
		if (!p || !q) return p | q;
		t[p].sz += t[q].sz;
		t[p].lc = merge(t[p].lc, t[q].lc);
		t[p].rc = merge(t[p].rc, t[q].rc);
		return erase(q), p;
	}
	void split(int &p, int &q, ll x) {
		if (!p) return; q = newnode();
		ll v = t[t[p].lc].sz;
		if (x > v) split(t[p].rc, t[q].rc, x - v);
		else swap(t[p].rc, t[q].rc);
		if (x < v) split(t[p].lc, t[q].lc, x);
		t[q].sz = t[p].sz - x; t[p].sz = x;
	}
#undef mid
} T;
int main() {
	int n = read(), m = read();
	for (int i = 1; i <= n; ++i)
		T.modify(rt[1], 1, n, i, read());
	while (m--) {
		int op = read();
		if (op == 0) {
			int p = read(), x = read(), y = read();
			ll x1 = T.query(rt[p], 1, n, 1, y);
			ll x2 = T.query(rt[p], 1, n, x, y);
			int tmp = 0;
			T.split(rt[p], rt[++idx], x1 - x2);
			T.split(rt[idx], tmp, x2);
			rt[p] = T.merge(rt[p], tmp);
		} else if (op == 1) {
			int p = read(), t = read();
			rt[p] = T.merge(rt[p], rt[t]);
		} else if (op == 2) {
			int p = read(), x = read(), q = read();
			T.modify(rt[p], 1, n, q, x);
		} else if (op == 3) {
			int p = read(), x = read(), y = read();
			write(T.query(rt[p], 1, n, x, y)), putchar('\n');
		} else {
			int p = read(), k = read();
			if (T.t[rt[p]].sz < k) puts("-1");
			else write(T.kth(rt[p], 1, n, k)), putchar('\n');
		}
	}
	return 0;
}
```
