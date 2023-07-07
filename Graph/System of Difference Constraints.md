System of Difference Constraints (P5960)
```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read() {
	int x = 0; bool f = 0; char ch = getchar();
	while (!isdigit(ch)) f |= ch == '-', ch = getchar();
	while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}
const int MAXN = 5e3 + 6, MAXM = 5e3 + 6;
int n, m, cnte, hd[MAXN], vis[MAXN], dis[MAXN], cnt[MAXN];
struct tEdge { int to, nxt, wei; } e[MAXM + MAXN];
inline void link(int u, int v, int w) {
	e[++cnte] = {v, hd[u], w};
	hd[u] = cnte;
}
inline bool SPFA(int s) {
	queue <int> q; q.emplace(s);
	memset(cnt, 0, sizeof cnt);
	memset(vis, 0, sizeof vis); vis[s] = 1;
	memset(dis, 0x3f, sizeof dis); dis[s] = 0;
	while (!q.empty()) {
		int u = q.front(); q.pop(); vis[u] = 0;
		for (int i = hd[u]; ~i; i = e[i].nxt) {
			int v = e[i].to, w = e[i].wei;
			if (dis[v] > dis[u] + w) {
				dis[v] = dis[u] + w;
				if (vis[v]) continue;
				vis[v] = 1; q.emplace(v);
				if (++cnt[v] >= n + 1)
					return false;
			}
		}
	}
	return true;
}
int main() {
	memset(hd, -1, sizeof hd);
	n = read(), m = read();
	// x_i - x_j <= w
	while (m--) {
		int u = read(), v = read(), w = read();
		link(v, u, w);
	}
	for (int i = 1; i <= n; ++i)
		link(0, i, 0);
	if (!SPFA(0)) puts("NO");
	else {
		for (int i = 1; i <= n; ++i)
			printf("%d ", dis[i]);
		putchar('\n');
	}
	return 0;
}
