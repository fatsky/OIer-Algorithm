#include <cstdio>

typedef __int128_t ll;

const int maxn = 100005;

ll a[maxn], b[maxn], n;

void read_ll(ll &x) {
    x = 0; ll f = 1;
    char ch = getchar();
    while (ch > '9' || ch < '0') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    x *= f;
}

void print_ll(ll x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) print_ll(x / 10);
    putchar((char)(x % 10 + '0'));
}

ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll r = exgcd(b, a % b, x, y);
    ll t = x; x = y; y = t - a / b * y;
    return r;
}

ll excrt(ll n, ll *a, ll *m) { // 共n组数据，ans \equiv a[i] mod m[i]
    ll x, y;
    ll M = m[0], ans = a[0];    // 第一个方程的解特判
    for (int i = 1; i < n; i++) {
        ll p = M, b = m[i], c = (a[i] - ans % b + b) % b;   // px \equiv c (\mod b)
        ll r = exgcd(p, b, x, y), bg = b / r;
        if (c % r) return -1;   // 方程无解

        x = (x * c / r) % bg;
        ans += x * M;
        M *= bg;
        ans = (ans % M + M) % M;
    }
    return ((ans % M + M) % M);
}

