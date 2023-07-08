Gauss_Elimination  _Gauss-Jordan_  (P3389)
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e2 + 6;
double a[MAXN][MAXN];
int main() {
	int n; cin >> n;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n + 1; ++j)
			cin >> a[i][j];
	for (int i = 1; i <= n; ++i) {
		int t = i;
		for (int j = t + 1; j <= n; ++j)
			if (fabs(a[j][i]) > fabs(a[t][i])) t = j;
		if (t != i) swap(a[i], a[t]);
		if (!a[i][i]) return puts("No Solution"), 0;
		double x = a[i][i];
		for (int j = 1; j <= n + 1; ++j)
			a[i][j] /= x;
		for (int j = 1; j <= n; ++j) {
			if (i == j) continue;
			double x = -a[j][i] / a[i][i];
			for (int k = 1; k <= n + 1; ++k)
				a[j][k] += a[i][k] * x;
		}
	}
	for (int i = 1; i <= n; ++i)
		cout << fixed << setprecision(2) << a[i][n + 1] << endl;
	return 0;
}
```
