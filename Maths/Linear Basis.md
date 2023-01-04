Linear Basis1
```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MAXN = 50 + 6;
int n; ll p[MAXN];
inline void insert(ll x) {
	for (int i = 50; i >= 0; --i)
		if (x & (1ll << i)) {
			if (!p[i]) return p[i] = x, void();
			else x ^= p[i];
		}
}
inline ll getans() {
	ll ans = 0;
	for (int i = 50; i >= 0; --i)
		if ((ans ^ p[i]) > ans)
			ans ^= p[i];
	return ans;
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		ll x; scanf("%lld", &x);
		insert(x);
	}
	printf("%lld\n", getans());
	return 0;
}
```
Prefix Linear Basis
```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read() {
	int x = 0; bool f = 0; char ch = getchar();
	while (!isdigit(ch)) f |= ch == '-', ch = getchar();
	while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}
const int MAXN = 5e5 + 6;
struct Prefix_Linear_Basis {
	int p[1 << 5], pos[1 << 5];
	inline void insert(Prefix_Linear_Basis lst, int x, int w) {
		*this = lst;
		for (int i = 30; ~i; --i)
			if ((x >> i) & 1) {
				if (!p[i]) { p[i] = x; pos[i] = w; break; }
				else if (pos[i] < w) swap(pos[i], w), swap(p[i], x);
				x ^= p[i];
			}
	}
	inline int query(int l) {
		int ans = 0;
		for (int i = 30; ~i; --i)
			if (p[i] && pos[i] >= l)
				ans = max(ans, ans ^ p[i]);
		return ans;
	}
} blp[MAXN];
int main() {
	int n = read();
	for (int i = 1; i <= n; ++i)
		blp[i].insert(blp[i - 1], read(), i);
	int q = read();
	while (q--) {
		int l = read(), r = read();
		printf("%d\n", blp[r].query(l));
	}
	return 0;
}
```
