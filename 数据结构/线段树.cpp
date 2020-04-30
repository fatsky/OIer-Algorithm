// 魔改自 https://blog.csdn.net/yyt330507870/article/details/70037135
// 顺便加了读入优化
// luogu P3372
// 全部用了long long

#include <cstdio>

const int MAXN = 100000;
long long a[MAXN], segtree[MAXN << 2], lazy[MAXN << 2];


void PushUp(long long nd) {
    segtree[nd] = segtree[nd << 1] + segtree[nd << 1 | 1];
}

void Build(long long l, long long r, long long nd) {
    if(l == r) {
        segtree[nd] = a[l];
        return ;
    }
    long long mid = (l + r) >> 1;
    Build(l, mid, nd << 1);
    Build(mid + 1, r, nd << 1 | 1);
    PushUp(nd);
}

void PushDown(long long nd, long long ln, long long rn) {
    if(lazy[nd]) {
        lazy[nd << 1] += lazy[nd];
        lazy[nd << 1 | 1] += lazy[nd];
        segtree[nd << 1] += lazy[nd] * ln;
        segtree[nd << 1 | 1] += lazy[nd] * rn;
        lazy[nd] = 0;
    }
}

void Add(long long loc, long long val, long long l, long long r, long long nd) {  //点更新
    if(l == r) {
        segtree[nd] += val;
        return ;
    }

    long long mid = (l + r) >> 1;
    PushDown(nd, mid - l + 1, r - mid);        //这里去掉Query好像会错，但是仍然不清楚原因
    if(loc <= mid) Add(loc, val, l, mid, nd << 1);
    else Add(loc, val, mid + 1, r, nd << 1 | 1);
    PushUp(nd);
}

void Update(long long L, long long R, long long val, long long l, long long r, long long nd) {  //区间更新
    if(L <= l && r <= R) {
        segtree[nd] += val * (r - l + 1);
        lazy[nd] += val;
        return ;
    }

    long long mid = (l + r) >> 1;
    PushDown(nd, mid - l + 1, r - mid);
    if(L <= mid) Update(L, R, val, l, mid, nd << 1);
    if(R > mid) Update(L, R, val, mid + 1, r, nd << 1 | 1);
    PushUp(nd);
}

long long Query(long long L, long long R, long long l, long long r, long long nd) {
    if(L <= l && r <= R)
        return segtree[nd];
    long long mid = (l + r) >> 1;
    PushDown(nd, mid - l + 1, r - mid);
    long long ANS = 0;
    if(L <= mid) ANS += Query(L, R,  l, mid, nd << 1);
    if(R > mid) ANS += Query(L, R, mid + 1, r, nd << 1 | 1);
    return ANS;
}

long long readlong() {
    long long x = 0, f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9') {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch =  getchar();
    }
    return (x * f);
}


long long n, m, x, y, z, k;

int main() {
    n = readlong();
    m = readlong();
    for(int i = 1; i <= n; i++) {
        a[i] = readlong();
    }

    Build(1, n, 1);
    for(int i = 0; i < m; i++) {
        x = readlong();
        if(x == 1) {
            y = readlong();
            z = readlong();
            k = readlong();
            Update(y, z, k, 1, n, 1);
        }
        else {
            y = readlong();
            z = readlong();
            printf("%lld\n", Query(y, z, 1, n, 1));
        }
    }
    return 0;
}