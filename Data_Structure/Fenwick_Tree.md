Fenwick_Tree
```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read() {
	int x = 0; bool f = 0; char ch = getchar();
	while (!isdigit(ch)) f |= ch == '-', ch = getchar();
	while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}
void write(int x) {
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) write(x / 10);
	putchar(x % 10 ^ 48);
}
const int MAXN = 2e6 + 6;
int n, m;
struct Fenwick_Tree {
	int f[MAXN];
	inline int lowbit(int x) { return x & -x; }
	inline void add(int x, int v) {
		for (; x <= n; x += lowbit(x))
			f[x] += v;
	}
	inline int getsum(int x) {
		int ans = 0;
		for (; x; x -= lowbit(x))
			ans += f[x];
		return ans;
	}
} fwt;
int main() {
	n = read(), m = read();
	for (int i = 1; i <= n; ++i)
		fwt.add(i, read());
	while (m--) {
		int a = read(), b = read(), c = read();
		if (a == 1) fwt.add(b, c);
		else write(fwt.getsum(c) - fwt.getsum(b - 1)), putchar('\n');
	}
	return 0;
}
```
