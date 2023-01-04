CDQ Divide&Conquer (3D Partial Order)
```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read() {
	int x = 0; bool f = 0; char ch = getchar();
	while (!isdigit(ch)) f |= ch == '-', ch = getchar();
	while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}
const int MAXN = 1e5 + 6, MAXK = 2e5;
int n, m, k, cnt[MAXN], lnk[MAXN], ans[MAXN];
struct tNode { int a, b, c, w, id; } seg[MAXN], useg[MAXN], tmp[MAXN];
struct Fenwick_Tree {
	int f[MAXK + 6];
	inline int lowbit(int x) { return x & -x; }
	inline void insert(int x, int v) {
		for (; x <= k; x += lowbit(x))
			f[x] += v;
	}
	inline int ask(int x) {
		int ans = 0;
		for (; x; x -= lowbit(x))
			ans += f[x];
		return ans;
	}
} fwt;
void chtholly(int l, int r) {
	if (r <= l) return;
	int mid = l + r >> 1;
	chtholly(l, mid); chtholly(mid + 1, r);
	int p = l, i = l, j = mid + 1;
	vector <tNode> vec;
	for (; j <= r; ) {
		while (i <= mid && useg[i].b <= useg[j].b) {
			fwt.insert(useg[i].c, useg[i].w);
			vec.emplace_back(useg[i]);
			tmp[p++] = useg[i++];
		}
		cnt[useg[j].id] += fwt.ask(useg[j].c);
		tmp[p++] = useg[j++];
	}
	while (i <= mid) tmp[p++] = useg[i++];
	for (int i = l; i <= r; ++i) useg[i] = tmp[i];
	for (auto v : vec) fwt.insert(v.c, -v.w);
}
inline bool cmp(tNode x, tNode y) {
	if (x.a != y.a) return x.a < y.a;
	if (x.b != y.b) return x.b < y.b;
	if (x.c != y.c) return x.c < y.c;
	return x.id < y.id;
}
int main() {
	n = read(), k = read();
	for (int i = 1; i <= n; ++i)
		seg[i] = {read(), read(), read(), 1, i};
	sort(seg + 1, seg + n + 1, cmp);
	for (int i = 1; i <= n; ++i) {
		if (seg[i].a == useg[m].a && seg[i].b == useg[m].b && seg[i].c == useg[m].c)
			++useg[m].w, ++cnt[useg[m].id], lnk[seg[i].id] = lnk[useg[m].id];
		else useg[++m] = seg[i], lnk[seg[i].id] = seg[i].id; 
	}
	chtholly(1, m);
	for (int i = 1; i <= n; ++i){
		if (lnk[i] != i) cnt[i] = cnt[lnk[i]];
		// printf("f(%d) = %d\n", i, cnt[i]);
		++ans[cnt[i]];
	}
	for (int i = 0; i < n; ++i)
		printf("%d\n", ans[i]);
	return 0;
}
```
