exgcd (P5656)
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
inline ll read() {
	ll x = 0; bool f = 0; char ch = getchar();
	while (!isdigit(ch)) f |= ch == '-', ch = getchar();
	while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}
ll exgcd(ll a, ll b, ll &x, ll &y) {
	if (!b) return x = 1, y = 0, a;
	ll g = exgcd(b, a % b, y, x);
	return y -= a / b * x, g;
}
int main() {
	int T = read();
	while (T--) {
		ll a = read(), b = read(), c = read(), x, y;
		ll g = exgcd(a, b, x, y);
		if (c % g) puts("-1");
		else {
			x *= c / g, y *= c / g;
			ll p = b / g, q = a / g, k;
			if (x < 0) k = ceil((1.0 - x) / p), x += p * k, y -= q * k;
			else k = (x - 1) / p, x -= p * k, y += q * k;
			if (y > 0) {
				printf("%lld ", (y - 1) / q + 1);
				printf("%lld ", x);
				printf("%lld ", (y - 1) % q + 1);
				printf("%lld ", x + (y - 1) / q * p);
				printf("%lld ", y);
			} else {
				printf("%lld ", x);
				printf("%lld ", y + q * (ll)ceil((1.0 - y) / q));
			}
			putchar('\n');
		}
	}
	return 0;
}
```
