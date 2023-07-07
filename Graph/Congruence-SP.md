Congruence-SP (P2371)
```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MAXN = 5e5 + 6, MAXM = 6e6 + 6;
int N, a[20], cnte, hd[MAXN], vis[MAXN];
ll L, R, dis[MAXN];
struct tEdge { int to, nxt, wei; } e[MAXM];
inline void link(int u, int v, int w) {
	e[++cnte] = {v, hd[u], w};
	hd[u] = cnte;
}
void dijkstra(int s) {
	priority_queue <pair <int, int>> pq;
	pq.emplace(make_pair(0, s));
	memset(vis, 0, sizeof vis);
	for (int i = 1; i <= 5e5; ++i)
		dis[i] = 1e18;
	dis[s] = 0;
	while (!pq.empty()) {
		int u = pq.top().second; pq.pop();
		vis[u] = 1;
		for (int i = hd[u]; ~i; i = e[i].nxt) {
			int v = e[i].to, w = e[i].wei;
			if (dis[v] > dis[u] + w) {
				dis[v] = dis[u] + w;
				if (vis[v]) continue;
				pq.emplace(make_pair(-dis[v], v));
			}
		}
	}
}
int main() {
	scanf("%d%lld%lld", &N, &L, &R); --L;
	for (int i = 1; i <= N; ++i)
		scanf("%d", a + i);
	sort(a + 1, a + N + 1);
	memset(hd, -1, sizeof hd);
	for (int i = 0; i < a[1]; ++i)
		for (int j = 2; j <= N; ++j)
			link(i, (i + a[j]) % a[1], a[j]);
	dijkstra(0);
	ll ans = 0;
	for (int i = 0; i < a[1]; ++i) {
		if (dis[i] <= R) ans += (R - dis[i]) / a[1] + 1;
		if (dis[i] <= L) ans -= (L - dis[i]) / a[1] + 1;
	}
	printf("%lld\n", ans);
	return 0;
}
```
