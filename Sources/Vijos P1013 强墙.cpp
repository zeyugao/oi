//居然错在了判断线段相交
#ifndef _DEBUG
#pragma GCC optimize(2)

#include <sstream>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <memory>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <queue>
#include <cstring>
#include <fstream>
#include <cmath>
#include <Windows.h>
#include <iterator>
#include <set>
#include <process.h>
#include <ctime>
#include <utility>
#include <cctype>
#include <bitset>
using namespace std;
#endif // _DEBUG

#define walls(x,y) wall[get(x,y)]
int inline get(int c_x, int c_y) { return c_x * 4 + c_y; }
struct Walls { double x, y; };
Walls wall[100];
double _dis[100][100];
double f[100][100];
inline double _f(double x, double k, double b) {
	return k * x + b;
}
bool check(int x1, int y1, int x2, int y2) {
	//为什么我这么正确的用点斜式会错误
	//double k = (walls(x2, y2).y - walls(x1, y1).y) / (walls(x2, y2).x - walls(x1, y1).x);
	//double b = walls(x1, y1).y - k*walls(x1, y1).x;
	
	for (int i = x1 + 1; i < x2; i++) {
		//double fx = _f(i, k, b);
		
		//这是用Δx*k+y做的
		double fx = (walls(i, 0).x - walls(x1, 0).x) * (walls(x2, y2).y - walls(x1, y1).y) / (walls(x2, 0).x - walls(x1, 0).x) + walls(x1, y1).y;
		if ((fx >= walls(i, 0).y && fx <= walls(i, 1).y) || (fx >= walls(i, 2).y && fx <= walls(i, 3).y));
		else { return false; }
	}
	return true;
}
double getdis(int x1, int y1, int x2, int y2) {
	return sqrt((walls(x1, y1).x - walls(x2, y2).x) * (walls(x1, y1).x - walls(x2, y2).x) + (walls(x1, y1).y - walls(x2, y2).y) * (walls(x1, y1).y - walls(x2, y2).y));
}

int main() {
	int n; double t_x;
	memset(f, 127, sizeof(f));
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> t_x;
		for (int j = 0; j < 4; j++) {
			walls(i, j).x = t_x;
			cin >> walls(i, j).y;
		}
	}
	for (int i = 0; i < 4; i++) {
		walls(0, i).x = 0;
		walls(n + 1, i).x = 10;
		walls(0, i).y = walls(n + 1, i).y = 5;
		f[0][i] = 0;
	}
	
	//dp
	for (int i = 0; i < n + 1; i++)
		for (int h_1 = 0; h_1 < 4; h_1++)
			for (int j = i + 1; j <= n + 1; j++)
				for (int h_2 = 0; h_2 < 4; h_2++)
					if (check(i, h_1, j, h_2))
						if (f[j][h_2] > getdis(i, h_1, j, h_2) + f[i][h_1]) {
							f[j][h_2] = getdis(i, h_1, j, h_2) + f[i][h_1];
						}
	printf("%.2lf", f[n + 1][0]);
	return 0;
}


//AC 4个点...了 ，用dp

#define walls(x,y) wall[get(x,y)]
int inline get(int c_x, int c_y) { return c_x * 4 + c_y; }
struct Walls { double x, y; };
Walls wall[100];
double _dis[100][100];
double f[100][100];
inline double _f(double x, double k, double b) {
	return k * x + b;
}
bool check(int x1, int y1, int x2, int y2) {
	double k = (walls(x2, y2).y - walls(x1, y1).y) / (walls(x2, y2).x - walls(x1, y1).x);
	double b = walls(x1, y1).y - k * walls(x1, y1).x;
	
	for (int i = x1 + 1; i < x2; i++) {
		bool bb = false;
		for (int j = 0; j < 4; j += 2) {
			auto fx = _f(i, k, b);
			if (fx >= walls(i, j).y && fx <= walls(i, j + 1).y) { bb = true; }
		}
		if (!bb) { return false; }
	}
	return true;
}
double getdis(int x1, int y1, int x2, int y2) {
	return sqrt((walls(x1, y1).x - walls(x2, y2).x) * (walls(x1, y1).x - walls(x2, y2).x) + (walls(x1, y1).y - walls(x2, y2).y) * (walls(x1, y1).y - walls(x2, y2).y));
}

