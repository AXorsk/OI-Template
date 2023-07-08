exBSGS (P4195)
```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
unordered_map <int, int> h;
inline int gcd(int x, int y) { return y ? gcd(y, x % y) : x; }
inline int qpow(int x, int y, int mod) {
	int ret = 1;
	while (y) {
		if (y & 1) ret = 1ll * ret * x % mod;
		x = 1ll * x * x % mod;
		y >>= 1;
	}
	return ret;
}
int exgcd(int a, int b, int &x, int &y) {
	if (!b) return x = 1, y = 0, a;
	int g = exgcd(b, a % b, y, x);
	return y -= a / b * x, g;
}
inline int inv(int a, int b) {
	int x, y; exgcd(a, b, x, y);
	return (x % b + b) % b;
}
inline int BSGS(int a, int b, int p) {
	int q = p, phi = q;
	for (int i = 2; i * i <= q; ++i) {
		if (q % i) continue;
		phi = phi / i * (i - 1);
		while (!(q % i)) q /= i;
	}
	if (q > 1) phi = phi / q * (q - 1);
	int m = ceil(sqrt(phi));
	int z = b; h.clear();
	for (int j = 0; j <= m; ++j) {
		h[z] = j;
		z = 1ll * z * a % p;
	}
	int pw = qpow(a, m, p), ret = 1;
	for (int i = 1; i <= m; ++i) {
		ret = 1ll * ret * pw % p;
		if (h.count(ret))
			return i * m - h[ret];
	}
	return -1;
}
inline int exBSGS(int a, int b, int p) {
	if (b == 1 || p == 1) return 0;
	int g = gcd(a, p), k = 0, _a = 1;
	while (g > 1) {
		if (b % g) return -1;
		++k; b /= g; p /= g; _a = 1ll * _a * (a / g) % p;
		if (_a == b) return k;
		g = gcd(a, p);
	}
	int f = BSGS(a, 1ll * b * inv(_a, p) % p, p);
	if (!~f) return -1;
	return f + k;
}
int main() {
	int a, p, b; scanf("%d%d%d", &a, &p, &b);
	while (a || p || b) {
		a %= p; b %= p;
		int ans = exBSGS(a, b, p);
		if (~ans) printf("%d\n", ans);
		else puts("No Solution");
		scanf("%d%d%d", &a, &p, &b);
	}
	return 0;
}
