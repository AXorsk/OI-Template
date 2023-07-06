Splay (P6136)
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
int lst, ans, tot;
struct Splay {
	int size, root;
	int ch[MAXN][2], fa[MAXN], val[MAXN], cnt[MAXN], sz[MAXN];
	inline bool chk(int x) { return ch[fa[x]][1] == x; }
	inline void update(int x) {
		sz[x] = sz[ch[x][0]] + sz[ch[x][1]] + cnt[x];
	}
	inline void rotate(int x) {
		int y = fa[x], z = fa[y];
		int cx = chk(x), cy = chk(y), w = ch[x][chk(x) ^ 1];
		ch[y][cx] = w; fa[w] = y;
		ch[z][cy] = x; fa[x] = z;
		ch[x][cx ^ 1] = y; fa[y] = x;
		update(y); update(x);
	}
	inline void splay(int x, int goal) {
		while (fa[x] != goal) {
			int y = fa[x], z = fa[y];
			if (z != goal) {
				if (chk(x) == chk(y)) rotate(y);
				else rotate(x);
			}
			rotate(x);
		}
		if (!goal) root = x;
	}
	inline void insert(int x) {
		int k = root, p = 0;
		while (k && val[k] != x) p = k, k = ch[k][x > val[k]];
		if (k) ++cnt[k];
		else {
			k = ++size;
			if (p) ch[p][x > val[p]] = k;
			ch[k][0] = ch[k][1] = 0;
			fa[k] = p; val[k] = x;
			cnt[k] = sz[k] = 1;
		}
		splay(k, 0);
	}
	inline void find(int x) {
		int k = root;
		while (ch[k][x > val[k]] && x != val[k])
			k = ch[k][x > val[k]];
		splay(k, 0);
	}
	inline int ranking(int x) {
		find(x);
		if (val[root] >= x) return sz[ch[root][0]];
		else return sz[ch[root][0]] + cnt[root];
	}
	inline int kth(int x) {
		int k = root;
		while (true) {
			if (ch[k][0] && x <= sz[ch[k][0]])
				k = ch[k][0];
			else if (x > sz[ch[k][0]] + cnt[k]) {
				x -= sz[ch[k][0]] + cnt[k];
				k = ch[k][1];
			} else return splay(k, 0), k;
		}
	}
	inline int pre(int x) {
		find(x);
		if (val[root] < x) return root;
		int k = ch[root][0];
		while (ch[k][1]) k = ch[k][1];
		return splay(k, 0), k;
	}
	inline int nxt(int x) {
		find(x);
		if (val[root] > x) return root;
		int k = ch[root][1];
		while (ch[k][0]) k = ch[k][0];
		return splay(k, 0), k;
	}
	inline void remove(int x) {
		int last = pre(x), next = nxt(x);
		splay(last, 0); splay(next, last);
		int del = ch[next][0];
		if (cnt[del] > 1) --cnt[del], splay(del, 0);
		else ch[next][0] = 0;
		update(next); update(root);
	}
} T;
int main() {
	int n = read(), m = read();
	T.insert(INT_MAX); T.insert(INT_MIN);
	while (n--) T.insert(read());
	while (m--) {
		int op = read(), x = read() ^ lst; ++tot;
		switch (op) {
			case 1: T.insert(x); break;
			case 2: T.remove(x); break;
			case 3: lst = T.ranking(x); ans ^= lst; break;
			case 4: lst = T.val[T.kth(x + 1)]; ans ^= lst; break;
			case 5: lst = T.val[T.pre(x)]; ans ^= lst; break;
			case 6: lst = T.val[T.nxt(x)]; ans ^= lst; break;
		}
	}
	write(ans);
    return 0;
}
```
