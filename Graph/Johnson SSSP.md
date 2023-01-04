Johnson (SSSP)
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
using pii = pair <ll, int>;
const int MAXN = 3e3 + 6, MAXM = 1e4 + 6, INF = 1e9;
int n, m, cnte, hd[MAXN], inq[MAXN], vis[MAXN];
ll h[MAXN], dis[MAXN];
struct tEdge { int to, nxt, wei; } e[MAXM];
inline void link(int u, int v, int w) {
	e[++cnte] = {v, hd[u], w};
	hd[u] = cnte;
}
bool SPFA(int s) {
	queue <int> q; q.emplace(s);
	memset(h, 0x3f, sizeof h); h[s] = 0;
	memset(vis, 0, sizeof vis); vis[s] = 1;
	while (!q.empty()) {
		int u = q.front(); q.pop(); vis[u] = 0;
		for (int i = hd[u]; ~i; i = e[i].nxt) {
			int v = e[i].to;
			if (h[v] > h[u] + e[i].wei) {
				h[v] = h[u] + e[i].wei;
				if (vis[v]) continue;
				vis[v] = 1; q.emplace(v);
				if (++inq[v] == n + 1) return false;
			}
		}
	}
	return true;
}
void dijkstra(int s) {
	priority_queue <pii> pq; pq.emplace(make_pair(0, s));
	for (int i = 1; i <= n; ++i) dis[i] = INF;
	memset(vis, 0, sizeof vis); dis[s] = 0;
	while (!pq.empty()) {
		int u = pq.top().second; pq.pop();
		if (vis[u]) continue; vis[u] = 1;
		for (int i = hd[u]; ~i; i = e[i].nxt) {
			int v = e[i].to;
			if (dis[v] > dis[u] + e[i].wei) {
				dis[v] = dis[u] + e[i].wei;
				if (vis[v]) continue;
				pq.emplace(make_pair(-dis[v], v));
			}
		}
	}
}
int main() {
	n = read(), m = read();
	memset(hd, -1, sizeof hd);
	for (int i = 1; i <= m; ++i) {
		int u = read(), v = read(), w = read();
		link(u, v, w);
	}
	for (int i = 1; i <= n; ++i) 
		link(0, i, 0);
	if (!SPFA(0)) return puts("-1"), 0;
	for (int u = 1; u <= n; ++u)
		for (int i = hd[u]; ~i; i = e[i].nxt) {
			int v = e[i].to;
			e[i].wei += h[u] - h[v];
		}
	for (int i = 1; i <= n; ++i) {
		dijkstra(i); ll ans = 0;
		for (int j = 1; j <= n; ++j) {
			if (dis[j] == INF) ans += 1ll * j * INF;
			else ans += 1ll * j * (dis[j] + h[j] - h[i]);
		}
		printf("%lld\n", ans);
	}
	return 0;
}
```
