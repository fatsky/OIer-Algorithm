//修改和求区间和的时间复杂度均为O(log n);
//令C数组为树状数组， A数组为原数组
//i & (-i) 为 2 ^ x;
//此处的x等于 i 二进制数的末尾 1 的位数 -1
const int MAXN = 1030;
int C[MAXN], A[MAXN];

void Plus(int i, int val) {	//第i个数加val
	A[i] += val;
	while(i <= n) {
		C[i] += val;
		i += i & (-i);
	}
}

int Sum(int i) {
	//前i个元素和
	int sum = 0;
	while(i > 0) {
		sum += C[i];
		i -= i & (-i);
	}
	return sum;
}