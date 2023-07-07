Mincost-Maxflow [Dinic] (P3381)
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
void write(ll x) {
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) write(x / 10);
	putchar(x % 10 ^ 48);
}
const int MAXN = 5e3 + 6, MAXM = 5e4 + 6, INF = 2e9;
int n, m, s, t, all, cnte = 1;
int hd[MAXN], cur[MAXN], vis[MAXN], dvis[MAXN];
ll dis[MAXN], max_flow, min_cost;
struct tNode { int to, nxt; ll cap, cost; } e[MAXM << 1];
inline void link(int u, int v, ll w, ll c) {
	e[++cnte] = {v, hd[u], w, c}; hd[u] = cnte;
	e[++cnte] = {u, hd[v], 0, -c}; hd[v] = cnte;
}
bool SPFA() {
	fill(dis, dis + all + 1, INF); dis[s] = 0;
	memset(vis, 0, sizeof vis); vis[s] = 1;
	queue <int> q; q.emplace(s);
	while (!q.empty()) {
		int u = q.front(); q.pop(); vis[u] = 0;
		for (int i = hd[u]; i; i = e[i].nxt) {
			int v = e[i].to;
			if (!e[i].cap) continue;
			if (dis[u] + e[i].cost < dis[v]) {
				dis[v] = dis[u] + e[i].cost;
				if (!vis[v]) q.emplace(v), vis[v] = 1;
			}
		}
	}
	return dis[t] != INF;
}
ll misaka(int u, ll flow) {
	if (u == t) return flow;
	ll now = flow; dvis[u] = 1;
	// dvis: prevent from running in "0" circle
	for (int &i = cur[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if (dvis[v] || !e[i].cap || dis[v] != dis[u] + e[i].cost) continue;
		ll d = misaka(v, min(e[i].cap, now));
		if (d) {
			min_cost += d * e[i].cost;
			e[i].cap -= d; e[i ^ 1].cap += d;
			now -= d; if (!now) break;
		}
	}
	return flow - now;
}
void mcmf() {
	max_flow = min_cost = 0;
	while (SPFA()) {
		memset(dvis, 0, sizeof dvis);
		memcpy(cur, hd, sizeof hd);
		max_flow += misaka(s, INF);
	}
}
int main() {
	n = read(), m = read(), s = read(), t = read(); all = n;
	for (int i = 1; i <= m; ++i) {
		int u = read(), v = read(), w = read(), c = read();
		link(u, v, w, c);
	}
	mcmf();
	write(max_flow); putchar(' ');
	write(min_cost); putchar('\n');
	return 0;
}
```
