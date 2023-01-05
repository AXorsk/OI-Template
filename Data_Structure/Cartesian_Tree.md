Cartesian_Tree
```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read() {
	int x = 0; bool f = 0; char ch = getchar();
	while (!isdigit(ch)) f |= ch == '-', ch = getchar();
	while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}
const int MAXN = 1e5 + 6;
using ll = long long;
int n, a[MAXN];
struct Cartesian_Tree {
	Cartesian_Tree() { top = 0; }
	int stk[MAXN], top;
	int lson[MAXN], rson[MAXN];
	inline void insert_nxt(int k, int v) {
		int p = top;
		while (p && a[stk[p]] > v) --p;
		if (p) rson[stk[p]] = k;
		if (p < top) lson[k] = stk[p + 1];
		stk[top = p + 1] = k;
	}
	void misaka(int k) {
		if (!k) return;
		printf("%d ", k);
		misaka(lson[k]); misaka(rson[k]);
	}
} T;
int main() {
	n = read();
	for (int i = 1; i <= n; ++i)
		a[read()] = i;
	for (int i = 1; i <= n; ++i)
		T.insert_nxt(i, a[i]);
	T.misaka(T.stk[1]);
	return 0;
}
```
