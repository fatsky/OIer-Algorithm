#include <cstdio>
typedef long long ll;

ll exgcd(ll a, ll b, ll &x, ll &y) {
	if (b == 0) {
		x = 1;
		y = 0; 
		return a;
	}
	ll r = exgcd(b, a % b, x, y);
	ll t = x;
	x = y;
	y = t - a / b * y;
	return r;
}

// n个方程：x = a[i] % m[i], (0 <= i < n)
ll CRT(int n, int *a, int *m) {
    ll M = 1, t, y, x = 0;
    for (int i = 0; i < n; i++) M *= m[i];
    for (int i = 0; i < n; i++) {
        ll w = M / m[i];
        exgcd(w, m[i], t, y);
		x = ((x + t * w * a[i]) % M + M) % M;
    }
    return x;
}
