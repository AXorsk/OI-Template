Convex-Hull
```cpp
#include <bits/stdc++.h>
using namespace std;
using pii = pair <double, double>;
const int MAXN = 1e5 + 6;
pii a[MAXN], stk[MAXN];
int top; double ans;
inline double D(pii x, pii y) { return hypot(x.first - y.first, x.second - y.second); }
inline double K(pii x, pii y) { return x.first == y.first ? INT_MAX : (x.second - y.second) / (x.first - y.first); }
int main() {
	int n; scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		scanf("%lf%lf", &a[i].first, &a[i].second);
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; ++i) {
		stk[++top] = a[i];
		while (top > 2 && K(stk[top], stk[top - 2]) < K(stk[top - 1], stk[top - 2]))
			stk[top - 1] = stk[top], --top;
	}
	for (int i = 2; i <= top; ++i)
		ans += D(stk[i], stk[i - 1]);
	top = 0;
	for (int i = n; i; --i) {
		stk[++top] = a[i];
		while (top > 2 && K(stk[top], stk[top - 2]) < K(stk[top - 1], stk[top - 2]))
			stk[top - 1] = stk[top], --top;
	}
	for (int i = 2; i <= top; ++i)
		ans += D(stk[i], stk[i - 1]);
	printf("%.2lf", ans);
	return 0;
}
```
