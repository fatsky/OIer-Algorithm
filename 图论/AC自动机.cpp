/**
 * 来自OI-Wiki
 * https://www.luogu.com.cn/problem/P3808
 * 这份代码的时间和空间复杂度都很棒
 **/

#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
#define _for(i, a, b) for (int i = (a); i < (b); i++)
#define _rep(i, a, b) for (int i = (a); i <= (b); i++)

using namespace std;
const int maxn = 1e6 + 5;
int n = 0;

int tr[maxn][26], tot = 0;
int e[maxn] = {0}, fail[maxn] = {0};

void insert(char *s) {
    int u = 0, len = strlen(s);
    _for(i, 0, len) {
        if (!tr[u][s[i] - 'a']) tr[u][s[i] - 'a'] = ++tot;
        u = tr[u][s[i] - 'a'];
    }
    e[u]++;
}

queue<int> q;

void Build() {
    _for(i, 0, 26)
        if (tr[0][i]) q.push(tr[0][i]);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        _for(i, 0, 26)
            if (tr[u][i])
                fail[tr[u][i]] = tr[fail[u]][i], q.push(tr[u][i]);
            else
                tr[u][i] = tr[fail[u]][i];
    }
}

int Query(char *t) {
    int u = 0, res = 0, len = strlen(t);
    _for(i, 0, len) {
        u = tr[u][t[i] - 'a'];
        for (int j = u; j && e[j] != -1; j = fail[j]) {
            res += e[j]; e[j] = -1;
        }
    }
    return res;
}

char str[maxn];

int main() {
    scanf("%d", &n);
    _for(i, 0, n) {
        scanf("%s", str);
        insert(str);
    }
    Build();
    scanf("%s", str);
    printf("%d\n", Query(str));
    return 0;
}