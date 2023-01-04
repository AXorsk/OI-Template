FHQ_Treap covers on Segment_Tree
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
const int MAXN = 5e4 + 6, INF = INT_MAX;
mt19937 rnd(20061216);
int a[MAXN], n, m;
struct FHQ_Treap {
	int size, ch[MAXN * 50][2];
	int sz[MAXN * 50], val[MAXN * 50], pri[MAXN * 50];
	inline int newnode(int v) {
		int k = ++size;
		sz[k] = 1;
		val[k] = v;
		pri[k] = rnd();
		return k;
	}
	inline void pushup(int k) {
		sz[k] = sz[ch[k][0]] + sz[ch[k][1]] + 1;
	}
	void split(int k, int v, int &x, int &y) {
		if (!k) return x = y = 0, void();
		if (v < val[k]) {
			y = k;
			split(ch[k][0], v, x, ch[k][0]);
		} else {
			x = k;
			split(ch[k][1], v, ch[k][1], y);
		}
		pushup(k);
	}
	int merge(int x, int y) {
		if (!x || !y) return x | y;
		if (pri[x] < pri[y]) {
			ch[x][1] = merge(ch[x][1], y);
			pushup(x); return x;
		} else {
			ch[y][0] = merge(x, ch[y][0]);
			pushup(y); return y;
		}
	}
	int query(int k, int x) {
		if (sz[ch[k][0]] + 1 == x) return val[k];
		if (x <= sz[ch[k][0]]) return query(ch[k][0], x);
		else return query(ch[k][1], x - sz[ch[k][0]] - 1);
	}
	inline void insert(int &root, int v) {
		int x, y;
		split(root, v, x, y);
		root = merge(merge(x, newnode(v)), y);
	}
	inline void remove(int &root, int v) {
		int x, y, z;
		split(root, v, x, z);
		split(x, v - 1, x, y);
		root = merge(merge(x, ch[y][0]), merge(ch[y][1], z));
	}
	inline int order_of_key(int &root, int v) {
		int x, y, ans;
		split(root, v - 1, x, y);
		ans = sz[x]; // -INF
		root = merge(x, y);
		return ans;
	}
	inline int find_by_order(int &root, int k) {
		return query(root, k + 1); //-INF
	}
	inline int pre(int &root, int v) {
		int x, y, z, ans;
		split(root, v - 1, x, y); z = x;
		while (ch[z][1]) z = ch[z][1];
		ans = val[z];
		root = merge(x, y);
		return ans;
	}
	inline int nxt(int &root, int v) {
		int x, y, z, ans;
		split(root, v, x, y); z = y;
		while (ch[z][0]) z = ch[z][0];
		ans = val[z];
		root = merge(x, y);
		return ans;
	}
} BT;
struct Segment_Tree1 {
#define lson k << 1
#define rson k << 1 | 1
#define mid (l + r >> 1)
	int root[MAXN << 2];
	void build(int k, int l, int r) {
		BT.insert(root[k], -INF);
		BT.insert(root[k], INF);
		for (int i = l; i <= r; ++i)
			BT.insert(root[k], a[i]);
		if (l == r) return;
		build(lson, l, mid);
		build(rson, mid + 1, r);
	}
	void update(int k, int l, int r, int p, int v) {
		BT.remove(root[k], a[p]);
		BT.insert(root[k], v);
		if (l == r) return;
		if (p <= mid) update(lson, l, mid, p, v);
		else update(rson, mid + 1, r, p, v);
	}
	int order_of_key(int k, int l, int r, int x, int y, int v) {
		if (x <= l && y >= r) return BT.order_of_key(root[k], v);
		int ans = 0;
		if (x <= mid) ans += order_of_key(lson, l, mid, x, y, v);
		if (y > mid) ans += order_of_key(rson, mid + 1, r, x, y, v);
		if (x <= mid && y > mid) --ans; // #
		return ans;
	}
	int find_by_order(int l, int r, int x, int y, int v) {
		int ans = -1;
		while (l <= r) {
			int ret = order_of_key(1, 1, n, x, y, mid);
			if (ret <= v) ans = mid, l = mid + 1;
			else r = mid - 1;
		}
		return ans;
	}
	int pre(int k, int l, int r, int x, int y, int v) {
		if (x <= l && y >= r) return BT.pre(root[k], v);
		int ans = -INF;
		if (x <= mid) ans = max(ans, pre(lson, l, mid, x, y, v));
		if (y > mid) ans = max(ans, pre(rson, mid + 1, r, x, y, v));
		return ans;
	}
	int nxt(int k, int l, int r, int x, int y, int v) {
		if (x <= l && y >= r) return BT.nxt(root[k], v);
		int ans = INF;
		if (x <= mid) ans = min(ans, nxt(lson, l, mid, x, y, v));
		if (y > mid) ans = min(ans, nxt(rson, mid + 1, r, x, y, v));
		return ans;
	}
} ST;
struct tNode { int minv, maxv; };
struct Segment_Tree2 {
#define lson k << 1
#define rson k << 1 | 1
#define mid (l + r >> 1)
	tNode tree[MAXN << 2];
	inline void pushup(int k) {
		tree[k].maxv = max(tree[lson].maxv, tree[rson].maxv);
		tree[k].minv = min(tree[lson].minv, tree[rson].minv);
	}
	void build(int k, int l, int r) {
		if (l == r) return tree[k] = {a[l], a[l]}, void();
		build(lson, l, mid);
		build(rson, mid + 1, r);
		pushup(k);
	}
	void update(int k, int l, int r, int p, int v) {
		if (l == r) return tree[k] = {v, v}, void();
		if (p <= mid) update(lson, l, mid, p, v);
		else update(rson, mid + 1, r, p, v);
		pushup(k);
	}
	tNode query(int k, int l, int r, int x, int y) {
		if (x <= l && y >= r) return tree[k];
		tNode ans = {INT_MAX, INT_MIN};
		if (x <= mid) {
			tNode ret1 = query(lson, l, mid, x, y);
			ans.maxv = max(ans.maxv, ret1.maxv);
			ans.minv = min(ans.minv, ret1.minv);
		}
		if (y > mid) {
			tNode ret2 = query(rson, mid + 1, r, x, y);
			ans.maxv = max(ans.maxv, ret2.maxv);
			ans.minv = min(ans.minv, ret2.minv);
		}
		return ans;
	}
} RMQ;
int main() {
	n = read(), m = read();
	for (int i = 1; i <= n; ++i)
		a[i] = read();
	RMQ.build(1, 1, n);
	ST.build(1, 1, n);
	while (m--) {
		int opt = read();
		if (opt == 1) {
			int l = read(), r = read(), v = read();
			write(ST.order_of_key(1, 1, n, l, r, v)); putchar('\n');
		}
		if (opt == 2) {
			int l = read(), r = read(), v = read();
			tNode now = RMQ.query(1, 1, n, l, r);
			write(ST.find_by_order(now.minv, now.maxv, l, r, v)); putchar('\n');
		}
		if (opt == 3) {
			int p = read(), v = read();
			ST.update(1, 1, n, p, v);
			RMQ.update(1, 1, n, p, v);
			a[p] = v;
		}
		if (opt == 4) {
			int l = read(), r = read(), v = read();
			write(ST.pre(1, 1, n, l, r, v)); putchar('\n');
		}
		if (opt == 5) {
			int l = read(), r = read(), v = read();
			write(ST.nxt(1, 1, n, l, r, v)); putchar('\n');
		}
	}
	return 0;
}
```
