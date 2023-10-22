RB_Tree `pbds` (P3369)

```cpp
#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
using namespace __gnu_cxx;
using namespace __gnu_pbds;
inline int read() {
	int x = 0; bool f = 0; char ch = getchar();
	while (!isdigit(ch)) f |= ch == '-', ch = getchar();
	while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}
using pii = pair <int, int>;
tree <pii, null_type, less <pii>, rb_tree_tag, tree_order_statistics_node_update> T;
int main() {
	int n = read();
	for (int i = 1; i <= n; ++i) {
		int op = read(), x = read();
		if (op == 1) T.insert(make_pair(x, i));
		else if (op == 2) {
			auto it = T.upper_bound(make_pair(x, 0));
			T.erase(it);
		} else if (op == 3) {
			int k = T.order_of_key(make_pair(x, 0)) + 1;
			printf("%d\n", k);
		} else if (op == 4) {
			auto it = T.find_by_order(x - 1);
			if (it != T.end()) printf("%d\n", it->first);
		} else if (op == 5) {
			auto it = T.upper_bound(make_pair(x, 0)); --it;
			pii v = *it;
			printf("%d\n", v.first);
		} else {
			auto it = T.upper_bound(make_pair(x, INT_MAX));
			pii v = *it;
			printf("%d\n", v.first);
		}
	}
	return 0;
}
```