Min-Steiner-Tree (P6192)

```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read() {
	int x = 0; bool f = 0; char ch = getchar();
	while (!isdigit(ch)) f |= ch == '-', ch = getchar();
	while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}
const int MAXN = 1e2 + 6, MAXM = 5e2 + 6, MAXK = 11;
int n, m, k, p[MAXN], hd[MAXN], tot, dp[MAXN][1 << MAXK];
struct tEdge { int to, nxt, w; } e[MAXM << 1];
queue <int> q; bool vis[MAXN];
inline void link(int u, int v, int w) {
	e[++tot] = {v, hd[u], w};
	hd[u] = tot;
}
inline void SPFA(int s) {
	while (!q.empty()) {
		int u = q.front(); q.pop();
		vis[u] = 0;
		for (int i = hd[u]; i; i = e[i].nxt) {
			int v = e[i].to;
			if (dp[v][s] > dp[u][s] + e[i].w) {
				dp[v][s] = dp[u][s] + e[i].w;
				if (vis[v]) continue;
				q.emplace(v); vis[v] = 1;
			}
		}
	}
}
int main() {
	n = read(), m = read(), k = read();
	for (int i = 1; i <= m; ++i) {
		int u = read(), v = read(), w = read();
		link(u, v, w); link(v, u, w);
	}
	memset(dp, 0x3f, sizeof dp);
	for (int i = 1; i <= k; ++i) {
		p[i] = read();
		dp[p[i]][1 << i - 1] = 0;
	}
	for (int s = 1; s <= (1 << k) - 1; ++s) {
		for (int i = 1; i <= n; ++i) {
			for (int t = s & s - 1; t; t = t - 1 & s)
				dp[i][s] = min(dp[i][s], dp[i][t] + dp[i][s ^ t]);
			if (dp[i][s] < 0x3f3f3f3f) q.push(i), vis[i] = 1;
		}
		SPFA(s);
	}
	printf("%d\n", dp[p[1]][(1 << k) - 1]);
	return 0;
}
```

