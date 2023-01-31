exKMP _(Function Z)_ 
1. "extend"
```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MAXN = 2e7 + 6;
char s[MAXN], t[MAXN];
int n, m, Z[MAXN], P[MAXN];
void get_Z() {
	int j = 0, p = 2;
	while (j + 2 <= m && t[j + 1] == t[j + 2]) ++j;
	Z[1] = m; Z[2] = j;
	for (int i = 3; i <= m; ++i) {
		if (i + Z[i - p + 1] < p + Z[p]) Z[i] = Z[i - p + 1];
		else {
			j = max(0, p + Z[p] - i);
			while (i + j <= m && t[j + 1] == t[i + j]) ++j;
			Z[i] = j; p = i;
		}
	}
}
void exKMP() {
	int j = 0, p = 1;
	while (j + 1 <= m && t[j + 1] == s[j + 1]) ++j;
	P[1] = j;
	for (int i = 2; i <= n; ++i) {
		if (i + Z[i - p + 1] < p + P[p]) P[i] = Z[i - p + 1];
		else {
			j = max(0, p + P[p] - i);
			while (j + 1 <= m && i + j <= n && t[j + 1] == s[i + j]) ++j;
			P[i] = j; p = i;
		}
	}
}
int main() {
	scanf("%s%s", s + 1, t + 1);
	n = strlen(s + 1), m = strlen(t + 1);
	get_Z(); exKMP();
	ll ans = 0;
	for (int i = 1; i <= m; ++i)
		ans ^= 1ll * i * (Z[i] + 1);
	printf("%lld\n", ans);
	ans = 0;
	for (int i = 1; i <= n; ++i)
		ans ^= 1ll * i * (P[i] + 1);
	printf("%lld\n", ans);
	return 0;
}
```
2. "manacher"
```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MAXN = 2e7 + 6;
char s[MAXN], t[MAXN];
int n, m, Z[MAXN], P[MAXN];
void get_Z() {
    int l = 0, r = 0; Z[1] = m;
    for (int i = 2; i <= m; ++i) {
        if (i <= r) Z[i] = min(Z[i - l + 1], r - i + 1);
        while (i + Z[i] <= m && t[i + Z[i]] == t[Z[i] + 1]) ++Z[i];
        if (i + Z[i] - 1 > r) l = i, r = i + Z[i] - 1;
    }
}
void exKMP() {
    int l = 0, r = 0;
    for (int i = 1; i <= n; ++i) {
        if (i <= r) P[i] = min(Z[i - l + 1], r - i + 1);
        while (i + P[i] <= n && s[i + P[i]] == t[P[i] + 1]) ++P[i];
        if (i + P[i] - 1 > r) l = i, r = i + P[i] - 1;
    }
}
int main() {
    scanf("%s%s", s + 1, t + 1);
    n = strlen(s + 1), m = strlen(t + 1);
    get_Z(); exKMP();
    ll ans = 0;
    for (int i = 1; i <= m; ++i)
        ans ^= 1ll * i * (Z[i] + 1);
    printf("%lld\n", ans);
    ans = 0;
    for (int i = 1; i <= n; ++i)
        ans ^= 1ll * i * (P[i] + 1);
    printf("%lld\n", ans);
    return 0;
}
```
