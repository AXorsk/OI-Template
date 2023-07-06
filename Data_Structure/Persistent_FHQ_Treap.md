Persistent_FHQ_Treap [General] (P3835)
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
const int MAXN = 5e5 + 6;
int root[MAXN];
mt19937 rnd(20061216);
struct tNode { int val, pri, sz, lson, rson; };
struct FHQ_Treap {
	int size;
	tNode t[MAXN * 100];
	inline int newnode(int v) {
		int k = ++size;
		t[k].val = v;
		t[k].pri = rnd();
		t[k].sz = 1;
		return k;
	}
	inline void pushup(int k) {
		t[k].sz = t[t[k].lson].sz + t[t[k].rson].sz + 1;
	}
	void split(int k, int v, int &x, int &y) {
		if (!k) return x = y = 0, void();
		if (v < t[k].val) {
			y = ++size; t[y] = t[k];
			split(t[k].lson, v, x, t[y].lson);
			pushup(y);
		} else {
			x = ++size; t[x] = t[k];
			split(t[k].rson, v, t[x].rson, y);
			pushup(x);
		}
	}
	int merge(int x, int y) {
		if (!x || !y) return x | y;
		if (t[x].pri < t[y].pri) {
			t[x].rson = merge(t[x].rson, y);
			pushup(x); return x;
		} else {
			t[y].lson = merge(x, t[y].lson);
			pushup(y); return y;
		}
	}
	int query(int k, int x) {
		if (t[t[k].lson].sz + 1 == x) return t[k].val;
		if (x <= t[t[k].lson].sz) return query(t[k].lson, x);
		else return query(t[k].rson, x - t[t[k].lson].sz - 1);
	}
} T;
int main() {
	int n = read();
	root[0] = T.merge(T.newnode(INT_MIN + 1), T.newnode(INT_MAX));
	for (int i = 1; i <= n; ++i) {
		int vs = read(), op = read(), v = read(), x, y, z;
		root[i] = root[vs];
		if (op == 1) {
			T.split(root[i], v, x, y);
			root[i] = T.merge(T.merge(x, T.newnode(v)), y);
		}
		if (op == 2) {
			T.split(root[i], v, x, z);
			T.split(x, v - 1, x, y);
			root[i] = T.merge(T.merge(x, T.t[y].lson), T.merge(T.t[y].rson, z));
		}
		if (op == 3) {
			T.split(root[i], v - 1, x, y);
			write(T.t[x].sz), putchar('\n');
			root[i] = T.merge(x, y);
		}
		if (op == 4) write(T.query(root[i], v + 1)), putchar('\n');
		if (op == 5) {
			T.split(root[i], v - 1, x, y); z = x;
			while (T.t[z].rson) z = T.t[z].rson;
			write(T.t[z].val), putchar('\n');
			root[i] = T.merge(x, y);
		}
		if (op == 6) {
			T.split(root[i], v, x, y); z = y;
			while (T.t[z].lson) z = T.t[z].lson;
			write(T.t[z].val), putchar('\n');
			root[i] = T.merge(x, y);
		}
	}
	return 0;
}
```
Persistent_FHQ_Treap [Reverse] (P5055)
```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
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
const int MAXN = 2e5 + 6;
int root[MAXN];
mt19937 rnd(20061216);
struct tNode {
	bool tag; ll sum;
	int val, pri, sz, lson, rson;
};
struct FHQ_Treap {
	int size;
	tNode t[MAXN * 100];
	inline int newnode(int v) {
		int k = ++size;
		t[k].val = t[k].sum = v;
		t[k].pri = rnd();
		t[k].sz = 1;
		return k;
	}
	inline void pushup(int k) {
		t[k].sz = t[t[k].lson].sz + t[t[k].rson].sz + 1;
		t[k].sum = t[t[k].lson].sum + t[t[k].rson].sum + t[k].val;
	}
	inline void pushdown(int k) {
		if (!t[k].tag) return;
		int x, y;
		if (t[k].lson) {
			x = ++size;
			t[x] = t[t[k].lson];
			t[t[k].lson = x].tag ^= 1;
		}
		if (t[k].rson) {
			y = ++size;
			t[y] = t[t[k].rson];
			t[t[k].rson = y].tag ^= 1;
		}
		swap(t[k].lson, t[k].rson);
		t[k].tag = 0;
	}
	void split(int k, int v, int &x, int &y) {
		if (!k) return x = y = 0, void();
		pushdown(k);
		if (t[t[k].lson].sz + 1 <= v) {
			x = ++size; t[x] = t[k];
			split(t[k].rson, v - t[t[k].lson].sz - 1, t[x].rson, y);
			pushup(x);
		} else {
			y = ++size; t[y] = t[k];
			split(t[k].lson, v, x, t[y].lson);
			pushup(y);
		}
	}
	int merge(int x, int y) {
		if (!x || !y) return x | y;
		if (t[x].pri < t[y].pri) {
			pushdown(x);
			t[x].rson = merge(t[x].rson, y);
			pushup(x); return x;
		} else {
			pushdown(y);
			t[y].lson = merge(x, t[y].lson);
			pushup(y); return y;
		}
	}
} T;
int main() {
	ll last = 0; int n = read();
	for (int i = 1; i <= n; ++i) {
		int vs = read(), op = read(), x, y, z;
		root[i] = root[vs];
		if (op == 1) {
			int p = read() ^ last, v = read() ^ last;
			T.split(root[i], p, x, y);
			root[i] = T.merge(T.merge(x, T.newnode(v)), y);
		}
		if (op == 2) {
			int p = read() ^ last;
			T.split(root[i], p, x, z);
			T.split(x, p - 1, x, y);
			root[i] = T.merge(x, z);
		}
		if (op == 3) {
			int l = read() ^ last, r = read() ^ last;
			T.split(root[i], r, x, z);
			T.split(x, l - 1, x, y);
			T.t[y].tag ^= 1;
			root[i] = T.merge(T.merge(x, y), z);
		}
		if (op == 4) {
			int l = read() ^ last, r = read() ^ last;
			T.split(root[i], r, x, z);
			T.split(x, l - 1, x, y);
			last = T.t[y].sum;
			write(last), putchar('\n');
			root[i] = T.merge(T.merge(x, y), z);
		}
	}
	return 0;
}
```
