Minimum Show
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 3e5 + 6;
int n, a[MAXN];
int minimum() {
	int i = 0, j = 1, k = 0;
	while (i < n && j < n && k < n) {
		if (a[(i + k) % n] == a[(j + k) % n]) ++k;
		else {
			if (a[(i + k) % n] > a[(j + k) % n]) i += k + 1;
			else j += k + 1;
			if (i == j) ++i;
			k = 0;
		}
	}
	return min(i, j);
}
int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i)
		scanf("%d", a + i);
	int p = minimum();
	for (int i = 0; i < n; ++i)
		printf("%d ", a[(p + i) % n]);
	return 0;
}
```
