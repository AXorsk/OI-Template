All-in Divide&Conquer
```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read() {
	int x = 0; bool f = 0; char ch = getchar();
	while (!isdigit(ch)) f |= ch == '-', ch = getchar();
	while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}
const int MAXN = 5e2 + 6, MAXM = 1e6 + 6;
struct tQue { int x1, y1, x2, y2, k, id; } q[MAXM], t1[MAXM], t2[MAXM];
int n, m, tot, ans[MAXM];
struct Fenwick_Tree {
	int f[MAXN][MAXN];
	inline int lowbit(int x) { return x & -x; }
	inline void add(int x, int y, int v) {
		for (int i = x; i <= n; i += lowbit(i))
			for (int j = y; j <= n; j += lowbit(j))
				f[i][j] += v;
	}
	inline int ask(int x, int y) {
		int ret = 0;
		for (int i = x; i; i -= lowbit(i))
			for (int j = y; j; j -= lowbit(j))
				ret += f[i][j];
		return ret;
	}
	inline int query(int x1, int y1, int x2, int y2) {
		return ask(x2, y2) - ask(x1 - 1, y2) - ask(x2, y1 - 1) + ask(x1 - 1, y1 - 1);
	}
} fwt;
void misaka(int l, int r, int L, int R) {
	if (l > r) return;
	if (L == R) {
		for (int i = l; i <= r; ++i)
			if (q[i].id) ans[q[i].id] = L;
		return;
	}
	int cnt1 = 0, cnt2 = 0, mid = L + R >> 1;
	for (int i = l; i <= r; ++i) {
		if (!q[i].id) {
			if (q[i].k <= mid) {
				fwt.add(q[i].x2, q[i].y2, 1);
				t1[++cnt1] = q[i];
			} else t2[++cnt2] = q[i];
		} else {
			int ret = fwt.query(q[i].x1, q[i].y1, q[i].x2, q[i].y2);
			if (ret >= q[i].k) t1[++cnt1] = q[i];
			else q[i].k -= ret, t2[++cnt2] = q[i];
		}
	}
	for (int i = 1; i <= cnt1; ++i)
		q[l + i - 1] = t1[i];
	for (int i = 1; i <= cnt2; ++i)
		q[l + cnt1 + i - 1] = t2[i];
	for (int i = l; i <= l + cnt1 - 1; ++i)
		if (!q[i].id && q[i].k <= mid)
			fwt.add(q[i].x2, q[i].y2, -1);
	misaka(l, l + cnt1 - 1, L, mid);
	misaka(l + cnt1, r, mid + 1, R);
}
int main() {
	n = read(), m = read();
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			q[++tot] = {0, 0, i, j, read(), 0};
	for (int i = 1; i <= m; ++i)
		q[++tot] = {read(), read(), read(), read(), read(), i};
	misaka(1, tot, INT_MIN, INT_MAX);
	for (int i = 1; i <= m; ++i)
		printf("%d\n", ans[i]);
	return 0;
}
```
