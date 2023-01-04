2-SAT
```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read() {
	int x = 0; bool f = 0; char ch = getchar();
	while (!isdigit(ch)) f |= ch == '-', ch = getchar();
	while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}
const int MAXN = 2e6 + 6, MAXM = 2e6 + 6;
int n, m, cnte, totscc, tim, top, hd[MAXN];
int low[MAXN], dfn[MAXN], vis[MAXN], stk[MAXN], scc[MAXN];
struct tEdge { int to, nxt; } e[MAXM];
inline void link(int u, int v) {
	e[++cnte] = {v, hd[u]};
	hd[u] = cnte;
}
void tarjan(int u) {
	low[u] = dfn[u] = ++tim;
	stk[++top] = u; vis[u] = 1;
	for (int i = hd[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if (!dfn[v]) tarjan(v), low[u] = min(low[u], low[v]);
		else if (vis[v]) low[u] = min(low[u], dfn[v]);
	}
	if (low[u] == dfn[u]) {
		++totscc;
		while (top) {
			int x = stk[top--];
			scc[x] = totscc; vis[x] = 0;
			if (x == u) break;
		}
	}
}
int main() {
	n = read(), m = read();
	// set up the 2-SAT graph
	for (int i = 1; i <= m; ++i) {
		int a = read(), va = read(), b = read(), vb = read();
		// bit operation shorten the code-length;
		// i stands for x, i + n stands for !x;
		link(a + n * (va & 1), b + n * (vb ^ 1));
		link(b + n * (vb & 1), a + n * (va ^ 1));
	}
	// use tarjan find scc;
	for (int i = 1; i <= (n << 1); ++i)
		if (!dfn[i]) tarjan(i);
	// check if x but must satisfy !x, obviously this situation is wrong;
	for (int i = 1; i <= n; ++i)
		if (scc[i] == scc[i + n])
			return puts("IMPOSSIBLE"), 0;
	puts("POSSIBLE");
	// tarjan has marked each of the scc a number;
	// so just compare the scc-number to consider the relation between x and !x;
	// we order the first scc-bool is true;
	for (int i = 1; i <= n; ++i)
		printf("%d ", scc[i] < scc[i + n]);
	putchar('\n');
	return 0;
}
