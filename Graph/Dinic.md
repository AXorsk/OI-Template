Dinic (Maxflow)
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
inline int read() {
	int x = 0; bool f = 0; char ch = getchar();
	while (!isdigit(ch)) f |= ch == '-', ch = getchar();
	while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}
const int MAXN = 5e2 + 6, MAXM = 1e5 + 6, INF = 2e9;
int n, m, s, t, cnte = 1, hd[MAXN], cur[MAXN];
ll dis[MAXN];
struct tEdge { int to, nxt; ll cap; } e[MAXM];
inline void link(int u, int v, int w) {
	e[++cnte] = {v, hd[u], w};
	hd[u] = cnte;
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
ll dfs(int u, ll f) {
	if (u == t) return f;
	ll now = f;
	for (int &i = cur[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if (!e[i].cap || dis[v] != dis[u] + 1) continue;
		ll d = dfs(v, min(e[i].cap, now));
		if (d) {
			e[i].cap -= d;
			e[i ^ 1].cap += d;
			now -= d;
			if (!now) break;
		} else dis[v] = 0;
	}
	return f - now;
}
inline ll dinic() {
	ll ret = 0;
	while (bfs()) {
		memcpy(cur, hd, sizeof hd);
		ret += dfs(s, INF);
	}
	return ret;
}
int main() {
	n = read(), m = read(), s = read(), t = read();
	for (int i = 1; i <= m; ++i) {
		int u = read(), v = read(), w = read();
		link(u, v, w); link(v, u, 0);
	}
	printf("%lld\n", dinic());
	return 0;
}
```
Dinic (MCMF)
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
inline int read() {
	int x = 0; bool f = 0; char ch = getchar();
	while (!isdigit(ch)) f |= ch == '-', ch = getchar();
	while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}
const int MAXN = 5e3 + 6, MAXM = 1e5 + 6, INF = INT_MAX;
int n, m, s, t, cnte = 1, hd[MAXN], cur[MAXN], vis[MAXN], dvis[MAXN];
ll dis[MAXN], ans, sum;
struct tEdge { int to, nxt; ll cap, cost; } e[MAXM];
inline void link(int u, int v, int w, int c) {
	e[++cnte] = {v, hd[u], w, c};
	hd[u] = cnte;
}
inline bool SPFA() {
	memcpy(cur, hd, sizeof hd);
	fill(dis, dis + n + 1, INF); dis[s] = 0;
	memset(vis, 0, sizeof vis); vis[s] = 1;
	queue <int> q; q.emplace(s);
	while (!q.empty()) {
		int u = q.front(); q.pop(); vis[u] = 0;
		for (int i = hd[u]; i; i = e[i].nxt) {
			int v = e[i].to;
			if (!e[i].cap) continue;
			if (dis[v] > dis[u] + e[i].cost) {
				dis[v] = dis[u] + e[i].cost;
				if (!vis[v]) q.emplace(v), vis[v] = 1;
			}
		}
	}
	return dis[t] != INF;
}
ll dfs(int u, ll f) {
	if (u == t) return f;
	ll now = f; dvis[u] = 1;
	for (int &i = cur[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if (dvis[v] || !e[i].cap || dis[v] != dis[u] + e[i].cost) continue;
		ll d = dfs(v, min(e[i].cap, now));
		if (d) {
			sum += d * e[i].cost;
			e[i].cap -= d;
			e[i ^ 1].cap += d;
			now -= d;
			if (!now) break;
		}
	}
	return f - now;
}
inline ll mcmf() {
	ll ret = 0;
	while (SPFA()) {
		memset(dvis, 0, sizeof dvis);
		ret += dfs(s, INF);
	}
	return ret;
}
int main() {
	n = read(), m = read(), s = read(), t = read();
	for (int i = 1; i <= m; ++i) {
		int u = read(), v = read(), w = read(), c = read();
		link(u, v, w, c); link(v, u, 0, -c);
	}
	ans = mcmf();
	printf("%lld %lld\n", ans, sum);
	return 0;
}
```
