Simulate Annealing
```cpp
#include <bits/stdc++.h>
using namespace std;
#define TIME clock() * 1.0 / CLOCKS_PER_SEC
mt19937 rnd(time(NULL));
uniform_real_distribution <double> u1(0, 1), u2(-1, 1);
const int MAXN = 1e3 + 6;
int n;
struct tNode { int x, y, w; } a[MAXN];
double ansx, ansy, ansd;
inline double calc(double x, double y) {
	double ret = 0;
	for (int i = 1; i <= n; ++i) {
		double dx = a[i].x - x, dy = a[i].y - y;
		ret += hypot(dx, dy) * a[i].w;
	}
	if (ret < ansd) ansd = ret, ansx = x, ansy = y;
	return ret;
}
inline void SA() {
	double t = 10000;
	double nowx = ansx, nowy = ansy;
	while (t > 1e-10) {
		if (TIME > 0.95) {
			printf("%.3lf %.3lf\n", ansx, ansy);
			exit(0);
		}
		double nxtx = nowx + t * u2(rnd);
		double nxty = nowy + t * u2(rnd);
		double delta = calc(nxtx, nxty) - calc(nowx, nowy);
		if (exp(-delta / t) > u1(rnd)) nowx = nxtx, nowy = nxty;
		t *= 0.998;
	}
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d%d%d", &a[i].x, &a[i].y, &a[i].w);
		ansx += a[i].x; ansy += a[i].y;
	}
	ansx /= n; ansy /= n; ansd = calc(ansx, ansy);
	while (true) SA();
	return 0;
}
```
