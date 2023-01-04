CRT
```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MAXN = 1e5 + 6;
int a[MAXN], m[MAXN];
int exgcd(int a, int b, int &x, int &y) {
	if (!b) return x = 1, y = 0, a;
	int g = exgcd(b, a % b, y, x);
	return y = y - a / b * x, g;
}
int main() {
	// x === a1 (% m1)
	// x === a2 (% m2)
	// ...   ...
	// x === ak (% mk)
	// only have a root in range(m1 * m2 * ... * mk)
	int k; scanf("%d", &k);
	for (int i = 1; i <= k; ++i)
		scanf("%d%d", a + i, m + i);
	// draw a matrix to help us solve the problem
	// ...
	// yi = m1 * m2 * .. * mk / mi
	// then x = sum[1, k]_{ai * yi * yi ^ -1(mod mi)}
	ll prod = 1, ans = 0;
	for (int i = 1; i <= k; ++i)
		prod *= m[i];
	for (int i = 1; i <= k; ++i) {
		ll mul = prod / m[i];
		// (prod / mi) * yi === 1 (% mi)
		// => mi * x + mul * y == gcd(mi, mul) == 1
		// -> because gcd(m1, m2, ..., mk) == 1
		int x, y; exgcd(m[i], mul, x, y);
		ans += y * mul * a[i]; ans %= prod;
	}
	ans = (ans + prod) % prod;
	printf("%lld\n", ans);
	return 0;
}
```
