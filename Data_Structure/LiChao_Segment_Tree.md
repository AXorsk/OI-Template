LiChao_Segment_Tree (P4097)
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
using pid = pair <int, double>;
const int MAXN = 1e5 + 6, MOD1 = 39989, MOD2 = 1e9;
const double EPS = 1e-6;
int n, lans;
struct tLine { double k, b; } a[MAXN];
inline double f(int id, int x) { return a[id].k * x + a[id].b; }
inline int cmp(double x, double y) {
	if (x - y > EPS) return 1;
	if (y - x > EPS) return -1;
	return 0;
}
inline void add(int x0, int y0, int x1, int y1) {
	double k, b;
	if (x0 == x1) k = 0, b = max(y0, y1);
	else k = 1.0 * (y1 - y0) / (x1 - x0), b = y0 - k * x0;
	a[++n] = {k, b};
}
inline void chkmax(pid &x, pid y) {
	int b = cmp(y.second, x.second);
	if (b == 1 || (!b && y.first < x.first)) x = y;
}
struct Segment_Tree { // LiChao
#define lson k << 1
#define rson k << 1 | 1
#define mid (l + r >> 1)
	int t[MOD1 << 2];
	inline void upd(int k, int l, int r, int u) {
		int &v = t[k];
		if (cmp(f(u, mid), f(v, mid)) == 1) swap(u, v);
		int L = cmp(f(u, l), f(v, l)), R = cmp(f(u, r), f(v, r));
		if (L == 1 || (!L && u < v)) upd(lson, l, mid, u);
		if (R == 1 || (!R && u < v)) upd(rson, mid + 1, r, u);
	}
	inline void modify(int k, int l, int r, int x, int y, int id) {
		if (x <= l && y >= r) return upd(k, l, r, id);
		if (x <= mid) modify(lson, l, mid, x, y, id);
		if (y > mid) modify(rson, mid + 1, r, x, y, id);
	}
	pid query(int k, int l, int r, int x) {
		pid ret = {0, 0.0};
		if (x < l || x > r) return ret;
		chkmax(ret, {t[k], f(t[k], x)});
		if (l == r) return ret;
		if (x <= mid) chkmax(ret, query(lson, l, mid, x));
		else chkmax(ret, query(rson, mid + 1, r, x));
		return ret;
	}
#undef lson
#undef rson
#undef mid
} T;
int main() {
	int q = read();
	while (q--) {
		int op = read();
		if (op == 1) {
			int x0 = (read() + lans - 1) % MOD1 + 1;
			int y0 = (read() + lans - 1) % MOD2 + 1;
			int x1 = (read() + lans - 1) % MOD1 + 1;
			int y1 = (read() + lans - 1) % MOD2 + 1;
			if (x0 > x1) swap(x0, x1), swap(y0, y1);
			add(x0, y0, x1, y1);
			T.modify(1, 1, MOD1, x0, x1, n);
		} else {
			int x = (read() + lans - 1) % MOD1 + 1;
			write(lans = T.query(1, 1, MOD1, x).first), putchar('\n');
		}
	}
	return 0;
}
```
