AC Automaton
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e6 + 6, MAXC = 26;
int id[MAXN], ans[MAXN], tot[MAXN], unq[MAXN];
int f[MAXN], a[MAXN], m;
struct AC_Automaton {
	int ch[MAXN][MAXC], fail[MAXN], size;
	AC_Automaton() {
		memset(ch, 0, sizeof ch);
		memset(fail, 0, sizeof fail);
		memset(id, 0, sizeof id);
		memset(ans, 0, sizeof ans);
		memset(tot, 0, sizeof tot);
		memset(f, 0, sizeof f);
		memset(unq, 0, sizeof unq);
		size = 0;
	}
	inline void insert(string s, int k) {
		int u = 0;
		for (int i = 0; i < s.size(); ++i) {
			int c = s[i] - 'a';
			if (!ch[u][c]) ch[u][c] = ++size;
			u = ch[u][c];
		}
		if (id[u]) unq[k] = id[u];
		else id[u] = k;
	}
	inline void getfail() {
		int u = 0;
		queue <int> q;
		for (int i = 0; i < MAXC; ++i)
			if (ch[0][i]) {
				q.emplace(ch[0][i]);
				fail[ch[0][i]] = 0;
			}
		while (!q.empty()) {
			int u = q.front(); q.pop();
			for (int i = 0; i < MAXC; ++i) {
				int v = ch[u][i];
				if (v) fail[v] = ch[fail[u]][i], q.emplace(v);
				else ch[u][i] = ch[fail[u]][i];
			}
		}
		for (int i = 1; i <= size; ++i)
			f[fail[i]] = 1;
		for (int i = 1; i <= size; ++i)
			if (!f[i]) a[++m] = i;
	}
	inline void query(string s) {
		int u = 0;
		for (int i = 0; i < s.size(); ++i) {
			u = ch[u][s[i] - 'a'];
			++tot[u];
		}
	}
	inline void misaka() {
		for (int i = 1; i <= m; ++i) {
			int u = a[i], now = 0;
			for (int j = u; j; j = fail[j]) {
				now += tot[j];
				tot[j] = 0;
				ans[id[j]] += now;
			}
		}
	}
};
int main() {
	int n; cin >> n;
	AC_Automaton AC;
	string s, t;
	for (int i = 1; i <= n; ++i) {
		cin >> s;
		AC.insert(s, i);
	}
	AC.getfail(); cin >> t;
	AC.query(t); AC.misaka();
	for (int i = 1; i <= n; ++i) {
		int j = i;
		if (unq[i]) j = unq[i];
		cout << ans[j] << endl;
	}
	return 0;
}
```
