Mo’s Algorithm (Original)
```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MAXN = 5e4 + 6;
int a[MAXN], cnt[MAXN], n, m, block;
struct tQue { int l, r, id; } q[MAXN];
struct tAns { int l, r; ll p, q; } ans[MAXN];
inline int read() {
	int x = 0; bool f = 0; char ch = getchar();
	while (!isdigit(ch)) f |= ch == '-', ch = getchar();
	while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}
void write(ll x) {
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) write(x / 10);
	putchar(x % 10 ^ 48);
}
ll gcd(ll x, ll y) { return y ? gcd(y, x % y) : x; }
inline bool cmp(tQue u, tQue v) {
	if (u.l / block != v.l / block) return u.l / block < v.l / block;
	if (u.l / block & 1) return u.r < v.r;
	return u.r > v.r;
}
int main() {
	n = read(), m = read();
	block = sqrt(n);
	for (int i = 1; i <= n; ++i)
		a[i] = read();
	for (int i = 1; i <= m; ++i) {
		int x = read(), y = read();
		q[i] = {x, y, i};
		ans[i] = {x, y, 0, 1};
	}
	sort(q + 1, q + m + 1, cmp);
	int l = 1, r = 0; ll now = 0;
	for (int i = 1; i <= m; ++i) {
		while (q[i].l < l) now += cnt[a[--l]]++;
		while (q[i].l > l) now -= --cnt[a[l++]];
		while (q[i].r > r) now += cnt[a[++r]]++;
		while (q[i].r < r) now -= --cnt[a[r--]];
		ans[q[i].id].p = now;
	}
	for (int i = 1; i <= m; ++i) {
		if (ans[i].l == ans[i].r)
			ans[i].p = 0, ans[i].q = 1;
		else {
			ans[i].q = (ans[i].r - ans[i].l + 1ll) * (ans[i].r - ans[i].l) >> 1;
			ll g = gcd(ans[i].p, ans[i].q);
			ans[i].p /= g; ans[i].q /= g;
		}
		write(ans[i].p); putchar('/');
		write(ans[i].q); putchar('\n');
	}
	return 0;
}
```
Mo’s Algorithm (Modifiable)
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2e5 + 6, MAXC = 1e6 + 6;
int n, m, cntq, cntc, block;
int a[MAXN], cnt[MAXC], ans[MAXN];
struct tNode { int p, c; } c[MAXN];
struct tQue { int l, r, ct, t; } q[MAXN];
inline int read() {
	int x = 0; bool f = 0; char ch = getchar();
	while (!isdigit(ch)) f |= ch == '-', ch = getchar();
	while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}
inline char readc() {
	char ch = getchar();
	while (!isalpha(ch)) ch = getchar();
	return ch;
}
void write(int x) {
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) write(x / 10);
	putchar(x % 10 ^ 48);
}
inline bool cmp(tQue a, tQue b) {
	if (a.l / block != b.l / block) return a.l / block < b.l / block;
	if (a.r / block != b.r / block) return a.r / block < b.r / block;
	if (a.r / block & 1) return a.t < b.t;
	return a.t > b.t;
}
inline int insert(int x) { return cnt[x]++ ? 0 : 1; }
inline int remove(int x) { return --cnt[x] ? 0 : 1; }
int main() {
	n = read(), m = read();
	block = pow(n, 2.0 / 3.0);
	for (int i = 1; i <= n; ++i) a[i] = read();
	for (int i = 1; i <= m; ++i) {
		char op = readc(); int x = read(), y = read();
		if (op == 'Q') q[++cntq] = {x, y, cntc, cntq};
		else c[++cntc] = {x, y};
	}
	sort(q + 1, q + cntq + 1, cmp);
	int l = 1, r = 0, t = 0, now = 0;
	for (int i = 1; i <= cntq; ++i) {
		while (l < q[i].l) now -= remove(a[l++]);
		while (l > q[i].l) now += insert(a[--l]);
		while (r < q[i].r) now += insert(a[++r]);
		while (r > q[i].r) now -= remove(a[r--]);
		while (t < q[i].ct) {
			++t;
			if (q[i].l <= c[t].p && c[t].p <= q[i].r) {
				now -= remove(a[c[t].p]);
				now += insert(c[t].c);
			}
			swap(a[c[t].p], c[t].c);
		}
		while (t > q[i].ct) {
			if (q[i].l <= c[t].p && c[t].p <= q[i].r) {
				now -= remove(a[c[t].p]);
				now += insert(c[t].c);
			}
			swap(a[c[t].p], c[t].c);
			--t;
		}
		ans[q[i].t] = now;
	}
	for (int i = 1; i <= cntq; ++i)
		write(ans[i]), putchar('\n');
	return 0;
}
```
