AC Automaton (P3796)
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e6 + 6, MAXC = 26;
int ans[MAXN], id[MAXN];
char dic[200][80], t[MAXN];
struct AC_Automaton {
	int ch[MAXN][MAXC], fail[MAXN], size;
	AC_Automaton() {
		memset(ch, 0, sizeof ch);
		memset(fail, 0, sizeof fail);
		memset(id, 0, sizeof id);
		memset(ans, 0, sizeof ans);
		size = 0;
	}
	inline void insert(char s[], int k) {
		int u = 0;
		for (int i = 1; s[i]; ++i) {
			int c = s[i] - 'a';
			if (!ch[u][c]) ch[u][c] = ++size;
			u = ch[u][c];
		}
		id[u] = k;
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
	}
	inline void query(char s[]) {
		int u = 0, res = 0;
		for (int i = 1; s[i]; ++i) {
			u = ch[u][s[i] - 'a'];
			for (int j = u; j; j = fail[j])
				++ans[id[j]];
		}
	}
};
int main() {
	int n; scanf("%d", &n);
	while (n) {
		AC_Automaton AC;
		for (int i = 1; i <= n; ++i) {
			scanf("%s", dic[i] + 1);
			AC.insert(dic[i], i);
		}
		AC.getfail();
		scanf("%s", t + 1);
		AC.query(t);
		int mx = 0;
		for (int i = 1; i <= n; ++i)
			mx = max(mx, ans[i]);
		printf("%d\n", mx);
		for (int i = 1; i <= n; ++i)
			if (ans[i] == mx)
				puts(dic[i] + 1);
		scanf("%d", &n);
	}
	return 0;
}
```
