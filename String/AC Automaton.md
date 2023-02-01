AC Automaton
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e6 + 6, ALP = 26;
int f[MAXN], a[MAXN], m; char s[MAXN << 1];
int id[MAXN], ans[MAXN], cnt[MAXN], unq[MAXN];
struct AC_Automaton {
	int ch[MAXN][ALP], fail[MAXN], tot;
	AC_Automaton() {
		memset(ch, 0, sizeof ch);
		memset(fail, 0, sizeof fail);
		tot = 0;
	}
	inline void insert(char *s, int k) {
		int u = 0, n = strlen(s + 1);
		for (int i = 1; i <= n; ++i) {
			int c = s[i] - 'a';
			if (!ch[u][c]) ch[u][c] = ++tot;
			u = ch[u][c];
		}
		if (id[u]) unq[k] = id[u];
		else id[u] = k;
	}
	inline void get_fail() {
		queue <int> q;
		for (int i = 0; i < ALP; ++i)
			if (ch[0][i]) {
				q.emplace(ch[0][i]);
				fail[ch[0][i]] = 0;
			}
		while (!q.empty()) {
			int u = q.front(); q.pop();
			for (int i = 0; i < ALP; ++i) {
				int v = ch[u][i];
				if (!v) ch[u][i] = ch[fail[u]][i];
				else fail[v] = ch[fail[u]][i], q.emplace(v);
			}
		}
		for (int i = 1; i <= tot; ++i) f[fail[i]] = 1;
		for (int i = 1; i <= tot; ++i) if (!f[i]) a[++m] = i;
	}
	inline void query(char *s) {
		int u = 0, n = strlen(s + 1);
		for (int i = 1; i <= n; ++i) {
			u = ch[u][s[i] - 'a'];
			++cnt[u];
		}
	}
	inline void misaka() {
		for (int i = 1; i <= m; ++i) {
			int u = a[i], now = 0;
			for (int j = u; j; j = fail[j]) {
				now += cnt[j];
				cnt[j] = 0;
				ans[id[j]] += now;
			}
		}
	}
} ACM;
int main() {
	int n; scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%s", s + 1);
		ACM.insert(s, i);
	}
	ACM.get_fail(); scanf("%s", s + 1);
	ACM.query(s); ACM.misaka();
	for (int i = 1; i <= n; ++i) {
		int j = i;
		if (unq[i]) j = unq[i];
		printf("%d\n", ans[j]);
	}
	return 0;
}
```
