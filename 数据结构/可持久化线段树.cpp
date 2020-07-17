#include <cstdio>
#include <algorithm>

const int maxn = 1e6 + 5;

int top, root[maxn], n, m, a[maxn], rt, mode, x, y;

void readint(int &x) {
    x = 0; int f = 1;
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


struct Node {
    int lson, rson , val;
}tree[maxn * 20];

int Clone(int nd) {
    top++;
    tree[top] = tree[nd];
    return top;
}

int Build(int nd, int l, int r) {
    nd = ++top;
    if (l == r) {
        tree[nd].val = a[l];
        return top;
    }

    int mid = (l + r) >> 1;
    tree[nd].lson = Build(tree[nd].lson, l, mid);
    tree[nd].rson = Build(tree[nd].rson, mid + 1, r);
    return nd;
}

int Update(int nd, int l, int r, int loc, int val) {
    nd = Clone(nd);
    if (l == r) {
        tree[nd].val = val;
        return nd;
    }
    int mid = (l + r) >> 1;
    if (loc <= mid) tree[nd].lson = Update(tree[nd].lson, l, mid, loc, val);
    else tree[nd].rson = Update(tree[nd].rson, mid + 1, r, loc, val);
    return nd;
}

int Query(int nd, int l, int r, int loc) {
    if (l == r) 
        return tree[nd].val;
    int mid = (l + r) >> 1;
    if (loc <= mid) return Query(tree[nd].lson, l, mid, loc);
    else return Query(tree[nd].rson, mid + 1, r, loc);
}

int main() {
    readint(n); readint(m);
    for (int i = 1; i <= n; i++) readint(a[i]);
    root[0] = Build(0, 1, n);

    for (int i = 1; i <= m; i++) {
        readint(rt); readint(mode); readint(x);
        if (mode == 1) {
            scanf("%d", &y);
            root[i] = Update(root[rt], 1, n, x, y);
        }
        else {
            printf("%d\n", Query(root[rt], 1, n, x));
            root[i] = root[rt];
        }
    }
    return 0;
}
