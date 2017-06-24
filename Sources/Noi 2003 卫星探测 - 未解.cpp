/*这道题我的方法是二分判断+计算几何。

首先要找到多边形的边界，可以用四个点分别表示多边形上下左右边界的一个顶点。寻找边界可以用二分的方法。由于已知原点一定在多边形内或边上，寻找左边界就可以从x取值-10000到0之间二分答案，其余边界以此类推。

确定边界后，接着要确定每个每个顶点的位置，由于这是一个凸多边形，而且没有边与坐标轴平行，所以从左界点到下界点之间的一段折线斜率一定是严格单调递增的，类似的相邻两个边界点之间的一段折线的斜率也都是单调的。于是我们可以二分答案，确定折线每条线段的端点。最后在按照极角排序好的顶点顺序求出多边形面积，顺序输出每个顶点坐标。其实再写程序时如果求折线端点的顺序恰当，顶点就是直接排好的。

为了尽量减少询问次数，可以把已经询问过的记录下来，以免重复询问。计算几何题一般来说细节较多，代码量大，很难一次写对。再加上这是一个交互式题，我调了好长时间。由于询问次数的限制，我的程序不能拿到满分，后面有几个点都是8分9分。谁要是能写出满分的程序，我一定拜读。

/*
 * Problem: NOI2003 detect
 * Author: Guo Jiabao
 * Time: 2009.5.26 13:30
 * State: Solved
 * Memo: 交互式 二分 凸多边形面积
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include "detect_lib.h"
using namespace std;
const int MAXB = 10000, MAXL = 20001, MAXN = 201;
const double zero = 1e-6;
struct point {
	double x, y;
} LB, RB, BB, TB, V[MAXN], V2[MAXN];
struct ask {
	int acnt;
	double v1, v2;
} AX0[MAXL], AY0[MAXL], *Ax, *Ay;
int N, N2;
double (*opt)(double, double) ;
double min(double a, double b) {
	if (a == MAXB + 1) { return b; }
	if (b == MAXB + 1) { return a; }
	return a < b ? a : b;
}
double max(double a, double b) {
	if (a == MAXB + 1) { return b; }
	if (b == MAXB + 1) { return a; }
	return a > b ? a : b;
}
void init() {
	Ax = AX0 + MAXB; Ay = AY0 + MAXB;
	prog_initialize();
	for (int i = -MAXB; i <= MAXB; i++) {
		Ax[i].acnt = Ay[i].acnt = -1;
	}
}
ask Ask(int k, bool x) {
	if (x) {
		if (Ax[k].acnt == -1) {
			Ax[k].acnt = ask_x(k, &Ax[k].v1, &Ax[k].v2);
		}
		if (Ax[k].acnt == 1) {
			Ax[k].v2 = MAXB + 1;
		}
		return Ax[k];
	}
	else {
		if (Ay[k].acnt == -1) {
			Ay[k].acnt = ask_y(k, &Ay[k].v1, &Ay[k].v2);
		}
		if (Ay[k].acnt == 1) {
			Ay[k].v2 = MAXB + 1;
		}
		return Ay[k];
	}
}
int BS_inc(int a, int b, bool x) {
	int m; ask A;
	while (a <= b) {
		m = (a + b) >> 1;
		A = Ask(m, x);
		if (A.acnt == 0) {
			a = m + 1;
		}
		else if (A.acnt == 2) {
			b = m - 1;
		}
		else {
			return m;
		}
	}
}
int BS_dec(int a, int b, bool x) {
	int m; ask A;
	while (a <= b) {
		m = (a + b) >> 1;
		A = Ask(m, x);
		if (A.acnt == 0) {
			b = m - 1;
		}
		else if (A.acnt == 2) {
			a = m + 1;
		}
		else {
			return m;
		}
	}
}
void Boundary() {
	LB.y = Ax[(int)(LB.x = BS_inc(-MAXB, 0, true)) ].v1;
	BB.x = Ay[(int)(BB.y = BS_inc(-MAXB, 0, false))].v1;
	RB.y = Ax[(int)(RB.x = BS_dec(0, MAXB, true))  ].v1;
	TB.x = Ay[(int)(TB.y = BS_dec(0, MAXB, false)) ].v1;
}
double FP(point p1, point p2) {
	return (p1.x * p2.y) - (p2.x * p1.y);
}
inline bool online(point p1, point p2, point p3, point p4) {
	point r1, r2;
	r1.x = p1.x - p2.x; r1.y = p1.y - p2.y;
	r2.x = p3.x - p4.x; r2.y = p3.y - p4.y;
	return fabs(FP(r1, r2)) < zero;
}
bool check(int p, int m) {
	point p1, p2, r1, r2;
	ask A;
	r1.x = p; r2.x = p + 1;
	A = Ask(p, true);
	r1.y = opt(A.v1, A.v2);
	A = Ask(p + 1, true);
	r2.y = opt(A.v1, A.v2);
	p1.x = m; p2.x = m + 1;
	A = Ask(m, true);
	p1.y = opt(A.v1, A.v2);
	A = Ask(m + 1, true);
	p2.y = opt(A.v1, A.v2);
	return !online(r1, r2, p1, p2);
}
int BS(int a, int b, int p) {
	int m;
	if (a > b || !check(p, b)) {
		return MAXB + 1;
	}
	while (a + 1 < b) {
		m = (a + b) >> 1;
		if (check(p, m)) {
			b = m;
		}
		else {
			a = m + 1;
		}
	}
	if (check(p, a)) {
		b = a;
	}
	return b;
}
void Vertex() {
	int x, x1;
	V[++N] = LB;
	opt = min;
	for (x = LB.x; x < BB.x; x = x1) {
		x1 = BS(x + 1, BB.x - 1, x);
		if (x1 == MAXB + 1) { break; }
		V[++N].x = x1;
		V[N].y = opt(Ax[x1].v1, Ax[x1].v2);
	}
	if (BB.x != LB.x || BB.y != LB.y) {
		V[++N] = BB;
	}
	for (x = BB.x; x < RB.x; x = x1) {
		x1 = BS(x + 1, RB.x - 1, x);
		if (x1 == MAXB + 1) { break; }
		V[++N].x = x1;
		V[N].y = opt(Ax[x1].v1, Ax[x1].v2);
	}
	opt = max;
	for (x = LB.x; x < TB.x; x = x1) {
		x1 = BS(x + 1, TB.x - 1, x);
		if (x1 == MAXB + 1) { break; }
		V2[++N2].x = x1;
		V2[N2].y = opt(Ax[x1].v1, Ax[x1].v2);
	}
	if (TB.x != LB.x || TB.y != LB.y) {
		V2[++N2] = TB;
	}
	for (x = TB.x; x < RB.x; x = x1) {
		x1 = BS(x + 1, RB.x - 1, x);
		if (x1 == MAXB + 1) { break; }
		V2[++N2].x = x1;
		V2[N2].y = opt(Ax[x1].v1, Ax[x1].v2);
	}
	if ((BB.x != RB.x || BB.y != RB.y) && (TB.x != RB.x || TB.y != RB.y)) {
		V2[++N2] = RB;
	}
	for (; N2 >= 1; N2--) {
		V[++N] = V2[N2];
	}
}
void Square() {
	int i;
	double S = 0, k;
	for (i = 1; i < N; i++) {
		k = FP(V[i], V[i + 1]);
		if (k < 0) { k = -k; }
		S += k;
	}
	k = FP(V[N], V[1]);
	if (k < 0) { k = -k; }
	S += k;
	S /= 2;
	ret_area(S);
}
void solve() {
	Boundary();
	Vertex();
	Square();
	ret_n(N);
	for (int i = 1; i <= N; i++) {
		ret_vertex(V[i].x, V[i].y);
	}
}
int main() {
	init();
	solve();
	return 0;
}
