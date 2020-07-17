#include <cstdio>

typedef long long ll;

ll F(ll a, ll b, ll c, ll n) {    // (ai + b) / c, From i = 0 to i = n;
    if (c == 0) return 0;
    if (a >= c || b >= c)
        return (n * (n + 1) / 2 * (a / c) + (n + 1) * (b / c)) + F(a % c, b % c, c, n);
    ll m = (a * n + b) / c;
    return n * m - F(c, c - b - 1, a, m - 1);
}