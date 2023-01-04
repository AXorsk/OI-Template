Manacher
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1.1e7 + 6;
char s[MAXN << 1];
int d[MAXN << 1], n;
inline void read() {
	char ch = getchar();
	s[0] = '^', s[n = 1] = '|';
	while (!islower(ch)) ch = getchar();
	while (islower(ch)) s[++n] = ch, s[++n] = '|', ch = getchar();
}
int main() {
	read();
	int mid = 0, r = 0, ans = 0;
	for (int i = 1; i <= n; ++i) {
		if (i <= r) d[i] = min(d[(mid << 1) - i], r - i + 1);
		while (s[i - d[i]] == s[i + d[i]]) ++d[i];
		if (d[i] + i > r) r = d[i] + i - 1, mid = i;
		ans = max(ans, d[i]);
	}
	printf("%d\n", ans - 1);
	return 0;
}
```
