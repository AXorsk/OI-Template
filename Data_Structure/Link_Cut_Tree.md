Link_Cut_Tree ( P3690)
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
const int MAXN = 3e5 + 6;
int n, m, a[MAXN];
struct Link_Cut_Tree {
	int rev[MAXN], fa[MAXN], ch[MAXN][2], tree[MAXN];
	inline bool which(int x) { return ch[fa[x]][1] == x; }
	inline bool isroot(int x) { return ch[fa[x]][which(x)] != x; }
	inline void init() {
		for (int i = 1; i <= n; ++i)
			tree[i] = a[i];
	}
	inline void pushdown(int x) {
		if (!rev[x]) return;
		swap(ch[x][0], ch[x][1]);
		rev[ch[x][0]] ^= 1;
		rev[ch[x][1]] ^= 1;
		rev[x] = 0;
	}
	inline void update(int x) {
		if (!isroot(x)) update(fa[x]);
		pushdown(x);
	}
	inline void pushup(int x) { tree[x] = tree[ch[x][0]] ^ tree[ch[x][1]] ^ a[x]; }
	inline void rotate(int x) {
		int f = fa[x], g = fa[f], w = which(x);
		if (!isroot(f)) ch[g][which(f)] = x; fa[x] = g;
		ch[f][w] = ch[x][w ^ 1];
		if (ch[f][w]) fa[ch[f][w]] = f;
		ch[x][w ^ 1] = f; fa[f] = x;
		pushup(f); pushup(x);
	}
	inline void splay(int x) {
		update(x);
		for (; !isroot(x); rotate(x)) {
			if (isroot(fa[x])) continue;
			rotate(which(x) == which(fa[x]) ? fa[x] : x);
		}
	}
	inline void access(int x) {
		for (int p = 0; x; p = x, x = fa[x])
			splay(x), ch[x][1] = p, pushup(x);
	}
	inline void makeroot(int x) { access(x); splay(x); rev[x] ^= 1; }
	inline int findroot(int x) {
		access(x); splay(x);
		while (ch[x][0]) x = ch[x][0];
		splay(x); return x;
	}
	inline void link(int x, int y) { makeroot(x); fa[x] = y; }
	inline void split(int x, int y) { makeroot(x); access(y); splay(y); }
	inline void cut(int x, int y) {
		split(x, y);
		if (fa[x] == y && !ch[x][1])
			ch[y][0] = fa[x] = 0;
	}
	inline int query(int x, int y) { split(x, y); return tree[y]; }
	inline void change(int x, int v) { splay(x); a[x] = v; }
} LCT;
int main() {
	n = read(), m = read();
	for (int i = 1; i <= n; ++i)
		a[i] = read();
	LCT.init();
	while (m--) {
		int op = read(), x = read(), y = read();
		if (op == 0) write(LCT.query(x, y)), putchar('\n');
		if (op == 1) if (LCT.findroot(x) != LCT.findroot(y)) LCT.link(x, y);
		if (op == 2) if (LCT.findroot(x) == LCT.findroot(y)) LCT.cut(x, y);
		if (op == 3) LCT.change(x, y);
	}
	return 0;
}
```
