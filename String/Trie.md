Trie (P8306)
```cpp
#include <bits/stdc++.h>
using namespace std;
const int ALPHA = 1 << 6, MAXN = 3e6 + 6;
char s[MAXN]; int a[MAXN];
struct Trie {
	int ch[MAXN][ALPHA], cnt[MAXN], size;
	inline void clear() {
		for (int i = 0; i <= size; ++i) {
			for (int j = 0; j < ALPHA; ++j)
				ch[i][j] = 0;
			cnt[i] = 0;
		}
		size = 0;
	}
	inline void insert(int a[], int n) {
		int u = 0;
		for (int i = 1; i <= n; ++i) {
			if (!ch[u][a[i]])
				ch[u][a[i]] = ++size;
			u = ch[u][a[i]]; ++cnt[u];
		}
	}
	inline int count(int a[], int n) {
		int u = 0, ans = 0;
		for (int i = 1; i <= n; ++i) {
			if (!ch[u][a[i]]) return 0;
			u = ch[u][a[i]];
		}
		return cnt[u];
	}
} T;
inline int getid(char c) {
	if (c >= '0' && c <= '9')
		return c - '0' + 1;
	if (c >= 'A' && c <= 'Z')
		return c - 'A' + 11;
	if (c >= 'a' && c <= 'z')
		return c - 'a' + 37;
}
inline void solve() {
	T.clear();
	int n, q; scanf("%d%d", &n, &q);
	while (n--) {
		scanf("%s", s + 1);
		int n = strlen(s + 1);
		for (int i = 1; i <= n; ++i)
			a[i] = getid(s[i]);
		T.insert(a, n);
	}
	while (q--) {
		scanf("%s", s + 1);
		int n = strlen(s + 1);
		for (int i = 1; i <= n; ++i)
			a[i] = getid(s[i]);
		printf("%d\n", T.count(a, n));
	}
}
int main() {
	int T; scanf("%d", &T);
	while (T--) solve();
	return 0;
}
```
