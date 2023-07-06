Chtholly_Tree (CF896C)
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MAXN = 1e5 + 6, MOD = 1e9 + 7;
struct tNode {
	ll l, r;
	mutable ll v;
	tNode (ll l, ll r = 0, ll v = 0) : l(l), r(r), v(v) {}
	inline bool operator < (const tNode &a) const {
		return l < a.l;
	}
};
ll n, m, seed, vmax, a[MAXN];
set <tNode> s;
typedef set <tNode> ::iterator IT;
inline IT split(int pos) {
	IT it = s.lower_bound(tNode(pos));
	if (it != s.end() && it->l == pos) {
		return it;
	}
	it--;
	if (it->r < pos) return s.end();
	ll l = it->l;
	ll r = it->r;
	ll v = it->v;
	s.erase(it);
	s.insert(tNode(l, pos - 1, v));
	return s.insert(tNode(pos, r, v)).first;
}
inline void add(ll l, ll r, ll x) {
	IT itr = split(r + 1), itl = split(l);
	for (IT it = itl; it != itr; ++it)
		it->v += x;
}
inline void assign(ll l, ll r, ll x) {
	IT itr = split(r + 1), itl = split(l);
	s.erase(itl, itr);
	s.insert(tNode(l, r, x));
}
struct tRank {
	ll num, cnt;
	inline bool operator < (const tRank &a) const {
		return num < a.num;
	}
	tRank(ll num, ll cnt) : num(num), cnt(cnt) {}
};
inline ll rnk(ll l, ll r, ll x) {
	IT itr = split(r + 1), itl = split(l);
	vector <tRank> v;
	for (IT i = itl; i != itr; ++i)
		v.push_back(tRank(i->v, i->r - i->l + 1));
	sort(v.begin(), v.end());
	int i;
	for (i = 0; i < v.size(); ++i) {
		if (v[i].cnt < x)
			x -= v[i].cnt;
		else break;
	}
	return v[i].num;
}
inline ll qpow(ll x, ll y, ll p) {
	ll ans = 1, base = x % p;
	while (y) {
		if (y & 1) ans = ans * base % p;
		base = base * base % p;
		y >>= 1;
	}
	return ans;
}
inline ll calP(ll l, ll r, ll x, ll y) {
	IT itr = split(r + 1), itl = split(l);
	ll ans = 0;
	for (IT i = itl; i != itr; ++i)
		ans = (ans + qpow(i->v, x, y) * (i->r - i->l + 1) % y) % y;
	return ans;
}
inline ll rnd() {
	ll ret = seed;
	seed = (seed * 7 + 13) % MOD;
	return ret;
}
int main() {
	scanf("%lld%lld%lld%lld", &n, &m, &seed, &vmax);
	for (int i = 1; i <= n; ++i) {
		a[i] = (rnd() % vmax) + 1;
		s.insert(tNode(i, i, a[i]));
	}
	for (int i = 1; i <= m; ++i) {
		ll op, l, r, x, y;
		op = (rnd() % 4) + 1;
		l = (rnd() % n) + 1;
		r = (rnd() % n) + 1;
		if (l > r) swap(l, r);
		if (op == 3) x = (rnd() % (r - l + 1)) + 1;
		else x = (rnd() % vmax) + 1;
		if (op == 4) y = (rnd() % vmax) + 1;
		if (op == 1) add(l, r, x);
		else if (op == 2) assign(l, r, x);
		else if (op == 3) printf("%lld\n", rnk(l, r, x));
		else printf("%lld\n", calP(l, r, x, y));
	}
	return 0;
}
```
