Linear_Inv (P3811)
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 3e6 + 6;
int inv[MAXN];
int main() {
	int n, p; scanf("%d%d", &n, &p);
	inv[1] = 1;
	for (int i = 2; i <= n; ++i)
		inv[i] = 1ll * (p - p / i) * inv[p % i] % p;
	for (int i = 1; i <= n; ++i)
		printf("%d\n", inv[i]);
	return 0;
}
```
