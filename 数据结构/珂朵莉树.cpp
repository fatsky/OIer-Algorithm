/**
 * 本代码是Codeforces 896C的AC代码
 * 珂朵莉树，一种非常暴力的神奇数据结构
 * 又叫老司机树Old Driver Tree
 * 然后很神奇的时间复杂度很低（数据随机情况下）
 **/ 

#include <cstdio>
#include <set>
#include <vector>
#include <algorithm>

using std::set;
using std::sort;
using std::vector;
using std::pair;
using std::swap;

typedef long long ll;

struct Node {
    ll l, r;
    mutable ll v;       // 据说不加mutable可能会CE，没有亲测
    Node(ll u, ll v = -1, ll w = 0): l(u), r(v), v(w) { }
    bool operator < (const Node &rhs) const {
        return this -> l < rhs.l;
    }
};

ll fpower(ll a, ll b, ll c) {   // 快速幂板子
    a %= c;
    ll res = 1;
    while (b) {
        if (b & 1) res = (res * a) % c;
        a = (a * a) % c;
        b >>= 1;
    }
    return res;
}

set<Node> s;

set<Node>::iterator split(ll pos) {     // 将区间[L, R]划分成[L, pos - 1]和[pos, R]
    set<Node>::iterator it = s.lower_bound(pos);
    if (it != s.end() && it -> l == pos) return it;
    --it;
    ll L = it -> l, R = it -> r, V = it -> v;

    s.erase(it);
    s.insert(Node(L, pos - 1, V));
    return s.insert(Node(pos, R, V)).first;
}

void Assign(ll l, ll r, ll val = 0) {   // 区间赋值
    set<Node>::iterator itl = split(l), itr = split(r + 1);
    s.erase(itl, itr);
    s.insert(Node(l, r, val));
}

void Add(ll l, ll r, ll val) {  // 区间加
    set<Node>::iterator itl = split(l), itr = split(r + 1);
    for ( ; itl != itr; itl++) {
        itl -> v += val;
    }
}

ll rank(ll l, ll r, ll k) {     // 区间第k小
    vector<pair<ll, ll> > vp;
    vp.clear();
    set<Node>::iterator itl = split(l), itr = split(r + 1);
    for ( ; itl != itr; itl++)
        vp.push_back(pair<ll, ll>(itl -> v, itl -> r - itl -> l + 1));
    
    sort(vp.begin(), vp.end());
    for (vector<pair<ll, ll> >::iterator itl = vp.begin(); itl != vp.end(); itl++) {
        k -= itl -> second;
        if (k <= 0)
            return itl -> first;
    }
    return -1LL;
}

ll SegPow(ll l, ll r, ll ex, ll mod) {      // 具体含义清参考题目
    set<Node>::iterator itl = split(l), itr = split(r + 1);
    ll res = 0;
    for ( ; itl != itr; itl++)
        res = (res + (itl -> r - itl -> l + 1) * fpower(itl -> v, ex, mod)) % mod;
    return res;
}

ll n, m, seed, vmax, op, l, r, x, y;

ll rnd(ll &seed) {
    ll ret = seed;
    seed = (seed * 7 + 13) % 1000000007;
    return ret;
}

int main() {
    scanf("%lld%lld%lld%lld", &n, &m, &seed, &vmax);
    for (int i = 1; i <= n; i++) {
        s.insert(Node(i, i, rnd(seed) % vmax + 1));
    }

    for (int i = 1; i <= m; i++) {
        op = rnd(seed) % 4 + 1;
        l = rnd(seed) % n + 1;
        r = rnd(seed) % n + 1;

        if (l > r)
            swap(l, r);
        
        if (op == 3) 
            x = rnd(seed) % (r - l + 1) + 1;
        else 
            x = rnd(seed) % vmax + 1;
        

        if (op == 4)
            y = rnd(seed) % vmax + 1;

        switch (op) {
            case 1:
                Add(l, r, x);
                break;
            case 2:
                Assign(l, r, x);
                break;
            case 3:
                printf("%lld\n", rank(l, r, x));
                break;
            case 4:
                printf("%lld\n", SegPow(l, r, x, y));
                break;
        }
    }
    return 0;
}