int main() {
	int n; double t_x;
	
	//double memset 只能到127？？！！
	//原来用0xffff，直接-nan.....
	memset(f, 127, sizeof(f));
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> t_x;
		for (int j = 0; j < 4; j++) {
			walls(i, j).x = t_x;
			cin >> walls(i, j).y;
		}
	}
	for (int i = 0; i < 4; i++) {
		walls(0, i).x = 0;
		walls(n + 1, i).x = 10;
		walls(0, i).y = walls(n + 1, i).y = 5;
		f[0][i] = 0;
	}
	
	//dp
	for (int i = 0; i < n + 1; i++)
		for (int h_1 = 0; h_1 < 4; h_1++)
			for (int j = i + 1; j <= n + 1; j++)
				for (int h_2 = 0; h_2 < 4; h_2++)
					if (check(i, h_1, j, h_2))
						if (f[j][h_2] > getdis(i, h_1, j, h_2) + f[i][h_1]) {
							f[j][h_2] = getdis(i, h_1, j, h_2) + f[i][h_1];
						}
	printf_s("%.2lf", f[n + 1][0]);
	system("pause");
	return 0;
}
/*
for (int i = 0; i < n+1; i++)
		for (int h_1 = 0; h_1 < 4; h_1++)
			for (int j = i; j <= n + 1; j++)
				for (int h_2 = 0; h_2 < 4; h_2++)
					if (check(i, h_1, j, h_2))
						if (f[j][h_2]>getdis(i, h_1, j, h_2) + f[i][h_1])
							f[j][h_2] = getdis(i, h_1, j, h_2) + f[i][h_1];


	//dp
	//又是细节的问题，这里j=1一开始变成j=0，样例都过不了
	/*for (int j = 1; j <= n + 1; j++)
		for (int h_2 = 0; h_2 < 4; h_2++) {
			f[j][h_2] = -1;
			for (int i = 0; i < j; i++)
				for (int h_1 = 0; h_1 < 4; h_1++) {
					if (check(i, h_1, j, h_2))
						if (f[j][h_2]>getdis(i, h_1, j, h_2) + f[i][h_1] || f[j][h_2] == -1)
							f[j][h_2] = getdis(i, h_1, j, h_2) + f[i][h_1];
				}
		}

		auto fx = _f(i, k, b);
			if ((fx >= walls(i, 0).y&&fx <= walls(i, 1).y) || (fx >= walls(i, 2).y&&fx <= walls(i, 3).y));
			else return false;*/




