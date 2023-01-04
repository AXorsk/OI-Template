LCA: ST_Table
```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read() {
	int x = 0; bool f = 0; char ch = getchar();
	while (!isdigit(ch)) f |= ch == '-', ch = getchar();
	while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}
const int MAXN = 5e5 + 6;
int n, m, s, cnte, hd[MAXN], dep[MAXN], f[MAXN][21];
struct tEdge { int to, nxt; } e[MAXN << 1];
inline void link(int u, int v) {
	e[++cnte] = {v, hd[u]};
	hd[u] = cnte;
}
void misaka(int u, int p) {
	f[u][0] = p; dep[u] = dep[p] + 1;
	for (int i = hd[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if (v != p) misaka(v, u);
	}
}
inline void init() {
	for (int j = 1; j <= 20; ++j)
		for (int i = 1; i <= n; ++i)
			f[i][j] = f[f[i][j - 1]][j - 1];
}
inline int lca(int u, int v) {
	if (dep[u] < dep[v]) swap(u, v);
	for (int i = 20; i >= 0; --i)
		if (dep[f[u][i]] >= dep[v])
			u = f[u][i];
	if (u == v) return u;
	for (int i = 20; i >= 0; --i)
		if (f[u][i] != f[v][i])
			u = f[u][i], v = f[v][i];
	return f[u][0];
}
int main() {
	n = read(), m = read(), s = read();
	for (int i = 1; i < n; ++i) {
		int u = read(), v = read();
		link(u, v); link(v, u);
	}
	misaka(s, 0); init();
	while (m--) {
		int u = read(), v = read();
		printf("%d\n", lca(u, v));
	}
	return 0;
}
```
LCA: Heavy-Light Decomposition
```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read() {
	int x = 0; bool f = 0; char ch = getchar();
	while (!isdigit(ch)) f |= ch == '-', ch = getchar();
	while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}
const int MAXN = 5e5 + 6;
int n, m, s, cnte, hd[MAXN];
int dep[MAXN], fa[MAXN], sz[MAXN], top[MAXN], hson[MAXN];
struct tEdge { int to, nxt; } e[MAXN << 1];
inline void link(int u, int v) {
	e[++cnte] = {v, hd[u]};
	hd[u] = cnte;
}
void misaka(int u, int p) {
	fa[u] = p; sz[u] = 1;
	dep[u] = dep[p] + 1;
	hson[u] = -1;
	for (int i = hd[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if (v == p) continue;
		misaka(v, u);
		sz[u] += sz[v];
		if (!~hson[u] || sz[v] > sz[hson[u]]) hson[u] = v;
	}
}
void accelerator(int u, int p, int t) {
	top[u] = t;
	if (!hson[u]) return;
	accelerator(hson[u], u, t);
	for (int i = hd[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if (v == p || v == hson[u]) continue;
		accelerator(v, u, v);
	}
}
inline int lca(int u, int v) {
	while (top[u] != top[v]) {
		if (dep[top[u]] > dep[top[v]])
			u = fa[top[u]];
		else v = fa[top[v]];
	}
	return dep[u] > dep[v] ? v : u;
}
int main() {
	n = read(), m = read(), s = read();
	for (int i = 1; i < n; ++i) {
		int u = read(), v = read();
		link(u, v); link(v, u);
	}
	misaka(s, 0); accelerator(s, 0, s);
	while (m--) {
		int u = read(), v = read();
		printf("%d\n", lca(u, v));
	}
	return 0;
}
```
LCA: Tarjan
```cpp
```
LCA: Euler_(dfs)
```cpp
```
