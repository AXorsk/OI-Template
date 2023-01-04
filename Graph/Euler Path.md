Eulerian Path
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
int n, m, in[MAXN], out[MAXN], p[MAXN];
vector <int> g[MAXN]; stack <int> ans;
void misaka(int u) {
	//									++i ...Wrong!
	for (int i = p[u]; i < g[u].size(); i = p[u])
		p[u] = i + 1, misaka(g[u][i]);
	ans.emplace(u);
}
void output() {
	while (!ans.empty()) {
		printf("%d ", ans.top());
		ans.pop();
	}
}
int main() {
	n = read(), m = read();
	for (int i = 1; i <= m; ++i) {
		int u = read(), v = read();
		g[u].emplace_back(v);
		++out[u]; ++in[v];
	}
	for (int i = 1; i <= n; ++i)
		sort(g[i].begin(), g[i].end());
	int cnt1 = 0, cnt2 = 0, f = 0, s = 1;
	for (int i = 1; i <= n; ++i) {
		if (in[i] != out[i]) f = 1;
		if (in[i] - out[i] == 1) ++cnt1;
		if (out[i] - in[i] == 1) ++cnt2, s = i;
	}
	if (f && (cnt1 != 1 || cnt2 != 1)) return !puts("No");
	misaka(s); output();
	return 0;
}
```
