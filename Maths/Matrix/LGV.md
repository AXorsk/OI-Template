LGV
```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read() {
	int x = 0; bool f = 0; char ch = getchar();
	while (!isdigit(ch)) f |= ch == '-', ch = getchar();
	while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}
using ll = long long;
const int MAXN = 1e6 + 6, MAXM = 106, MOD = 998244353;
int n, m, a[MAXM], b[MAXM];
ll fac[MAXN << 1], invf[MAXN << 1], inv[MAXN << 1], M[MAXM][MAXM];
inline ll qpow(ll x, ll y) {
	ll ret = 1;
	while (y) {
		if (y & 1) ret = ret * x % MOD;
		x = x * x % MOD; y >>= 1;
	}
	return ret;
}
inline ll C(int n, int m) {
	return fac[n] * invf[m] % MOD * invf[n - m] % MOD;
}
inline void init() {
	fac[0] = 1;
	for (int i = 1; i <= n << 1; ++i)
		fac[i] = fac[i - 1] * i % MOD;
	invf[n << 1] = qpow(fac[n << 1], MOD - 2);
	for (int i = (n << 1) - 1; ~i; --i)
		invf[i] = invf[i + 1] * (i + 1) % MOD;
}
inline ll det() {
	int f = 1; ll ans = 1;
	for (int i = 1; i <= m; ++i)
		for (int j = i + 1; j <= m; ++j) {
			while (M[i][i]) {
				ll x = M[j][i] / M[i][i];
				for (int k = i; k <= m; ++k)
					M[j][k] = (M[j][k] - x * M[i][k] % MOD + MOD) % MOD;
				swap(M[i], M[j]); f = -f;
			}
			swap(M[i], M[j]); f = -f;
		}
	for (int i = 1; i <= m; ++i)
		ans = ans * M[i][i] % MOD;
	return (ans * f + MOD) % MOD;
}
void solve() {
	n = read(), m = read(); init();
	for (int i = 1; i <= m; ++i)
		a[i] = read(), b[i] = read();
	for (int i = 1; i <= m; ++i)
		for (int j = 1; j <= m; ++j)
			M[i][j] = a[i] <= b[j] ? C(b[j] - a[i] + n - 1, n - 1) : 0;
	printf("%lld\n", det());
}
int main() {
	int T = read();
	while (T--) solve();
	return 0;
}
```
