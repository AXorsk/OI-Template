exCRT
```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = __int128;
const int MAXN = 1e5 + 6;
inline ll read() {
	ll x = 0; bool f = 0; char ch = getchar();
	while (!isdigit(ch)) f |= ch == '-', ch = getchar();
	while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}
void write(ll x) {
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) write(x / 10);
	putchar(x % 10 ^ 48);
}
ll exgcd(ll a, ll b, ll &x, ll &y) {
	if (!b) return x = 1, y = 0, a;
	ll g = exgcd(b, a % b, y, x);
	return y -= a / b * x, g;
}
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }
inline void merge(ll &A, ll &B, ll a, ll b) {
	ll x, y, g = exgcd(A, a, x, y);
	ll c = b - B;
	if (c % g) puts("-1"), exit(0);
	x = x * c / g % (a / g);
	if (x < 0) x += a / g;
	ll p = lcm(A, a);
	B = (A * x + B) % p;
	if (B < 0) B += p;
	A = p;
	write(A); putchar(' ');
	write(B); putchar('\n');
}
int main() {
	int n = read(); ll A, B;
	for (int i = 1; i <= n; ++i) {
		ll x = read(), y = read();
		if (i == 1) A = x, B = y;
		else merge(A, B, x, y);
	}
	write(B % A);
	return 0;
}
