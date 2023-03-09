Point Divide&Conquer 1:
```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read() {
	int x = 0; bool f = 0; char ch = getchar();
	while (!isdigit(ch)) f |= ch == '-', ch = getchar();
	while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}
const int MAXN = 4e4 + 6;
int n, k, root, cnte, cntd, ans;
int mxp[MAXN], vis[MAXN], sz[MAXN], hd[MAXN], dis[MAXN];
struct tEdge { int to, nxt, wei; } e[MAXN << 1];
inline void link(int u, int v, int w) {
	e[++cnte] = {v, hd[u], w};
	hd[u] = cnte;
}
void updsize(int u, int p) {
	sz[u] = 1;
	for (int i = hd[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if (vis[v] || v == p) continue;
		updsize(v, u);
		sz[u] += sz[v];
	}
}
void getroot(int u, int p, int n) {
	mxp[u] = 0;
	for (int i = hd[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if (vis[v] || v == p) continue;
		getroot(v, u, n);
		mxp[u] = max(mxp[u], sz[v]);
	}
	mxp[u] = max(mxp[u], n - sz[u]);
	if (mxp[u] < mxp[root]) root = u;
}
int calc(int u, int d) {
	cntd = 0; getdis(u, d, 0);
	sort(dis + 1, dis + cntd + 1);
	int sum = 0;
	for (int l = 1, r = cntd; ; ++l) {
		while (r && dis[l] + dis[r] > k) --r;
		if (r < l) break;
		sum += r - l;
	}
	return sum;
}
void solve(int u) {
	ans += calc(u, 0); vis[u] = 1;
	for (int i = hd[u]; i; i = e[i].nxt) {
		int v = e[i].to, w = e[i].wei;
		if (vis[v]) continue;
		ans -= calc(v, w);
		updsize(v, u); mxp[root = 0] = INT_MAX;
		getroot(v, 0, sz[v]); solve(root);
	}
}
int main() {
	n = read();
	for (int i = 1; i < n; ++i) {
		int u = read(), v = read(), w = read();
		link(u, v, w); link(v, u, w);
	}
	k = read();
	updsize(1, 0); mxp[root = 0] = INT_MAX;
	getroot(1, 0, n); solve(root);
	printf("%d\n", ans);
	return 0;
}
```
Point Divide&Conquer 2:
```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read() {
	int x = 0; bool f = 0; char ch = getchar();
	while (!isdigit(ch)) f |= ch == '-', ch = getchar();
	while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}
const int MAXN = 1e4 + 6, INF = 1e8 + 6;
int n, m, cnte, cntd, root;
int hd[MAXN], sz[MAXN], mxp[MAXN], vis[MAXN];
int q[MAXN], f[MAXN], dic[INF], dis[MAXN], tf[MAXN];
struct tEdge { int to, nxt, wei; } e[MAXN << 1];
inline void link(int u, int v, int w) {
	e[++cnte] = {v, hd[u], w};
	hd[u] = cnte;
}
void updsize(int u, int p) {
	sz[u] = 1;
	for (int i = hd[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if (vis[v] || v == p) continue;
		updsize(v, u);
		sz[u] += sz[v];
	}
}
void getroot(int u, int p, int n) {
	mxp[u] = 0;
	for (int i = hd[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if (vis[v] || v == p) continue;
		getroot(v, u, n);
		mxp[u] = max(mxp[u], sz[v]);
	}
	mxp[u] = max(mxp[u], n - sz[u]);
	if (mxp[u] < mxp[root]) root = u;
}
void getdis(int u, int d, int p) {
	dis[++cntd] = d;
	for (int i = hd[u]; i; i = e[i].nxt) {
		int v = e[i].to, w = e[i].wei;
		if (v == p || vis[v]) continue;
		getdis(v, d + w, u);
	}
}
void calc(int u) {
	int tot = 0;
	for (int i = hd[u]; i; i = e[i].nxt) {
		int v = e[i].to, w = e[i].wei;
		if (vis[v]) continue;
		cntd = 0; getdis(v, w, u);
		for (int j = cntd; j; --j)
			for (int k = 1; k <= m; ++k) {
				if (q[k] < dis[j]) continue;
				f[k] |= dic[q[k] - dis[j]];
			}
		for (int j = cntd; j; --j)
			tf[++tot] = dis[j], dic[dis[j]] = 1;
	}
	for (int i = 1; i <= tot; ++i)
		dic[tf[i]] = 0;
}
void solve(int u) {
	vis[u] = dic[0] = 1; calc(u);
	for (int i = hd[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if (vis[v]) continue;
		updsize(v, u); mxp[root = 0] = INT_MAX;
		getroot(v, 0, sz[v]); solve(root);
	}
}
int main() {
	n = read(), m = read();
	for (int i = 1; i < n; ++i) {
		int u = read(), v = read(), d = read();
		link(u, v, d); link(v, u, d);
	}
	for (int i = 1; i <= m; ++i)
		q[i] = read();
	updsize(1, 0); mxp[root = 0] = INT_MAX;
	getroot(1, 0, n); solve(root);
	for (int i = 1; i <= m; ++i) {
		if (f[i]) puts("AYE");
		else puts("NAY");
	}
	return 0;
}
```
