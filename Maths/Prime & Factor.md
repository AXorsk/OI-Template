Prime & Factor

Miller_Robbin & Pollard-$\rho$ (P4718)

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
inline ll read() {
	ll x = 0; bool f = 0; char ch = getchar();
	while (!isdigit(ch)) f |= ch == '-', ch = getchar();
	while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}
void write(ll x) {
	if (x < 0) putchar('-');
	if (x > 9) write(x / 10);
	putchar(x % 10 ^ 48);
}
mt19937_64 rnd(time(NULL));
ll gcd(ll x, ll y) { return y ? gcd(y, x % y) : x; }
inline ll qpow(ll x, ll y, ll mod) {
	ll ret = 1;
	while (y) {
		if (y & 1) ret = (__int128)ret * x % mod;
		x = (__int128)x * x % mod; y >>= 1;
	}
	return ret;
}
bool test(ll a, ll n, ll q, ll k) {
	ll x = qpow(a, q, n);
	if (x == 1) return true;
	for (int i = 0; i < k; ++i) {
		if (x == n - 1) return true;
		x = (__int128)x * x % n;
	}
	return false;
}
bool check(ll n) { // Miller_Rabin
	if (n < 2) return false;
	if (n == 2) return true;
	ll q = n - 1, k = 0;
	while (!(q & 1)) ++k, q >>= 1;
	for (int t = 0; t < 12; ++t) {
		ll a = rnd() % (n - 2) + 2; // [2, n - 1]
		if (!test(a, n, q, k)) return false;
	}
	return true;
}
ll fac(ll n) { // Pollard_Rho
	if (n == 4) return 2;
	if (check(n)) return n;
	while (1) {
		ll c = rnd() % (n - 1) + 1; // [1, n - 1]
		auto f = [=] (ll x) { return ((__int128)x * x + c) % n; };
		ll i = 0, j = 0, p = 1;
		do {
			for (int t = 0; t < 128; ++t) {
				i = f(i), j = f(f(j));
				if (i == j) break;
				ll np = (__int128)p * llabs(j - i) % n;
				if (!np) break; p = np;
			}
			ll g = gcd(p, n);
			if (g > 1) return g;
		} while (i != j);
	}
}
unordered_map <ll, ll> ram;
ll mx_fac(ll x) {
	if (ram.count(x)) return ram[x];
	ll f = fac(x);
	if (f == x) ram[x] = x;
	else ram[x] = max(mx_fac(f), mx_fac(x / f));
	return ram[x];
}
int main() {
	int T = read();
	while (T--) {
		ll x = read();
		if (check(x)) puts("Prime");
		else write(mx_fac(x)), putchar('\n');
	}
	return 0;
}