/*//这题爆炸了，看错了题目，没有注意到是使实数，由于后面很多都会用到假定是整数这个条件，爆炸了


#define _m(something) memset(something,0,sizeof(something))
//y[i][j][k]第i个墙壁，第j个空位，k为空的上下，0为下，1为上
int n, x[21], y[20][2][2];
double dis[500][512];
int gethash(int x, int y) {
	return x * 21 + y;
}
inline double f(int x, int k, int b) {
	return k*x + b;
}
//x1<x2,y1<y2
inline bool check(int x1, int y1, int x2, int y2) {
	double k = (y2 - y1) / (x[x2] - x[x1]);
	double b = y1 - k*x[x1];
	for (int i = x1 + 1; i < x2; i++) {
		bool b = false;
		for (int j = 0; i <= 1; j++) {
			double fx = f(x[i], k, b);
			if (fx >= y1&&fx <= y2)
				b = true;
		}
		if (!b)return false;
	}
	return true;
}
inline double Get_Dis(int x1, int y1, int x2, int y2) {
	return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
}
int main() {
	ios::sync_with_stdio(0);
	_m(x); _m(x); _m(y);
	memset(dis, 0xfffffff, sizeof(dis));
	cin>>n;
	for (int i = 1; i <= n; i++) {
		cin >> x[i];
		for (int j = 0; j <= 1; j++) {
			cin >> y[i][j][0] >> y[i][j][1];
		}
	}
	x[0] = 0; x[n + 1] = 10;
	y[0][0][0] = y[0][0][1] = y[0][1][0] = y[0][1][1] = y[n + 1][0][0] = y[n + 1][0][1] = y[n + 1][1][0] = y[n + 1][1][1] = 5;
	for (int i = 0; i <= n + 1; i++)
		for (int j = 0; j <= 1; j++)
			for (int k = 0; k <= 1; k++)\
				dis[gethash(i, y[i][j][k])][gethash(i, y[i][j][k])] = 0;
	for (int b = 0; b < n + 1; b++)//起始
		for (int k1 = 0; k1 <= 1; k1++)//起始的哪一个空位
			for (int u1 = 0; u1 <= 1; u1++)//起始空位的上or下
				for (int e = b + 1; e <= n + 1; e++)//结束
					for (int k2 = 0; k2 <= 1; k2++)//结束的哪一个空位
						for (int u2 = 0; u2 <= 1; u2++)//结束空位的上or下
							if (check(b, y[e][k1][u1], e, y[e][k2][u2]))
								dis[gethash(b, y[e][k1][u1])][gethash(e, y[e][k2][u2])] = Get_Dis(b, y[e][k1][u1], e, y[e][k2][u2]);
	for (int b = 0; b < n + 1; b++)//起始
		for (int k1 = 0; k1 <= 1; k1++)//起始的哪一个空位
			for (int u1 = 0; u1 <= 1; u1++)//起始空位的上or下
				for (int e = b + 1; e <= n + 1; e++)//结束
					for (int k2 = 0; k2 <= 1; k2++)//结束的哪一个空位
						for (int u2 = 0; u2 <= 1; u2++)//结束空位的上or下
							for (int k = 0; k <= n + 1; k++)
								for (int k3 = 0; k3 <= 1; k3++)
									for (int u3 = 0; u3 <= 1; u3++)
										if (dis[gethash(b, y[b][k1][u1])][gethash(k, y[k][k3][u3])] + dis[gethash(k, y[k][k3][u3])][gethash(e, y[e][k2][u2])]<dis[gethash(b, y[b][k1][u1])][gethash(e, y[e][k2][u2])])
											dis[gethash(b, y[b][k1][u1])][gethash(e, y[e][k2][u2])] = dis[gethash(b, y[b][k1][u1])][gethash(k, y[k][k3][u3])] + dis[gethash(k, y[k][k3][u3])][gethash(e, y[e][k2][u2])];
	printf_s("%.2lf", dis[gethash(0, y[0][0][0])][gethash(n + 1, y[n + 1][0][0])]);
	system("pause");
	return 0;
}


//为什么还是不行，思想是对的呀，再来
#define walls(x,y) wall[get(x,y)]
#define dis(x1,y1,x2,y2) _dis[get(x1,y1)][get(x2,y2)]
int inline get(int c_x, int c_y) { return c_x * 40 + c_y; }
struct Walls { double x, y; };
Walls wall[1000];
double _dis[1000][1000];
inline double f(double x, double k, double b) {
	return k*x + b;
}
bool check(int& x1, int& y1, int &x2, int& y2) {
	double k = (walls(x2, y2).y - walls(x1, y1).y) / (walls(x2, y2).x - walls(x1, y1).x);
	double b = walls(x1, y1).y - k*walls(x1, y1).x;

	for (int i = x1+1; i < x2; i++) {
		bool b = false;
		for (int j = 0; j < 4; j += 2) {
			auto fx = f(i, k, b);
			if (fx >= walls(i, j).y&&fx <= walls(i, j + 1).y)b = true;
		}
		if (!b)return false;
	}
	return true;
}
double getdis(int x1, int y1, int x2, int y2) {
	return sqrt((walls(x1, y1).x - walls(x2, y2).x)*(walls(x1, y1).x - walls(x2, y2).x) + (walls(x1, y1).y - walls(x2, y2).y)*(walls(x1, y1).y - walls(x2, y2).y));
}
int main() {
	int n; double t_x;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> t_x;
		for (int j = 0; j < 4; j++) {
			walls(i, j).x = t_x;
			cin >> walls(i, j).y;
		}
	}
	for (int i = 0; i < 4; i++) {
		walls(0, i).x = 0;
		walls(n + 1, i).x = 10;
		walls(0, i).y = walls(n + 1, i).y = 5;
	}
	for (int b = 0; b < n + 1; b++)
		for (int j1 = 0; j1 < 4; j1++)
			for (int e = b + 1; e <= n + 1; e++)
				for (int j2 = 0; j2 < 4; j2++)
					if (check(b, j1, e, j2))
						dis(b, j1, e, j2) = getdis(b, j1, e, j2);
					else
						dis(b, j1, e, j2) = 0xfffffff;

	for (int b = 0; b <= n + 1; b++)
		for (int j1 = 0; j1 < 4; j1++)
			for (int e = 0; e <= n + 1; e++)
				for (int j2 = 0; j2 < 4; j2++)
					for (int k = 0; k <= n + 1; k++)
						for (int j3 = 0; j3 < 4; j3++)
							if (dis(b, j1, k, j3) + dis(k, j3, e, j2) < dis(b, j1, e, j2))
								dis(b, j1, e, j2) = dis(b, j1, k, j3) + dis(k, j3, e, j2);
	printf_s("%.2lf", dis(0, 0, n + 1, 0));
	system("pause");
	return 0;
}

*/
