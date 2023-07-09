Suffix Automaton (P3804)
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 2e6 + 6, ALPHA = 30;
char s[MAXN]; ll ans, cnt[MAXN];
int n, hd[MAXN], tot, sz = 1, last = 1;
int ch[MAXN][ALPHA], len[MAXN], fail[MAXN];
struct tEdge { int to, nxt; } e[MAXN];
inline void link(int u, int v) {
	e[++tot] = {v, hd[u]};
	hd[u] = tot;
}
//================================
inline void insert(int x) {
	int u = ++sz, p = last; cnt[sz] = 1;
	len[u] = len[p] + 1; last = u;
	while (p && !ch[p][x]) ch[p][x] = u, p = fail[p];
	if (!p) fail[u] = 1;
	else {
		int q = ch[p][x];
		if (len[q] == len[p] + 1) fail[u] = q;
		else {
			int v = ++sz;
			len[v] = len[p] + 1, fail[v] = fail[q];
			memcpy(ch[v], ch[q], sizeof(ch[q]));
			fail[u] = fail[q] = v;
			while (p && ch[p][x] == q) ch[p][x] = v, p = fail[p];
		}
	}
}
//================================
void misaka(int u) {
	for (int i = hd[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		misaka(v);
		cnt[u] += cnt[v];
	}
	if (cnt[u] != 1) ans = max(ans, cnt[u] * len[u]);
}
int main() {
	scanf("%s", s + 1); n = strlen(s + 1);
	for (int i = 1; i <= n; ++i)
		insert(s[i] - 'a');
	for (int i = 2; i <= sz; ++i)
		link(fail[i], i);
	misaka(1);
	printf("%lld\n", ans);
	return 0;
}
