01_Trie (P4551)
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
int n, hd[MAXN], cnte, val[MAXN], ans;
struct tEdge { int to, nxt, wei; } e[MAXN << 1];
inline void link(int u, int v, int w) {
	e[++cnte] = {v, hd[u], w};
	hd[u] = cnte;
}
struct Trie {
	int f[MAXN * 31][2], size;
	inline void insert(int x) {
		int u = 0;
		for (int i = 1 << 30; i; i >>= 1) {
			bool d = x & i;
			if (!f[u][d]) f[u][d] = ++size;
			u = f[u][d];
		}
	}
	inline int query(int x) {
		int u = 0, ret = 0;
		for (int i = 1 << 30; i; i >>= 1) {
			bool d = x & i;
			if (f[u][d ^ 1]) ret += i, u = f[u][d ^ 1];
			else u = f[u][d];
		}
		return ret;
	}
} trie;
void misaka(int u, int p, int x) {
	val[u] = x;
	for (int i = hd[u]; i; i = e[i].nxt) {
		int v = e[i].to, w = e[i].wei;
		if (v == p) continue;
		misaka(v, u, x ^ w);
	}
}
int main() {
	n = read();
	for (int i = 1; i < n; ++i) {
		int u = read(), v = read(), w = read();
		link(u, v, w); link(v, u, w);
	}
	misaka(1, 0, 0);
	for (int i = 1; i <= n; ++i)
		trie.insert(val[i]);
	for (int i = 1; i <= n; ++i)
		ans = max(ans, trie.query(val[i]));
	printf("%d\n", ans);
	return 0;
}
```
