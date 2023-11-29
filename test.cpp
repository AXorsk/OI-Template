#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
using namespace __gnu_cxx;
using namespace __gnu_pbds;
using pii = pair <int, int>;
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
set <int> st; map <int, int> mp;
unordered_map <int, int> ump;
tree <pii, null_type, less <pii>, rb_tree_tag, tree_order_statistics_node_update> rbt;
#define TIME clock() * 1.0 / CLOCKS_PER_SEC
mt19937 rnd(time(NULL));
uniform_real_distribution <double> u(-1, 1);
void fst() {
	for (int i = 1; i <= 100; ++i) st.insert(i);
	auto it = st.upper_bound(47);
	st.erase(it);
	for (auto i : st) printf("%d ", i);
	putchar('\n');
}
void fmp() {
	for (int i = 1; i <= 100; ++i) mp[i] = i + 1;
	auto it = mp.lower_bound(15); ++it;
	cout << it->first << ": " << it->second << endl;
	printf("%d\n", mp.count(48));
}
void fump() {
	for (int i = 1; i <= 100; ++i) ump[i] = i - 1;
	printf("%d\n", ump.count(49));
}
void frbt() {
	int n = read();
	for (int i = 1; i <= n; ++i) {
		int op = read(), x = read();
		if (op == 1) rbt.insert(make_pair(x, i));
		else if (op == 2) {
			auto it = rbt.upper_bound(make_pair(x, 0));
			rbt.erase(it);
		} else if (op == 3) {
			int k = rbt.order_of_key(make_pair(x, 0)) + 1;
			printf("%d\n", k);
		} else if (op == 4) {
			auto it = rbt.find_by_order(x - 1);
			if (it != rbt.end()) printf("%d\n", it->first);
		} else if (op == 5) {
			auto it = rbt.upper_bound(make_pair(x, 0)); --it;
			pii v = *it;
			printf("%d\n", v.first);
		} else {
			auto it = rbt.upper_bound(make_pair(x, INT_MAX));
			pii v = *it;
			printf("%d\n", v.first);
		}
	}
}
int main() {
	freopen("data.in", "r", stdin);
	freopen("my.out", "w", stdout);
	fst();
	fmp();
	fump();
	frbt();
	// cout << u(rnd) << endl;
	// printf("%.5lfs\n", TIME);
	return 0;
}