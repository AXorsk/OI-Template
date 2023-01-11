Ji_Segment_Tree
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
const int MAXN = 5e5 + 6;
struct Segment_Tree {
#define lson k << 1
#define rson k << 1 | 1
#define mid (l + r >> 1)
	struct tNode {
		int mx1, mx1_, mx2, cnt; ll sum;
		int add1, add1_, add2, add2_;
	} t[MAXN << 2];
	inline void pushup(int k) {
		t[k].sum = t[lson].sum + t[rson].sum;
		t[k].mx1_ = max(t[lson].mx1_, t[rson].mx1_);
		if (t[lson].mx1 == t[rson].mx1) {
			t[k].mx1 = t[lson].mx1;
			t[k].mx2 = max(t[lson].mx2, t[rson].mx2);
			t[k].cnt = t[lson].cnt + t[rson].cnt;
		} else if (t[lson].mx1 > t[rson].mx1) {
			t[k].mx1 = t[lson].mx1;
			t[k].mx2 = max(t[lson].mx2, t[rson].mx1);
			t[k].cnt = t[lson].cnt;
		} else {
			t[k].mx1 = t[rson].mx1;
			t[k].mx2 = max(t[lson].mx1, t[rson].mx2);
			t[k].cnt = t[rson].cnt;
		}
	}
	inline void upd(int k, int l, int r, int k1, int k1_, int k2, int k2_) {
		t[k].sum += 1ll * k1 * t[k].cnt + 1ll * k2 * (r - l + 1 - t[k].cnt);
		t[k].mx1_ = max(t[k].mx1_, t[k].mx1 + k1_);
		t[k].add1_ = max(t[k].add1_, t[k].add1 + k1_);
		t[k].mx1 += k1, t[k].add1 += k1;
		t[k].add2_ = max(t[k].add2_, t[k].add2 + k2_);
		if (t[k].mx2 ^ INT_MIN) t[k].mx2 += k2;
		t[k].add2 += k2;
	}
	inline void pushdown(int k, int l, int r) {
		int tmp = max(t[lson].mx1, t[rson].mx1);
		if (t[lson].mx1 == tmp) upd(lson, l, mid, t[k].add1, t[k].add1_, t[k].add2, t[k].add2_);
		else upd(lson, l, mid, t[k].add2, t[k].add2_, t[k].add2, t[k].add2_);
		if (t[rson].mx1 == tmp) upd(rson, mid + 1, r, t[k].add1, t[k].add1_, t[k].add2, t[k].add2_);
		else upd(rson, mid + 1, r, t[k].add2, t[k].add2_, t[k].add2, t[k].add2_);
		t[k].add1 = t[k].add1_ = t[k].add2 = t[k].add2_ = 0;
	}
	void build(int k, int l, int r) {
		t[k].add1 = t[k].add1_ = t[k].add2 = t[k].add2_ = 0;
		if (l == r) {
			t[k].sum = t[k].mx1_ = t[k].mx1 = read();
			t[k].mx2 = INT_MIN, t[k].cnt = 1; return;
		}
		build(lson, l, mid);
		build(rson, mid + 1, r);
		pushup(k);
	}
	void modify1(int k, int l, int r, int x, int y, int v) {
		if (x <= l && y >= r) return upd(k, l, r, v, v, v, v), void();
		pushdown(k, l, r);
		if (x <= mid) modify1(lson, l, mid, x, y, v);
		if (y > mid) modify1(rson, mid + 1, r, x, y, v);
		pushup(k);
	}
	void modify2(int k, int l, int r, int x, int y, int v) { // !
		if (v >= t[k].mx1) return;
		if (x <= l && y >= r && v > t[k].mx2) return upd(k, l, r, v - t[k].mx1, v - t[k].mx1, 0, 0), void();
		pushdown(k, l, r);
		if (x <= mid) modify2(lson, l, mid, x, y, v);
		if (y > mid) modify2(rson, mid + 1, r, x, y, v);
		pushup(k);
	}
	ll query3(int k, int l, int r, int x, int y) {
		if (x <= l && y >= r) return t[k].sum;
		pushdown(k, l, r); ll ret = 0;
		if (x <= mid) ret += query3(lson, l, mid, x, y);
		if (y > mid) ret += query3(rson, mid + 1, r, x, y);
		return ret;
	}
	int query4(int k, int l, int r, int x, int y) {
		if (x <= l && y >= r) return t[k].mx1;
		pushdown(k, l, r); int ret = INT_MIN;
		if (x <= mid) ret = max(ret, query4(lson, l, mid, x, y));
		if (y > mid) ret = max(ret, query4(rson, mid + 1, r, x, y));
		return ret;
	}
	int query5(int k, int l, int r, int x, int y) {
		if (x <= l && y >= r) return t[k].mx1_;
		pushdown(k, l, r); int ret = INT_MIN;
		if (x <= mid) ret = max(ret, query5(lson, l, mid, x, y));
		if (y > mid) ret = max(ret, query5(rson, mid + 1, r, x, y));
		return ret;
	}
#undef lson
#undef rson
#undef mid
} T;
int main() {
	freopen("data.in", "r", stdin);
	freopen("my.out", "w", stdout);
	int n = read(), m = read();
	T.build(1, 1, n);
	while (m--) {
		int op = read(), l, r, v;
		if (op == 1) {
			l = read(), r = read(), v = read();
			T.modify1(1, 1, n, l, r, v);
		} else if (op == 2) {
			l = read(), r = read(), v = read();
			T.modify2(1, 1, n, l, r, v);
		} else if (op == 3) {
			l = read(), r = read();
			write(T.query3(1, 1, n, l, r)), putchar('\n');
		} else if (op == 4) {
			l = read(), r = read();
			write(T.query4(1, 1, n, l, r)), putchar('\n');
		} else {
			l = read(), r = read();
			write(T.query5(1, 1, n, l, r)), putchar('\n');
		}
	}
	return 0;
}
```
