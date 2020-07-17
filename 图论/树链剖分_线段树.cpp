//题目见洛谷P3384 https://www.luogu.org/problem/P3384
//内含我Debug用的代码
#include <cstdio>
#include <cstring>
// #define dbg
// #define dbg2

const int maxn = 100005;

int N, M, root, MOD;
int a[maxn], b[maxn], idx[maxn];        //a:原始树的每个节点的值  b:重新编号后每个节点的值  idx:每个节点重新编号后的编号
int son[maxn], fa[maxn], siz_tree[maxn], depth[maxn];   //son:重儿子  fa:父亲  siz_tree:树的大小  depth:当前节点的深度
int cnt, top[maxn];     //cnt:用于给每个节点重新编号  top:记录每个节点所在链的顶端
int SegTree[maxn << 2], lazy[maxn << 2];        //线段树


struct Edge {
    int from, to, nxt;
}edge[maxn << 1];       //树的边
int front[maxn], num_Edge;      //链式前向星存图

inline void Add_Edge(int, int); //添加一条边
inline int read();              //快速读入
void dfs1(int, int, int);       //处理每个节点的深度、子树大小以及重儿子
void dfs2(int, int);            //给每个节点重新编号，并处理出每条链的顶端
inline int max(int, int);
inline int min(int, int);
inline void swap(int&, int&);

void line_Add(int, int, int);
int line_Query(int, int);
void Tree_Add(int, int);
int Tree_Query(int);

/*----------------------以下为线段树----------------------*/
void PushUp(int nd) {
    SegTree[nd] = (SegTree[nd << 1] + SegTree[nd << 1 | 1]) % MOD;
}

void Build(int nd, int l, int r) {
    if(l == r) {
        SegTree[nd] = b[l];
        return ;
    }
    int mid = (l + r) >> 1;
    Build(nd << 1, l, mid);
    Build(nd << 1 | 1, mid + 1, r);
    PushUp(nd);
}

// void PushDown(int nd, int ln, int rn) {
//     if(lazy[nd] == 0) return ;
//     lazy[nd << 1] = lazy[nd] + lazy[nd << 1];
//     lazy[nd << 1 | 1] = lazy[nd] + lazy[nd << 1 | 1];
//     SegTree[nd << 1] = SegTree[nd << 1] + siz_tree[nd << 1] * ln;
//     SegTree[nd << 1 | 1] = SegTree[nd << 1 | 1] + siz_tree[nd << 1 | 1] * rn;
//     lazy[nd] = 0;
// }错误

void PushDown(long long nd, long long ln, long long rn) {
    if(lazy[nd]) {
        lazy[nd << 1] += lazy[nd];
        lazy[nd << 1 | 1] += lazy[nd];
        SegTree[nd << 1] += lazy[nd] * ln;
        SegTree[nd << 1 | 1] += lazy[nd] * rn;
        SegTree[nd << 1] %= MOD;
        SegTree[nd << 1 | 1] %= MOD;
        lazy[nd] = 0;
    }
}

// void Update(int nd, int l, int r, int L, int R, int val) {
//     if(L <= l && r <= R) {
//         lazy[nd] = lazy[nd] + val;
//         SegTree[nd] = SegTree[nd] + siz_tree[nd] * val;
//         return ;
//     }
//     PushDown(nd);
//     int mid = (l + r) >> 1;
//     if(L <= mid) Update(nd << 1, l, mid, L, R, val);
//     if(R > mid) Update(nd << 1 | 1, mid + 1, r, L, R, val);
//     PushUp(nd);
// }
// 有错误，错误来源于原来的pushdown

void Update(int nd, int l, int r, int L, int R, int val) {  //区间更新
    if(L <= l && r <= R) {
        SegTree[nd] += val * (r - l + 1);
        lazy[nd] += val;
        return ;
    }

    int mid = (l + r) >> 1;
    PushDown(nd, mid - l + 1, r - mid);
    if(L <= mid) Update(nd << 1, l, mid, L, R, val);
    if(R > mid) Update(nd << 1 | 1, mid + 1, r, L, R, val);
    PushUp(nd);
}

int Query(int nd, int l, int r, int L, int R) {
    if(L <= l && r <= R) {
        return SegTree[nd];
    }
    int mid = (l + r) >> 1;
    PushDown(nd, mid - l + 1, r - mid);
    int ans = 0;
    if(L <= mid) ans = (ans + Query(nd << 1, l, mid, L, R)) % MOD;
    if(R > mid) ans = (ans + Query(nd << 1 | 1, mid + 1, r, L, R)) % MOD;
    return ans;
}

/*----------------------以上为线段树----------------------*/



