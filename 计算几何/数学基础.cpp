/**
 * 参考资料：
 * 《算法竞赛入门经典 训练指南》
 * https://linxi99.gitee.io/20190211/ACM几何基础篇/
 * https://blog.csdn.net/linxilinxilinxi/article/details/81810944
 **/

// 常用的头文件
#include <cstdio>
#include <cmath>

// 几个常用的常数
const double pi = acos(-1.0);
const double eps = 1e-10; // 用来判断等于0，同时尽量避免精度误差
const double inf = 1e100;

int dcmp(double x) { // 用来判断正负和相等，判断相等不能用==
	if (fabs(x) < eps) return 0;
	else
		return x < 0 ? -1 : 1;
}

int main() {
	double x = 1.4999;
	int fx = floor(x); 	// 向下取整
	int cx = ceil(x); 	// 向上取整
	int rx = round(x); 	// 四舍五入

	// 小心输出负0
	double a = -0.000001;
	printf("%.4f", a);

	// 反三角函数
	// 注意定义域
	x = 1.000001;
	double acx;
	acx = acos(x); //可能会返回runtime error
	
	//此时我们可以加一句判断
	x = 1.000001;
	if(fabs(x - 1.0) < eps || fabs(x + 1.0) < eps)
	    x = round(x);
	acx = acos(x);
	return 0;
}
