BSGS (P3846)
```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
unordered_map <int, int> h;
inline int qpow(ll x, ll y, int mod) {
	ll ret = 1;
	while (y) {
		if (y & 1) ret = ret * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return ret;
}
int main() {
	int a, b, p; scanf("%d%d%d", &a, &b, &p);
	// a ^ x == b (% p)
	// a ^ phi(p) == 1 (% p)
	int q = p, phi = q;
	for (int i = 2; i * i <= q; ++i) {
		if (q % i) continue;
		phi = phi / i * (i - 1);
		while (!(q % i)) q /= i;
	}
	if (q > 1) phi = phi / q * (q - 1);
	// a ^ x == b (% p)   x -> [0, phi]
	int m = ceil(sqrt(phi));
	// x : im - j;   i -> [1, m], j -> [0, m]
	// a ^ (im - j) == b (% p)
	// a ^ im == a ^ j * b (% p)
	int z = b;
	for (int j = 0; j <= m; ++j) {
		h[z] = j;
		z = 1ll * z * a % p;
	}
	for (int i = 1; i <= m; ++i) {
		int ret = qpow(a, i * m, p);
		if (h.count(ret)) {
			printf("%d\n", i * m - h[ret]);
			return 0;
		}
	}
	puts("-1");
	return 0;
}
