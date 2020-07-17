// luogu P4781
#include <cstdio>
#define _for(i, a, b) for (int i = (a); i < (b); i++)
#define _rep(i, a, b) for (int i = (a); i <= (b); i++)

typedef long long ll;

const int maxn = 2048;
const int MOD = 998244353;

ll n, k;
ll x[maxn], y[maxn];

void readll(ll & x) {
    x = 0; ll f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    x *= f;
}

// 快速幂
ll power(ll a, ll b, ll c) {
    ll res = 1;
    while (b) {
        if (b & 1) res = (res * a) % c;
        b >>= 1;
        a = (a * a) % c;
    }
    return res;
}

// 求逆元，费马小定理
ll inv(ll x) {
    return power(x, MOD - 2, MOD);
}

// 求f(x)
ll f(ll t) {
    ll tmp, tmp2 = 1, ans = 0;
    _for(i, 0, n) {
        tmp = y[i] % MOD;
        tmp2 = 1;
        _for(j, 0, n) {
            if (i == j) continue;
            tmp = (tmp * (t - x[j])) % MOD;
            tmp2 = (tmp2 * (x[i] - x[j]) % MOD) % MOD;
        }
        ans = (ans % MOD + ((tmp * inv(tmp2)) % MOD)) % MOD;
    }
    return (ans + MOD) % MOD;
}

int main() {
    readll(n); readll(k);
    _for(i, 0, n) {
        readll(x[i]);
        readll(y[i]);
        // y[i] %= MOD;
    }
    printf("%lld\n", f(k));
    return 0;
}