A-star
```cpp
#include <bits/stdc++.h>
using namespace std;
const int dx[] = {-1, -1, -2, -2, 1, 1, 2, 2};
const int dy[] = {2, -2, 1, -1, 2, -2, 1, -1};
using mat = vector <vector <char>>;
mat a(6, vector <char>(6)), ans(6, vector <char>(6));
map <mat, int> val, vis;
struct tPos { int x, y; };
struct tNode {
	int pr, tot; tPos pt; mat st;
	bool operator < (const tNode o) const {
		return pr > o.pr;
	}
};
void init() {
	for (int i = 1; i <= 5; ++i)
		for (int j = 1; j <= i; ++j)
			ans[i][j] = '0';
	for (int i = 1; i < 5; ++i)
		for (int j = i; j <= 5; ++j)
			ans[i][j] = '1';
	ans[3][3] = '*'; ans[4][4] = '0';
}
inline int f(mat now) {
	int cnt = 0;
	for (int i = 1; i <= 5; ++i)
		for (int j = 1; j <= 5; ++j)
			cnt += now[i][j] != ans[i][j];
	return cnt;
}
void misaka(tPos pt, mat st) {
	priority_queue <tNode> pq;
	if (!f(st)) return puts("0"), void();
	tNode s = {f(st), 0, pt, st};
	pq.emplace(s); val[st] = s.pr;
	while (!pq.empty()) {
		tNode u = pq.top(); pq.pop();
		if (u.pr > 16) continue;
		for (int i = 0; i < 8; ++i) {
			int x1 = u.pt.x + dx[i];
			int y1 = u.pt.y + dy[i];
			if (x1 < 1 || x1 > 5 || y1 < 1 || y1 > 5) continue;
			mat now = u.st; swap(now[x1][y1], now[u.pt.x][u.pt.y]);
			if (!f(now))
				if (u.tot + 1 <= 15)
					return printf("%d\n", u.tot + 1), void();
			if (vis.count(now)) continue;
			tNode v = {f(now) + u.tot + 1, u.tot + 1, {x1, y1}, now};
			pq.emplace(v); val[now] = v.pr;
		}
		if (u.tot == 15) return puts("-1"), void();
		vis[u.st] = 1;
	}
	puts("-1");
}
int main() {
	int T; cin >> T;
	init();
	while (T--) {
		tPos p; vis.clear(), val.clear();
		for (int i = 1; i <= 5; ++i) {
			string s; cin >> s;
			for (int j = 1; j <= 5; ++j) {
				a[i][j] = s[j - 1];
				if (a[i][j] == '*') p = {i, j};
			}
		}
		misaka(p, a);
	}
	return 0;
}
```
