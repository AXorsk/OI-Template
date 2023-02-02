Suffix Array
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e6 + 6, ALP = 1 << 7;
char s[MAXN];
int n, bin[MAXN], ht[MAXN], tmp[MAXN];
int sa[MAXN], _sa[MAXN], rk[MAXN], _rk[MAXN];
inline bool cmp(int *a, int x, int y, int w) { return a[x] == a[y] && a[x + w] == a[y + w]; }
void SA() {
	for (int i = 1; i <= n; ++i) ++bin[s[i]];
	for (int i = 0; i < ALP; ++i) bin[i] += bin[i - 1];
	for (int i = n; i >= 1; --i) sa[bin[s[i]]--] = i;
	for (int i = 1; i <= n; ++i) rk[sa[i]] = rk[sa[i - 1]] + (s[sa[i]] != s[sa[i - 1]]);
	for (int k = 1; k <= n; k <<= 1) {
		for (int i = 1; i <= n; ++i) bin[rk[sa[i]]] = i;
		for (int i = n; i >= 1; --i) if (sa[i] > k) _sa[bin[rk[sa[i] - k]]--] = sa[i] - k;
		for (int i = n - k + 1; i <= n; ++i) _sa[bin[rk[i]]] = i;
		for (int i = 1; i <= n; ++i) _rk[_sa[i]] = _rk[_sa[i - 1]] + !cmp(rk, _sa[i], _sa[i - 1], k);
		swap(rk, _rk); swap(sa, _sa);
		if (rk[sa[n]] >= n) break;
	}
	for (int i = 1, k = 0; i <= n; ++i) {
		int j = sa[rk[i] - 1];
		while (s[i + k] == s[j + k]) ++k;
		ht[rk[i]] = k; if (k) --k;
	}
}
int main() {
	scanf("%s", s + 1);
	n = strlen(s + 1); SA();
	for (int i = 1; i <= n; ++i) printf("%d ", sa[i]);
	return 0;
}
```
