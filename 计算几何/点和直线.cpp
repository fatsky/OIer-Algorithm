/**
 * 参考资料：
 * 《算法竞赛入门经典 训练指南》
 * https://linxi99.gitee.io/20190211/ACM几何基础篇/
 * https://blog.csdn.net/linxilinxilinxi/article/details/81810944
 * 
 * 计算机中常用点向式表示直线
 * 需要用到Point，所以就把二维向量copy过来了
 **/
#include <cstdio>
#include <cmath>
#include "Vector.cpp"

struct Line{
    Point p;
    Vector v;
    Line(Point p, Vector v): p(p), v(v) { }

    // 返回P = v + p * t
    Point point(double t) {
        return (p + v * t);
    }
};

// 调用前需保证两直线不平行，否则会出现除0错(即Cross(a.v, b.v) != 0)
Point GetLineIntersection(Line a, Line b) {
    Vector u = a.p - b.p;
    double t = Cross(b.v, u) / Cross(a.v, b.v);
    return (a.p + a.v * t);
}

// 点到直线的距离
double DistanceToLine(Point P, Line l) {
    Vector v1 = l.v, v2 = P - l.p;
    return fabs(Cross(v1, v2) / v1.Length());
}

// 点P到线段AB的距离
double DistanceToSegment(Point P, Point A, Point B) {
    if (A == B) return (P - A).Length();
    Vector v1 = B - A, v2 = P - A, v3 = P - B;
    if (dcmp(v1 * v2) < 0)
        return v2.Length();
    if (dcmp(v1 * v3) > 0)
        return v3.Length();
    return DistanceToLine(P, Line(A, B - A));
}

Point GetLineProjection(Point P, Line l) {
    Vector v = l.v;
    return (l.p + v * ((v * (P - l.p) / (v * v))));
}

int main() {
    return 0;
}