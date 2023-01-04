KMP
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e6 + 6;
char s[MAXN], t[MAXN];
int nxt[MAXN];
inline void getnext(char s[], int n) {
	int j = 0; nxt[1] = 0;
	for (int i = 2; i <= n; ++i) {
		while (j && s[j + 1] != s[i]) j = nxt[j];
		if (s[j + 1] == s[i]) ++j;
		nxt[i] = j;
	}
}
inline void KMP(char s[], char t[], int n, int m) {
	int j = 0;
	for (int i = 1; i <= n; ++i) {
		while (j && t[j + 1] != s[i]) j = nxt[j];
		if (t[j + 1] == s[i]) ++j;
		if (j == m) {
			printf("%d\n", i - m + 1);
			j = nxt[j];
		}
	}
}
int main() {
	scanf("%s%s", s + 1, t + 1);
	int n = strlen(s + 1), m = strlen(t + 1);
	getnext(t, m); KMP(s, t, n, m);
	for (int i = 1; i <= m; ++i)
		printf("%d ", nxt[i]);
	puts("");
	return 0;
}
