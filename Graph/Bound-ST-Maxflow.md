Bound-ST-Maxflow (Dinic)
```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read() {
	int x = 0; bool f = 0; char ch = getchar();
	while (!isdigit(ch)) f |= ch == '-', ch = getchar();
	while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}
using ll = long long;
const int MAXN = 2e3 + 6, MAXM = 2e5 + 6, INF = 2e9;
int n, m, s, t, S, T, delta[MAXN];
int cnte = 1, hd[MAXN], cur[MAXN]; ll dis[MAXN];
struct tEdge { int to, nxt; ll cap; } e[MAXM << 1];
inline void link(int u, int v, int w) {
	e[++cnte] = {v, hd[u], w}; hd[u] = cnte;
	e[++cnte] = {u, hd[v], 0}; hd[v] = cnte;
}
inline void adde(int u, int v, int l, int r) {
	link(u, v, r - l);
	delta[u] -= l; delta[v] += l;
}
inline bool misaki() {
	memset(dis, -1, sizeof dis); dis[S] = 0;
	queue <int> q; q.emplace(S);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (int i = hd[u]; i; i = e[i].nxt) {
			int v = e[i].to;
			if (!e[i].cap || ~dis[v]) continue;
			dis[v] = dis[u] + 1; q.emplace(v);
		}
	}
	return ~dis[T];
}
ll misaka(int u, ll f) {
	if (u == T) return f;
	ll now = f;
	for (int &i = cur[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if (!e[i].cap || dis[v] != dis[u] + 1) continue;
		ll d = misaka(v, min(e[i].cap, now));
		if (d) {
			e[i].cap -= d;
			e[i ^ 1].cap += d;
			now -= d;
			if (!now) break;
		}
	}
	return f - now;
}
inline int dinic() {
	ll mxf = 0;
	while (misaki()) {
		memcpy(cur, hd, sizeof hd);
		mxf += misaka(S, INF);
	}
	return mxf;
}
inline void init() {
	s = n + m + 1, t = n + m + 2;
	S = t + 1, T = t + 2;
	memset(delta, 0, sizeof delta);
	memset(hd, 0, sizeof hd); cnte = 1;
}
int main() {
	while (~scanf("%d%d", &n, &m)) {
		init();
		for (int i = 1; i <= m; ++i) {
			int g = read();
			adde(s, i, g, INF);
		}
		for (int i = 1; i <= n; ++i) {
			int c = read(), d = read();
			adde(i + m, t, 0, d);
			while (c--) {
				int j = read() + 1, l = read(), r = read();
				adde(j, i + m, l, r);
			}
		}
		int sum = 0;
		for (int i = 1; i <= t; ++i) {
			if (delta[i] > 0) link(S, i, delta[i]), sum += delta[i];
			if (delta[i] < 0) link(i, T, -delta[i]);
		}
		link(t, s, INF);
		if (dinic() != sum) { puts("-1\n"); continue; }
		int ans = e[cnte].cap;
		e[cnte].cap = e[cnte - 1].cap = 0;
		S = s, T = t; ans += dinic();
		printf("%d\n\n", ans);
	}
	return 0;
}
```
