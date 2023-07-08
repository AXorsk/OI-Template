Lucas (P3807)
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 6;
int n, m, p, fac[MAXN], invfac[MAXN];
inline int qpow(int x, int y) {
	int ret = 1;
	while (y) {
		if (y & 1) ret = 1ll * ret * x % p;
		x = 1ll * x * x % p;
		y >>= 1;
	}
	return ret;
}
inline void init(int n) {
	fac[0] = 1;
	for (int i = 1; i <= n; ++i)
		fac[i] = 1ll * fac[i - 1] * i % p;
}
inline int C(int n, int m) {
	if (m > n) return 0;
	return 1ll * fac[n] * qpow(fac[m], p - 2) % p * qpow(fac[n - m], p - 2) % p;
}
int lucas(int n, int m) {
	if (!m) return 1;
	return 1ll * C(n % p, m % p) * lucas(n / p, m / p) % p;
}
int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d", &n, &m, &p); init(p);
		printf("%d\n", lucas(n + m, n));
	}
	return 0;
}
```