int main() {
    memset(front, -1, sizeof(front));

    N = read();
    M = read();
    root = read();
    MOD = read();
    for(int i = 1; i <= N; ++i) a[i] = read();
    for(int i = 1; i < N; ++i) {
        int x, y;
        x = read();
        y = read();
        Add_Edge(x, y);
        Add_Edge(y, x);
    }

    dfs1(root, 0, 1);
    dfs2(root, root);

    #ifdef dbg
        printf("\n\n");
        for(int i = 1; i <= N; ++i) printf("%d ", idx[i]);
        printf("\n\n");
    #endif

    Build(1, 1, N);

    #ifdef dbg
        printf("%d\n\n", Query(1, 1, N, 1, 5));
        for(int i = 1; i <= N; ++i) printf("%d ", b[i]);
        printf("\n\n");
    #endif



    while(M--) {
        int x, y, z, w;
        x = read();
        switch (x)
        {
        case 1:
            y = read();
            z = read();
            w = read();
            line_Add(y, z, w);
            break;

        case 2:
            y = read();
            z = read();
            printf("%d\n", line_Query(y, z) % MOD);
            break;

        case 3: 
            y = read();
            z = read();
            Tree_Add(y, z);
            break;
        
        case 4: 
            y = read();
            // printf("%d\n", Tree_Query(y) % MOD);
            Tree_Query(y);
            break;
        
        default:
            break;
        }
    }
    return 0;
}

inline int max(int a, int b) {
    return a > b ? a : b;
}

inline int min(int a, int b) {
    return a < b ? a : b;
}

inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while(ch > '9' || ch < '0') {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return (x * f);
}

inline void Add_Edge(int from, int to) {
    num_Edge++;
    edge[num_Edge].from = from;
    edge[num_Edge].to = to;
    edge[num_Edge].nxt = front[from];
    front[from] = num_Edge;
}

void dfs1(int nd, int f, int deep) {
    fa[nd] = f;
    depth[nd] = deep;
    siz_tree[nd] = 1;
    int max_son = -1;
    for(int i = front[nd]; i != -1; i = edge[i].nxt) {
        int j = edge[i].to;
        if(j == fa[nd]) continue;
        dfs1(j, nd, deep + 1);
        siz_tree[nd] += siz_tree[j];
        if(siz_tree[j] > max_son) {
            max_son = siz_tree[j];
            son[nd] = j;
        }
    }
}

void dfs2(int nd, int topf) {
    idx[nd] = ++cnt;
    b[cnt] = a[nd];
    top[nd] = topf;
    if(!son[nd]) return ;
    dfs2(son[nd], topf);

    for(int i = front[nd]; i != -1; i = edge[i].nxt) {
        int j = edge[i].to;
        if(j == fa[nd] || j == son[nd]) continue;
        dfs2(j, j);
    }
}

inline void swap(int &a, int &b) {
    int t = a;
    a = b;
    b = t;
}

void line_Add(int L, int R, int val) {
    #ifdef dbg
        printf("\nline query1:%d\n", line_Query(L, R));
    #endif
    val %= MOD;
    while(top[L] != top[R]) {
        if(depth[top[L]] < depth[top[R]]) swap(L, R);
        Update(1, 1, N, idx[top[L]], idx[L], val);
        L = fa[top[L]];
    }
    if(depth[L] > depth[R]) swap(L, R);
    Update(1, 1, N, idx[L], idx[R], val);

    #ifdef dbg
        printf("line query2:%d\n\n", line_Query(L, R));
    #endif
}

int line_Query(int L, int R) {
    int ans = 0;
    while(top[L] != top[R]) {
        if(depth[top[L]] < depth[top[R]]) swap(L, R);
        ans = (ans + Query(1, 1, N, idx[top[L]], idx[L])) % MOD;
        L = fa[top[L]];
    }
    if(depth[L] > depth[R]) swap(L, R);
    ans = (ans + Query(1, 1, N, idx[L], idx[R])) % MOD;
    return ans;
}

void Tree_Add(int nd, int val) {
    #ifdef dbg
        printf("\nTree query1:%d\n", Tree_Query(nd));
    #endif
    #ifdef dbg2
        for(int i = 1; i <= 9; ++i) printf("lazy %d is %d\n", i, lazy[i]);
        for(int i = 1; i <= 9; ++i) printf("SegTree %d is %d\n", i, SegTree[i]);
    #endif

    Update(1, 1, N, idx[nd], idx[nd] + siz_tree[nd] - 1, val);
    #ifdef dbg
        printf("Tree query2:%d\n\n", Tree_Query(nd));
    #endif

    #ifdef dbg2
        for(int i = 1; i <= 9; ++i) printf("lazy %d is %d\n", i, lazy[i]);
        for(int i = 1; i <= 9; ++i) printf("SegTree %d is %d\n", i, SegTree[i]);
    #endif
}

int Tree_Query(int nd) {
    #ifdef dbg2
        for(int i = 1; i <= 9; ++i) printf("lazy %d is %d\n", i, lazy[i]);
        for(int i = 1; i <= 9; ++i) printf("SegTree %d is %d\n", i, SegTree[i]);
    #endif
    // return Query(1, 1, N, idx[nd], idx[nd] + siz_tree[nd] - 1);
    printf("%d\n", Query(1, 1, N, idx[nd], idx[nd] + siz_tree[nd] - 1));
    #ifdef dbg2
        for(int i = 1; i <= 9; ++i) printf("lazy %d is %d\n", i, lazy[i]);
        for(int i = 1; i <= 9; ++i) printf("SegTree %d is %d\n", i, SegTree[i]);
    #endif
    return 0;
}