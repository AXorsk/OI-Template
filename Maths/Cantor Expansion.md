Cantor Expansion (P5367)
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 1e6 + 6, MOD = 998244353;
int n, a[MAXN], fac[MAXN], ans;
struct Fenwick_Tree {
	int f[MAXN];
	inline int lowbit(int x) { return x & -x; }
	inline void add(int x, int v) {
		for (; x <= n; x += lowbit(x))
			f[x] += v;
	}
	inline int getsum(int x) {
		int ans = 0;
		for (; x; x -= lowbit(x))
			ans += f[x];
		return ans;
	}
} BIT;
int main() {
	scanf("%d", &n); fac[0] = 1;
	for (int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
		fac[i] = 1ll * fac[i - 1] * i % MOD;
	}
	for (int i = 1; i <= n; ++i) {
		int tot = a[i] - 1 - BIT.getsum(a[i] - 1);
		ans = (ans + 1ll * tot * fac[n - i] % MOD) % MOD;
		BIT.add(a[i], 1);
	}
	printf("%d\n", ans + 1);
	return 0;
}
