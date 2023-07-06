FHQ_Treap [General] (P3369)
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
const int MAXN = 1e5 + 6;
mt19937 rnd(20061216);
struct FHQ_Treap {
	int root, size, ch[MAXN][2];
	int val[MAXN], pri[MAXN], sz[MAXN];
	inline int newnode(int v) {
		int k = ++size;
		val[k] = v;
		pri[k] = rnd();
		sz[k] = 1;
		return k;
	}
	inline void pushup(int k) {
		sz[k] = sz[ch[k][0]] + sz[ch[k][1]] + 1;
	}
	void split(int k, int v, int &x, int &y) {
		if (!k) return x = y = 0, void();
		if (v < val[k]) {
			y = k;
			split(ch[k][0], v, x, ch[k][0]);
		} else {
			x = k;
			split(ch[k][1], v, ch[k][1], y);
		}
		pushup(k);
	}
	int merge(int x, int y) {
		if (!x || !y) return x | y;
		if (pri[x] < pri[y]) {
			ch[x][1] = merge(ch[x][1], y);
			pushup(x); return x;
		} else {
			ch[y][0] = merge(x, ch[y][0]);
			pushup(y); return y;
		}
	}
	int query(int k, int x) {
		if (sz[ch[k][0]] + 1 == x) return val[k];
		if (x <= sz[ch[k][0]]) return query(ch[k][0], x);
		else return query(ch[k][1], x - sz[ch[k][0]] - 1);
	}
} T;
int main() {
	int Q = read();
	while (Q--) {
		int op = read(), v = read(), x, y, z;
		if (op == 1) {
			T.split(T.root, v, x, y);
			T.root = T.merge(T.merge(x, T.newnode(v)), y);
		}
		if (op == 2) {
			T.split(T.root, v, x, z);
			T.split(x, v - 1, x, y);
			T.root = T.merge(T.merge(x, T.ch[y][0]), T.merge(T.ch[y][1], z));
		}
		if (op == 3) {
			T.split(T.root, v - 1, x, y);
			write(T.sz[x] + 1), putchar('\n');
			T.root = T.merge(x, y);
		}
		if (op == 4) write(T.query(T.root, v)), putchar('\n');
		if (op == 5) {
			T.split(T.root, v - 1, x, y); z = x;
			while (T.ch[z][1]) z = T.ch[z][1];
			write(T.val[z]), putchar('\n');
			T.root = T.merge(x, y);
		}
		if (op == 6) {
			T.split(T.root, v, x, y); z = y;
			while (T.ch[z][0]) z = T.ch[z][0];
			write(T.val[z]), putchar('\n');
			T.root = T.merge(x, y);
		}
	}
	return 0;
}
```
FHQ_Treap [Reverse] (P3391)
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
const int MAXN = 1e5 + 6;
mt19937 rnd(20061216);
struct FHQ_Treap {
	int root, size, ch[MAXN][2]; bool tag[MAXN];
	int val[MAXN], pri[MAXN], sz[MAXN];
	inline int newnode(int v) {
		int k = ++size;
		val[k] = v;
		pri[k] = rnd();
		sz[k] = 1;
		return k;
	}
	inline void pushup(int k) {
		sz[k] = sz[ch[k][0]] + sz[ch[k][1]] + 1;
	}
	inline void pushdown(int k) {
		if (!tag[k]) return;
		tag[ch[k][0]] ^= 1;
		tag[ch[k][1]] ^= 1;
		swap(ch[k][0], ch[k][1]);
		tag[k] = 0;
	}
	void split(int k, int v, int &x, int &y) {
		if (!k) return x = y = 0, void();
		pushdown(k);
		if (sz[ch[k][0]] < v) {
			x = k;
			split(ch[k][1], v - sz[ch[k][0]] - 1, ch[k][1], y);
		} else {
			y = k;
			split(ch[k][0], v, x, ch[k][0]);
		}
		pushup(k);
	}
	int merge(int x, int y) {
		if (!x || !y) return x | y;
		if (pri[x] < pri[y]) {
			pushdown(x);
			ch[x][1] = merge(ch[x][1], y);
			pushup(x); return x;
		} else {
			pushdown(y);
			ch[y][0] = merge(x, ch[y][0]);
			pushup(y); return y;
		}
	}
	void misaka(int k) {
		if (!k) return;
		pushdown(k);
		misaka(ch[k][0]);
		write(val[k]), putchar(' ');
		misaka(ch[k][1]);
	}
} T;
int main() {
	int n = read(), m = read();
	for (int i = 1; i <= n; ++i)
		T.root = T.merge(T.root, T.newnode(i));
	int x, y, z;
	for (int i = 1; i <= m; ++i) {
		int l = read(), r = read();
		T.split(T.root, l - 1, x, y);
		T.split(y, r - l + 1, y, z);
		T.tag[y] ^= 1;
		T.root = T.merge(x, T.merge(y, z));
	}
	T.misaka(T.root);
	return 0;
}
```
