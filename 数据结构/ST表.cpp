//ST[i][j]表示区间[ a[i],  a[i + 2^j - 1] ]的最小值
//预处理O(N log N）, 查询 O(1)
//ST[i][j] = min(ST[i][j - 1], ST[i + 2^(j-1)][j - 1])
#include <cstdio>
#include <algorithm>

using namespace std;


const int maxn = 1024;
int a[maxn];
int ST[maxn][maxn];
int lg2[maxn];

void Build_ST(int n) {
	for (int i = 2; i <= n; i++) lg2[i] = lg2[i >> 1] + 1;
	for (int i = 1; i <= n; i++) ST[i][0] = a[i];
	for (int j = 1; j <= lg2[n]; j++)
		for (int i = 1; i <= n - (1 << (j - 1)) + 1; i++)
			ST[i][j] = min(ST[i][j - 1], ST[i + (1 << (j - 1))][j - 1]);
}

int RMQ(int l, int r) {
	int t = lg2[r - l + 1];
	return min(ST[l][t], ST[r - (1 << t) + 1][t]);
}