LiChao_Segment_Tree
```cpp
#include <bits/stdc++.h>
using namespace std;
#define lson k << 1
#define rson k << 1 | 1
#define mid (l + r >> 1)
typedef long long ll;
const int MAXN = 1e5 + 6, MAXM = 1e6 + 6;
ll a[MAXN], b[MAXN], h[MAXN], w[MAXN], f[MAXN];
int tree[MAXM << 2];
inline ll g(int x, int i) { return a[i] * x + b[i]; }
void update(int k, int l, int r, int t) {
	if (l == r) {
		if (g(l, t) < g(l, tree[k])) tree[k] = t;
		return;
	}
	if (g(mid, t) < g(mid, tree[k])) swap(t, tree[k]);
	if (g(l, t) < g(l, tree[k])) update(lson, l, mid, t);
	else if (g(r, t) < g(r, tree[k])) update(rson, mid + 1, r, t);
}
ll query(int k, int l, int r, int t) {
	ll res = g(t, tree[k]);
	if (l == r) return res;
	if (t <= mid) res = min(res, query(lson, l, mid, t));
	else res = min(res, query(rson, mid + 1, r, t));
	return res;
}
int main() {
	int n; scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		scanf("%lld", h + i);
	for (int i = 1; i <= n; ++i) {
		scanf("%lld", w + i);
		w[i] += w[i - 1];
	}
	b[0] = 1e18;
	for (int i = 1; i <= n; ++i) {
		if (i > 1) f[i] = h[i] * h[i] + w[i - 1] + query(1, 0, MAXM, h[i]);
		a[i] = -2 * h[i], b[i] = f[i] + h[i] * h[i] - w[i];
		update(1, 0, MAXM, i);
	}
	printf("%lld\n", f[n]);
	return 0;
}
```
