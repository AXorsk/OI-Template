exLucas
```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MAXN = 1e6 + 6;
int tot, b[MAXN], c[MAXN];
inline int qpow(ll x, ll y, int m) {
	int ret = 1;
	while (y) {
		if (y & 1) ret = 1ll * ret * x % m;
		x = 1ll * x * x % m; y >>= 1;
	}
	return ret;
}
inline int exgcd(int a, int b, int &x, int &y) {
	if (!b) return x = 1, y = 0, a;
	int g = exgcd(b, a % b, y, x);
	return y -= a / b * x, g;
}
inline int inv(int a, int m) {
	int x = 0, y = 0;
	exgcd(a, m, x, y);
	return (x % m + m) % m;
}
int crt() {
	int mul = 1, ans = 0;
	for (int i = 1; i <= tot; ++i) mul *= c[i];
	for (int i = 1; i <= tot; ++i) {
		int iv = inv(mul / c[i], c[i]);
		ans = (ans + 1ll * b[i] * (mul / c[i]) * iv % mul) % mul;
	}
	return (ans + mul) % mul;
}
int calc(ll n, int p, int pk) {
	if (!n) return 1;
	int ans = 1;
	for (int i = 1; i <= pk; ++i)
		if (i % p) ans = 1ll * ans * i % pk;
	ans = qpow(ans, n / pk, pk);
	for (int i = 1; i <= n % pk; ++i)
		if (i % p) ans = 1ll * ans * i % pk;
	return 1ll * ans * calc(n / p, p, pk) % pk;
}
int C(ll n, ll m, int p, int pk) {
	if (!n || !m || n == m) return 1;
	if (n < m) return 0;
	int nn = calc(n, p, pk), mm = calc(m, p, pk), nm = calc(n - m, p, pk);
	int cnt = 0; ll k = n - m;
	while (n) n /= p, cnt += n;
	while (m) m /= p, cnt -= m;
	while (k) k /= p, cnt -= k;
	return 1ll * nn * inv(mm, pk) % pk * inv(nm, pk) % pk * qpow(p, cnt, pk) % pk;
}
int exlucas(ll n, ll m, int p) {
	for (int i = 2; i * i <= p; ++i) {
		int pk = 1;
		while (!(p % i)) p /= i, pk *= i;
		if (pk > 1) b[++tot] = C(n, m, i, pk), c[tot] = pk;
	}
	if (p > 1) b[++tot] = C(n, m, p, p), c[tot] = p;
	return crt();
}
int main() {
	ll N, M; int P; cin >> N >> M >> P;
	cout << exlucas(N, M, P) << endl;
	return 0;
}
···
