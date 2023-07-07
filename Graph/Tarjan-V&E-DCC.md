Point Biconnected Component [Tarjan-V-DCC] (P8435)
```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read() {
	int x = 0; bool f = 0; char ch = getchar();
	while (!isdigit(ch)) f |= ch == '-', ch = getchar();
	while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}
const int MAXN = 5e5 + 6, MAXM = 2e6 + 6;
int n, m, cnte = 1, totscc, tim, top, hd[MAXN];
int root, low[MAXN], dfn[MAXN], stk[MAXN];
// int cut[MAXN];
struct tEdge { int from, to, nxt; } e[MAXM << 1];
vector <int> ans[MAXN];
inline void link(int u, int v) {
	e[++cnte] = {u, v, hd[u]};
	hd[u] = cnte;
}
void tarjan(int u, int fa) {
	low[u] = dfn[u] = ++tim;
	stk[++top] = u;
	if (u == root && !hd[u]) {
		ans[++totscc].emplace_back(u);
		return;
	}
	// int subtree = 0;
	for (int i = hd[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if (!dfn[v]) {
			tarjan(v, u), low[u] = min(low[u], low[v]);
			if (low[v] >= dfn[u]) {
				// ++subtree;
				// if (u != root || subtree > 1)
				// 	cut[u] = 1;
				++totscc; int k;
				do {
					k = stk[top--];
					ans[totscc].emplace_back(k);
				} while (k != v);
				ans[totscc].emplace_back(u);
			}
		} else if (v != fa) low[u] = min(low[u], dfn[v]);
	}
}
int main() {
	n = read(), m = read();
	for (int i = 1; i <= m; ++i) {
		int u = read(), v = read();
		if (u == v) continue;
		link(u, v); link(v, u);
	}
	for (int i = 1; i <= n; ++i)
		if (!dfn[i]) tarjan(root = i, -1);
	printf("%d\n", totscc);
	for (int i = 1; i <= totscc; ++i) {
		printf("%d ", ans[i].size());
		for (auto v : ans[i])
			printf("%d ", v);
		putchar('\n');
	}
	return 0;
}
```

Edge Biconnected Component [Tarjan-E-DCC] (P8436)
```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read() {
	int x = 0; bool f = 0; char ch = getchar();
	while (!isdigit(ch)) f |= ch == '-', ch = getchar();
	while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}
const int MAXN = 5e5 + 6, MAXM = 2e6 + 6;
int n, m, cnte = 1, totscc, tim, hd[MAXN], in[MAXN];
int low[MAXN], dfn[MAXN], scc[MAXN], bridge[MAXM << 1];
struct tEdge { int from, to, nxt; } e[MAXM << 1];
vector <int> ans[MAXN];
inline void link(int u, int v) {
	e[++cnte] = {u, v, hd[u]};
	hd[u] = cnte;
}
void tarjan(int u, int fa) {
	low[u] = dfn[u] = ++tim;
	for (int i = hd[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if (!dfn[v]) {
			tarjan(v, u), low[u] = min(low[u], low[v]);
			if (dfn[u] < low[v]) bridge[i] = bridge[i ^ 1] = 1;
		} else if (v != fa) low[u] = min(low[u], dfn[v]);
	}
}
void misaka(int u) {
	scc[u] = totscc;
	for (int i = hd[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if (scc[v] || bridge[i]) continue;
		misaka(v);
	}
}
int main() {
	n = read(), m = read();
	for (int i = 1; i <= m; ++i) {
		int u = read(), v = read();
		link(u, v); link(v, u);
	}
	for (int i = 1; i <= n; ++i)
		if (!dfn[i]) tarjan(i, -1);
	for (int i = 1; i <= n; ++i) {
		if (scc[i]) continue;
		++totscc; misaka(i);
	}
	printf("%d\n", totscc);
	for (int i = 1; i <= n; ++i)
		ans[scc[i]].emplace_back(i);
	for (int i = 1; i <= totscc; ++i) {
		printf("%d ", ans[i].size());
		for (auto v : ans[i])
			printf("%d ", v);
		putchar('\n');
	}
	return 0;
}
```
