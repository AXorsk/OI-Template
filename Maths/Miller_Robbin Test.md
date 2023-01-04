Miller_Robbin Test
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef __int128 ll;
inline ll read() {
	ll x = 0; bool f = 0; char ch = getchar();
	while (!isdigit(ch)) f |= ch == '-', ch = getchar();
	while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}
inline ll qpow(ll x, ll y, ll mod) {
	ll ret = 1;
	while (y) {
		if (y & 1) ret = ret * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return ret;
}
inline bool test(ll a, ll n, ll q, ll k) {
	ll x = qpow(a, q, n);
	if (x == 1) return true;
	for (int i = 0; i < k; ++i) {
		if (x == n - 1) return true;
		x = x * x % n;
	}
	return false;
}
inline bool check(ll n) {
	if (n < 2) return false;
	if (n == 2) return true;
	ll q = n - 1, k = 0;
	while (!(q & 1)) ++k, q >>= 1;
	for (int i = 1; i <= 10; ++i) {
		ll a = rand() % (n - 2) + 2;
		if (!test(a, n, q, k)) return false;
	}
	return true;
}
int main() {
	int T = read(); srand(time(0));
	while (T--) puts(check(read()) ? "Y" : "N");
	return 0;
}
