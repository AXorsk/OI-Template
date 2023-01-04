Segment_Tree
```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
inline ll read() {
	ll x = 0; bool f = 0; char ch = getchar();
	while (!isdigit(ch)) f |= ch == '-', ch = getchar();
	while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}
void write(ll x) {
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) write(x / 10);
	putchar(x % 10 ^ 48);
}
const int MAXN = 1e5 + 6;
struct Segment_Tree {
#define lson k << 1
#define rson k << 1 | 1
#define mid (l + r >> 1)
	ll tree[MAXN << 2], tag[MAXN << 2];
	inline void pushup(int k) {
		tree[k] = tree[lson] + tree[rson];
	}
	inline void pushdown(int k, int l, int r) {
		if (!tag[k]) return;
		tag[lson] += tag[k]; tag[rson] += tag[k];
		tree[lson] += tag[k] * (mid - l + 1);
		tree[rson] += tag[k] * (r - mid);
		tag[k] = 0;
	}
	void build(int k, int l, int r) {
		if (l == r) return tree[k] = read(), void();
		build(lson, l, mid);
		build(rson, mid + 1, r);
		pushup(k);
	}
	void modify(int k, int l, int r, int x, int y, int v) {
		if (x <= l && y >= r) {
			tree[k] += (r - l + 1) * v;
			tag[k] += v; return;
		}
		pushdown(k, l, r);
		if (x <= mid) modify(lson, l, mid, x, y, v);
		if (y > mid) modify(rson, mid + 1, r, x, y, v);
		pushup(k);
	}
	ll query(int k, int l, int r, int x, int y) {
		if (x <= l && y >= r) return tree[k];
		pushdown(k, l, r); ll ans = 0;
		if (x <= mid) ans += query(lson, l, mid, x, y);
		if (y > mid) ans += query(rson, mid + 1, r, x, y);
		return ans;
	}
} T;
int main() {
	int n = read(), m = read();
	T.build(1, 1, n);
	while (m--) {
		int op = read();
		if (op == 1) {
			int x = read(), y = read(), v = read();
			T.modify(1, 1, n, x, y, v);
		} else {
			int x = read(), y = read();
			write(T.query(1, 1, n, x, y)); putchar('\n');
		}
	}
	return 0;
}
```
