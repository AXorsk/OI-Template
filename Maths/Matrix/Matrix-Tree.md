Matrix-Tree (P6178)
```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read() {
	int x = 0; bool f = 0; char ch = getchar();
	while (!isdigit(ch)) f |= ch == '-', ch = getchar();
	while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}
const int MAXN = 306, MOD = 1e9 + 7;
int n, m, t, a[MAXN][MAXN];
inline void link_origin(int x, int y, int z) {
	(a[x][x] += z) %= MOD; (a[y][y] += z) %= MOD;
	(a[x][y] -= z) %= MOD; (a[y][x] -= z) %= MOD;
}
inline void link_outer(int x, int y, int z) {
	(a[y][y] += z) %= MOD;
	(a[x][y] -= z) %= MOD;
}
inline int det() {
	// remove the root: i = 1;
	int ans = 1, f = 1;
	for (int i = 2; i <= n; ++i)
		for (int j = i + 1; j <= n; ++j) {
			while (a[i][i]) {
				int x = a[j][i] / a[i][i];
				for (int k = i; k <= n; ++k)
					a[j][k] = (a[j][k] - 1ll * x * a[i][k] % MOD + MOD) % MOD;
				swap(a[i], a[j]); f = -f;
			}
			swap(a[i], a[j]); f = -f;
		}
	for (int i = 2; i <= n; ++i)
		ans = 1ll * ans * a[i][i] % MOD;
	return (ans * f + MOD) % MOD;
}
int main() {
	freopen("data.in", "r", stdin);
	freopen("my.out", "w", stdout);
	n = read(), m = read(), t = read();
	for (int i = 1; i <= m; ++i) {
		int x = read(), y = read(), z = read();
		if (!t) link_origin(x, y, z);
		else link_outer(x, y, z);
	}
	printf("%d\n", det());
	return 0;
}
```
