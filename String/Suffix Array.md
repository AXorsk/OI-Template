Suffix Array
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e6 + 6;
char s[MAXN];
int n, m, sa[MAXN], rnk[MAXN], bin[MAXN], tmp[MAXN];
inline void bsort() {
	int k = max(n, m);
	for (int i = 0; i <= k; ++i) bin[i] = 0;
	for (int i = 1; i <= n; ++i) ++bin[rnk[i]];
	for (int i = 1; i <= k; ++i) bin[i] += bin[i - 1];
	for (int i = n; i >= 1; --i) sa[bin[rnk[tmp[i]]]--] = tmp[i];
}
inline void SA() {
	for (int i = 1; i <= n; ++i) tmp[i] = i, rnk[i] = s[i];
	bsort();
	for (int j = 1; j <= n; j <<= 1) {
		int tot = 0;
		for (int i = n - j + 1; i <= n; ++i) tmp[++tot] = i;
		for (int i = 1; i <= n; ++i) if (sa[i] > j) tmp[++tot] = sa[i] - j;
		bsort();
		tmp[sa[1]] = tot = 1;
		for (int i = 2; i <= n; ++i) tmp[sa[i]] = (rnk[sa[i]] == rnk[sa[i - 1]] && rnk[sa[i] + j] == rnk[sa[i - 1] + j]) ? tot : ++tot;
		memcpy(rnk, tmp, sizeof(int) * (n + 1));
	}
}
int main() {
	scanf("%s", s + 1);
	n = strlen(s + 1); m = 1 << 7; SA();
	for (int i = 1; i <= n; ++i)
		printf("%d ", sa[i]);
	putchar('\n');
	return 0;
}
