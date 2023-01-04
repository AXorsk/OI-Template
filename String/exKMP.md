exKMP _(Function Z)_ 
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 2e7 + 7;
int z[MAXN], p[MAXN], n, m;
char s[MAXN], t[MAXN];
inline void getZ(char s[], int n) {
	int l = 0, r = 0; z[1] = n;
	for (int i = 2; i <= n; ++i) {
		if (i <= r) z[i] = min(z[i - l + 1], r - i + 1);
		while (i + z[i] <= n && s[i + z[i]] == s[z[i] + 1]) ++z[i];
		if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
	}
}
inline void exkmp(char s[], int n, char t[], int m) {
	getZ(t, m);
	int l = 0, r = 0;
	for (int i = 1; i <= n; ++i) {
		if (i <= r) p[i] = min(z[i - l + 1], r - i + 1);
		while (i + p[i] <= n && s[i + p[i]] == t[p[i] + 1]) ++p[i];
		if (i + p[i] - 1 > r) l = i, r = i + p[i] - 1;
	}
}
int main() {
	scanf("%s", s + 1); n = strlen(s + 1);
	scanf("%s", t + 1); m = strlen(t + 1);
	exkmp(s, n, t, m);
	ll ans = 0;
	for (int i = 1; i <= m; ++i)
		ans ^= 1ll * i * (z[i] + 1);
	printf("%lld\n", ans);
	ans = 0;
	for (int i = 1; i <= n; ++i)
		ans ^= 1ll * i * (p[i] + 1);
	printf("%lld\n", ans);
	return 0;
}
