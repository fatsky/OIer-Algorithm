/**
 * 参考资料：
 * 《算法竞赛入门经典 训练指南》
 * https://linxi99.gitee.io/20190211/ACM几何基础篇/
 * https://blog.csdn.net/linxilinxilinxi/article/details/81810944
 **/
#include <complex>
#include <cmath>

using std::complex;

typedef complex<double> Point;
typedef Point Vector;   //复数定义向量后，自动拥有构造函数、加减法和数量积

const double eps = 1e-9;

int sgn(double x) { // 判断是否为0
    if(fabs(x) < eps)
        return 0;
    if(x < 0)
        return -1;
    return 1;
}

double Length(Vector A) {
    return abs(A);
}

double Dot(Vector A, Vector B) {    //conj(a + bi)返回共轭复数a - bi
    return real(conj(A) * B);
}

double Cross(Vector A, Vector B) {
    return imag(conj(A) * B);
}

Vector Rotate(Vector A, double rad) {
    return A * exp(Point(0, rad));  //exp(p)返回以e为底复数的指数
}