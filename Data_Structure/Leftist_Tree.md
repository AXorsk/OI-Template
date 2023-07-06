Leftist_Tree [Mergeable_Heap] (P3377)
```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read() {
	int x = 0; bool f = 0; char ch = getchar();
	while (!isdigit(ch)) f |= ch == '-', ch = getchar();
	while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}
const int MAXN = 1e5 + 6;
int n, m, a[MAXN], vis[MAXN], dis[MAXN];
int lson[MAXN], rson[MAXN], fa[MAXN];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
int merge(int x, int y) {
	if (!x || !y) return x | y;
	if (a[y] < a[x]) swap(x, y);
	rson[x] = merge(rson[x], y);
	if (dis[lson[x]] < dis[rson[x]]) swap(lson[x], rson[x]);
	dis[x] = dis[rson[x]] + 1;
	return x;
}
int main() {
	// Leftist_Tree: lson[] & rson[]
	// Union_Find_Set: fa[]
	n = read(), m = read();
	for (int i = 1; i <= n; ++i)
		a[i] = read(), fa[i] = i;
	while (m--) {
		int op = read();
		if (op == 1) {
			int x = read(), y = read();
			if (vis[x] || vis[y]) continue;
			int fx = find(x), fy = find(y);
			if (fx != fy) fa[fx] = fa[fy] = merge(fx, fy);
		} else {
			int x = read();
			if (vis[x]) { puts("-1"); continue; }
			int fx = find(x);
			printf("%d\n", a[fx]); vis[fx] = 1;
			fa[lson[fx]] = fa[rson[fx]] = fa[fx] = merge(lson[fx], rson[fx]);
			// !!!important: fa[x] also needs setting to the new "scc" root although it has been removed.
			// 'cause Path-Compression, exist some vertexs which could be connected to the "fx"!
		}
	}
	return 0;
}
```
