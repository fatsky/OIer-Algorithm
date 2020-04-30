/* 快速幂取模
** 公式：(ab) mod c = [ (a mod c) * (b mod c) ] mod c
**
** 证明：
** a mod c = d  <==>  a = tc + d
** b mod c = e  <==>  b = kc + e
** ab mod c = (tc + d)(kc + e) mod c
**			= [tkc^2 + (te + dk)c + de] mod c
**			= de mod c
**			= [(a mod c) * (b mod c)] mod c
**
** 可得：
** 公式： a^b mod c = (a mod c)^b mod c
**
**
** 快速幂公式：
** a^b mod c = [(a^2)^(b / 2)] mod c	//b是偶数
** a^b mod c = [(a^2)^(b / 2) * a]mod c	//b是奇数
*/


//O(N) 算法
int fastpower_1(int a, int b, int c){
	a %= c;
	int ans = 1;

	for(int i = 1;i <= b;i++)
		ans = (ans * a) % c;

	ans = (ans * a) % c;
	return ans;
}


//O(log N)算法 递归
long long a,b,c,t;
long long fastpower_2(long long x){
	if(x == 1) return t;
	if(x & 1){
		long long temp = fastpower_2(x >> 1);
		return ((temp * temp) % c * t) % c;
	}
	else {
		long long temp = fastpower_2(x >> 1);
		return (temp * temp) % c;
	}
}

// int main(){
// 	scanf("%d%d%d", &a, &b, &c);
// 	t = a % c;
// 	printf("%d ^ %d mod %d = %d", a, b, c, fastpower_2(b));
// 	return 0;
// }


//O(log N)算法 迭代
int fastpower_3(int a, int b, int c){
	int res = 1;
	a %= c;
	while(b){
		if(b & 1)	res = (res * a) % c;
		a = (a * a) % c;
		b >>= 1;
	}
	return res;
}


