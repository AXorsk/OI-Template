Suffix Automaton (P3804)
```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MAXN = 2e6 + 6, ALPHA = 30;
char s[MAXN]; ll ans, sz_endpos[MAXN];
int n, hd[MAXN], tot, sz = 1, last = 1;
int ch[MAXN][ALPHA], len[MAXN], fail[MAXN];
struct tEdge { int to, nxt; } e[MAXN];
inline void link(int u, int v) {
	e[++tot] = {v, hd[u]};
	hd[u] = tot;
}
inline void insert(int x) {
	int u = ++sz, p = last; sz_endpos[sz] = 1;
	len[u] = len[p] + 1; last = u;
	while (p && !ch[p][x]) ch[p][x] = u, p = fail[p];
	if (!p) fail[u] = 1;
	else {
		int q = ch[p][x];
		if (len[q] == len[p] + 1) fail[u] = q;
		else {
			int v = ++sz;
			len[v] = len[p] + 1, fail[v] = fail[q];
			memcpy(ch[v], ch[q], sizeof ch[q]);
			fail[u] = fail[q] = v;
			while (p && ch[p][x] == q) ch[p][x] = v, p = fail[p];
		}
	}
}
void misaka(int u) {
	for (int i = hd[u], v; i; i = e[i].nxt)
		misaka(v = e[i].to), sz_endpos[u] += sz_endpos[v];
	if (sz_endpos[u] != 1) ans = max(ans, sz_endpos[u] * len[u]);
}
int main() {
	scanf("%s", s + 1); n = strlen(s + 1);
	for (int i = 1; i <= n; ++i) insert(s[i] - 'a');
	for (int i = 2; i <= sz; ++i) link(fail[i], i);
	misaka(1); printf("%lld\n", ans);
	return 0;
}
