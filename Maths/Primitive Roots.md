Primitive Roots
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e6 + 6;
int n, _n, c, d, g, phi, _phi, cnt, q[MAXN], ans[MAXN];
inline int qpow(int x, int y, int p) {
	int ret = 1;
	while (y) {
		if (y & 1) ret = 1ll * ret * x % p;
		x = 1ll * x * x % p;
		y >>= 1;
	}
	return ret;
}
int gcd(int x, int y) { return y ? gcd(y, x % y) : x; }
inline bool check() {
	if (qpow(g, phi, n) != 1) return false;
	for (int i = 1; i <= cnt; ++i) {
		int k = phi / q[i];
		if (qpow(g, k, n) == 1) return false;
	}
	return true;
}
inline void misaka() {
	scanf("%d%d", &n, &d);
	_n = n, phi = n;
	for (int i = 2; i * i <= _n; ++i) {
		if (_n % i) continue;
		while (!(_n % i)) _n /= i;
		phi = phi / i * (i - 1);
	}
	if (_n >= 2) phi = phi / _n * (_n - 1);
	_phi = phi, cnt = 0;
	for (int i = 2; i * i <= _phi; ++i) {
		if (_phi % i) continue;
		while (!(_phi % i)) _phi /= i;
		q[++cnt] = i;
	}
	if (_phi >= 2) q[++cnt] = _phi;
	g = 1, c = 0;
	for (; g < n; ++g)
		if (check()) break;
	if (g == n) return puts("0\n"), void();
	for (int i = 1; i <= phi; ++i)
		if (gcd(i, phi) == 1)
			ans[++c] = qpow(g, i, n);
	sort(ans + 1, ans + c + 1);
	printf("%d\n", c);
	for (int i = 1; i <= c / d; ++i)
		printf("%d ", ans[d * i]);
	putchar('\n');
}
int main() {
	int T; scanf("%d", &T);
	while (T--) misaka();
}
