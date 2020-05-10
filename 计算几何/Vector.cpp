/**
 * 参考资料：
 * 《算法竞赛入门经典 训练指南》
 * https://linxi99.gitee.io/20190211/ACM几何基础篇/
 * https://blog.csdn.net/linxilinxilinxi/article/details/81810944
 **/
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

struct Vector{
	double x, y;
	Vector(double x = 0, double y = 0):x(x), y(y) { }

	Vector operator + (Vector rhs) {
		return Vector(this -> x + rhs.x, this -> y + rhs.y);
	}

	Vector operator - (Vector rhs) {
		return Vector(this -> x - rhs.x, this -> y - rhs.y);
	}

	Vector operator * (double p) {
		return Vector(this -> x * p, this -> y * p);
	}

	double operator * (const Vector &rhs) {	// 这里采用运算符重载实现，默认*表示点积
		return (this -> x * rhs.x + this -> y * rhs.y);
	}

	Vector operator / (double p) {
		return Vector(this -> x / p, this -> y / p);
	}

	// 小于号，用于各种数据结构和排序
	// 有时候需要按照x坐标升序排序，若x相同，则按照y升序排序
	// 此比较器将在Andrew算法中用到
	// 而Graham Scan算法用到的比较器基于极角排序
	bool operator < (const Vector &rhs) const {
		if (this -> x == rhs.x)
			return this -> y < rhs.y;
		return this -> x < rhs.x;
	}

	bool operator == (const Vector &rhs) const {
		return (dcmp(this -> x - rhs.x) == 0 && dcmp(this -> y - rhs.y) == 0);
	}

	double Length() {
		return sqrt(*this * *this);
	}

	// 逆时针旋转，rad为弧度。注意this本身不变化
	Vector Rotate(double rad) {
		return Vector(this -> x * cos(rad) - this -> y * sin(rad), this -> x * sin(rad) + this -> y * cos(rad));
	}

	// 计算逆时针旋转90度后的单位法向量
	Vector Normal() {
		double L = this -> Length();
		return Vector(this -> x / L, this -> y / L);
	}
};

typedef Vector Point;

// 叉乘，因为不习惯重载^，所以放到外面了
// 二维叉乘的正负号也是有意义的
double Cross(Vector a, Vector b) {
	return (a.x * b.y - a.y * b.x);
}

// 返回弧度制的夹角
double Angle(Vector a, Vector b) {
	return acos(a * b / a.Length() / b.Length());
}

// 计算由A点出发构成的两个向量的平行四边形的有向面积
double Aria2(Point A, Point B, Point C) {
	return Cross(B - A, C - A);
}

// 判断折线bc是不是折线ab的逆时针方向转向
bool ToLeftTest(Point A, Point B, Point C) {
	return Cross(B - A, C - B) > 0;
}



int main() {
	Vector x;
	x.x = 10, x.y = 5;
	return 0;
}
