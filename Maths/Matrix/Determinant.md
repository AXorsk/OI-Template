Determinant
```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read() {
	int x = 0; bool f = 0; char ch = getchar();
	while (!isdigit(ch)) f |= ch == '-', ch = getchar();
	while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}
const int MAXN = 606;
int n, a[MAXN][MAXN], MOD;
inline int det() {
	int ans = 1, f = 1;
	for (int i = 1; i <= n; ++i)
		for (int j = i + 1; j <= n; ++j) {
			while (a[i][i]) {
				int x = a[j][i] / a[i][i];
				for (int k = i; k <= n; ++k)
					a[j][k] = (a[j][k] - 1ll * x * a[i][k] % MOD + MOD) % MOD;
				swap(a[i], a[j]); f = -f;
			}
			swap(a[i], a[j]); f = -f;
		}
	for (int i = 1; i <= n; ++i)
		ans = 1ll * ans *  a[i][i] % MOD;
	return (ans * f + MOD) % MOD;
}
int main() {
	n = read(), MOD = read();
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			a[i][j] = read();
	printf("%d\n", det());
	return 0;
}
```
