Maxflow (Dinic)
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
const int MAXN = 5e2 + 6, MAXM = 5e3 + 6, INF = 2e9;
int n, m, s, t, cnte = 1, hd[MAXN], cur[MAXN]; ll dis[MAXN];
struct tEdge { int to, nxt; ll cap; } e[MAXM << 1];
inline void link(int u, int v, int w) {
	e[++cnte] = {v, hd[u], w}; hd[u] = cnte;
	e[++cnte] = {u, hd[v], 0}; hd[v] = cnte;
}
inline bool misaki() {
	memset(dis, -1, sizeof dis); dis[s] = 0;
	queue <int> q; q.emplace(s);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (int i = hd[u]; i; i = e[i].nxt) {
			int v = e[i].to;
			if (!e[i].cap || ~dis[v]) continue;
			dis[v] = dis[u] + 1; q.emplace(v);
		}
	}
	return ~dis[t];
}
ll misaka(int u, ll f) {
	if (u == t) return f;
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
inline ll dinic() {
	ll ret = 0;
	while (misaki()) {
		memcpy(cur, hd, sizeof hd);
		ret += misaka(s, INF);
	}
	return ret;
}
int main() {
	n = read(), m = read(), s = read(), t = read();
	for (int i = 1; i <= m; ++i) {
		int u = read(), v = read(), w = read();
		link(u, v, w);
	}
	printf("%lld\n", dinic());
	return 0;
}
```
