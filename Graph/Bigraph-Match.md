Bigraph-Match

Hungarian
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 5e2 + 6;
int n, m, e, ans;
int g[MAXN][MAXN], vis[MAXN], match[MAXN];
bool misaka(int u) {
	for (int v = 1; v <= m; ++v) {
		if (vis[v] || !g[u][v]) continue;
		vis[v] = 1;
		if (!match[v] || misaka(match[v]))
			return match[v] = u, true;
	}
	return false;
}
int main() {
	scanf("%d%d%d", &n, &m, &e);
	for (int i = 1; i <= e; ++i) {
		int u, v; scanf("%d%d", &u, &v);
		g[u][v] = 1;
	}
	for (int i = 1; i <= n; ++i) {
		memset(vis, 0, sizeof vis);
		ans += misaka(i);
	}
	printf("%d\n", ans);
	return 0;
}
```

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
const int MAXN = 1e3 + 6, MAXM = 2e5 + 6, INF = 2e9;
int n, m1, m2, k, s, t, cnte = 1, hd[MAXN], cur[MAXN], dis[MAXN];
struct tEdge { int to, nxt; int cap; } e[MAXM];
inline void link(int u, int v, int w) {
	e[++cnte] = {v, hd[u], w}; hd[u] = cnte;
	e[++cnte] = {u, hd[v], 0}; hd[v] = cnte;
}
inline bool bfs() {
	memset(dis, -1, sizeof dis); dis[s] = 0;
	queue <int> q; q.emplace(s);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (int i = hd[u]; i; i = e[i].nxt) {
			int v = e[i].to;
			if (!e[i].cap) continue;
			if (!~dis[v]) {
				dis[v] = dis[u] + 1;
				q.emplace(v);
			}
		}
	}
	return ~dis[t];
}
int dfs(int u, int f) {
	if (u == t) return f;
	int now = f;
	for (int &i = cur[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if (!e[i].cap || dis[v] != dis[u] + 1) continue;
		int d = dfs(v, min(e[i].cap, now));
		if (d) {
			e[i].cap -= d;
			e[i ^ 1].cap += d;
			now -= d;
			if (!now) break;
		} else dis[v] = 0;
	}
	return f - now;
}
inline int dinic() {
	int ret = 0;
	while (bfs()) {
		memcpy(cur, hd, sizeof hd);
		ret += dfs(s, INF);
	}
	return ret;
}
int main() {
	m1 = read(), m2 = read(), k = read();
	s = 1; n = t = m1 + m2 + 2;
	for (int i = 1; i <= k; ++i) {
		int u = read(), v = read();
		link(u + 1, v + m1 + 1, 1);
	}
	for (int i = 1; i <= m1; ++i)
		link(s, i + 1, 1);
	for (int i = 1; i <= m2; ++i)
		link(i + m1 + 1, t, 1);
	printf("%d\n", dinic());
	return 0;
}
```
