exEuler (P5091)
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
inline int qpow(int x, int y, int m) {
	int ret = 1;
	while (y) {
		if (y & 1) ret = 1ll * ret * x % m;
		x = 1ll * x * x % m;
		y >>= 1;
	}
	return ret;
}
inline int read(int m) {
	ll x = 0; bool f = 0; char ch = getchar();
	while (!isdigit(ch)) ch = getchar();
	while (isdigit(ch)) {
		x = x * 10 + (ch ^ 48);
		if (x >= m) f = 1, x %= m;
		ch = getchar();
	}
	return x + (f ? m : 0);
}
int main() {
	int a, m; scanf("%d%d", &a, &m);
	int phi = m, _m = m;
	for (int i = 2; 1ll * i * i <= _m; ++i) {
		if (_m % i) continue;
		while (!(_m % i)) _m /= i;
		phi = phi / i * (i - 1);
	}
	if (_m > 1) phi = phi / _m * (_m - 1);
	int b = read(phi);
	printf("%d\n", qpow(a, b, m));
	return 0;
}
```
