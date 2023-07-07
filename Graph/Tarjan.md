Tarjan + Toposort + DP (P3387)
```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read() {
	int x = 0; bool f = 0; char ch = getchar();
	while (!isdigit(ch)) f |= ch == '-', ch = getchar();
	while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}
const int MAXN = 1e4 + 6, MAXM = 1e5 + 6;
int n, m, cnte, _cnte, top, idx;
int hd[MAXN], _hd[MAXN], stk[MAXN];
int sum[MAXN], in[MAXN], dis[MAXN];
int dfn[MAXN], low[MAXN], scc[MAXN], vis[MAXN];
struct tLnk { int from, to; } eg[MAXM];
struct tEdge { int to, nxt; } e[MAXM], _e[MAXM];
inline void link(int u, int v) {
	e[++cnte] = {v, hd[u]};
	hd[u] = cnte;
}
inline void _link(int u, int v) {
	_e[++_cnte] = {v, _hd[u]};
	_hd[u] = _cnte;
}
void tarjan(int u) {
	low[u] = dfn[u] = ++idx;
	stk[++top] = u; vis[u] = 1;
	for (int i = hd[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if (!dfn[v]) tarjan(v), low[u] = min(low[u], low[v]);
		else if (vis[v]) low[u] = min(low[u], dfn[v]);
	}
	if (dfn[u] == low[u]) {
		while (top) {
			int x = stk[top--];
			scc[x] = u; vis[x] = 0;
			if (u == x) break;
			sum[u] += sum[x];
		}
	}
}
void toposort() {
	queue <int> q;
	for (int i = 1; i <= n; ++i)
		if (scc[i] == i && !in[i]) {
			q.emplace(i);
			dis[i] = sum[i];
		}
	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (int i = _hd[u]; i; i = _e[i].nxt) {
			int v = _e[i].to;
			dis[v] = max(dis[v], dis[u] + sum[v]);
			if (!--in[v]) q.emplace(v);
		}
	}
}
int main() {
	n = read(), m = read();
	for (int i = 1; i <= n; ++i)
		sum[i] = read();
	for (int i = 1; i <= m; ++i) {
		int u = read(), v = read();
		eg[i] = {u, v}; link(u, v);
	}
	for (int i = 1; i <= n; ++i)
		if (!dfn[i]) tarjan(i);
	for (int i = 1; i <= m; ++i) {
		int u = scc[eg[i].from], v = scc[eg[i].to];
		if (u == v) continue;
		_link(u, v); ++in[v];
	}
	toposort();
	int ans = 0;
	for (int i = 1; i <= n; ++i)
		ans = max(ans, dis[i]);
	printf("%d\n", ans);
	return 0;
}
```
