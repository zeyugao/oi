/*（1）首先将各点按照x坐标从小到大排列，时间复杂度为O(nlgn)。
（2）寻找子结构：定义从Pi到Pj的路径为：从Pi开始，从右到左一直到P1，然后从左到右一直到Pj。在这个路径上，会经过P1到Pmax(i,j)之间的所有点且只经过一次。
在定义d(i,j)为满足这一条件的最短路径。我们只考虑i>=j的情况。
同时，定义dist(i,j)为点Pi到Pj之间的直线距离。
（3）最优解：我们需要求的是d(n,n)。
关于子问题d(i,j)的求解，分三种情况：
A、当j < i - 1时，d(i,j) = d(i-1,j) + dist(i - 1,i)。
由定义可知，点Pi-1一定在路径Pi-Pj上，而且又由于j<i-1,因此Pi的左边的相邻点一定是Pi-1.因此可以得出上述等式。
B、当j = i - 1时，与Pi左相邻的那个点可能是P1到Pi-1总的任何一个。因此需要递归求出最小的那个路径：
d(i,j) = d(i,i-1) = min{d(k,j) + dist(i,k)},其中1 <= k <= j。
C、当j=i时，路径上最后相连的两个点可能是P1-Pi、P2-Pi...Pi-1-Pi。
因此有：
d(i,i) = min{d(i,1)+dist(1,i),...,d(i,i-1),dist(i-1,i)}.。
*/

//双调欧几里得旅行商问题
//《算法导论（第二版）》思考题15-1
//PKU 2677

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

const int n = 7;//点的数目
const int MaxVal = 999999;
const int MaxLen = 201;

struct tagPoint{
	double x,y;
};

//计算点i和点j之间的直线距离
double distance(tagPoint *points,int i,int j)
{
	return sqrt((points[i].x - points[j].x) * (points[i].x - points[j].x) +
		(points[i].y - points[j].y) * (points[i].y - points[j].y));
}

double DP(tagPoint *points,int n)
{
	double b[MaxLen][MaxLen];//记录最短路径的长度
	//计算所有情况下的b[i][j]，1 <= i <= j
	//初始化
	b[1][2] = distance(points,1,2);
	for (int j = 3;j <= n;++j)
	{
		//i < j-1
		for (int i = 1;i <= j - 2;++i)
		{
			b[i][j] = b[i][j - 1] + distance(points,j - 1,j);
		}
		//i = j - 1,b[i][j] = min(b[k][j - 1] + distance(k,j));
		b[j - 1][j] = MaxVal;
		for (int k = 1;k <= j - 2;++k)
		{
			double temp = b[k][j - 1] + distance(points,k,j);
			if (temp < b[j - 1][j])
			{
				b[j - 1][j] = temp;
			}
		}
	}

	b[n][n] = b[n - 1][n] + distance(points,n - 1,n);

	return b[n][n];
}

int main()
{
	int NUM;
	while(cin >> NUM)
	{
		tagPoint *points = new tagPoint[NUM + 1];
		for (int i = 1;i <= NUM;++i)
		{
			cin >> points[i].x;
			cin >> points[i].y;
		}
		double minDis = DP(points,NUM);
		//设置输出格式：精确到小数点后2位
		cout.setf(ios::fixed);
		cout << setprecision(2) << minDis << endl;
	}
}

#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;

const int maxn = 1100;
const int inf = 0x7fffffff;
int n;
double x[maxn];
double y[maxn];
int r[maxn];
double f[maxn][maxn];

bool cmp (int a, int b) {
    return x[a] < x[b];
}

double dist (int a, int b) {
    return sqrt ((x[a] - x[b]) * (x[a] - x[b]) + (y[a] - y[b]) * (y[a] - y[b]));
}

int main ()
{
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> x[i] >> y[i];
        r[i] = i;
    }
    sort (r + 1, r + n + 1, cmp);
    for (int i = 1; i <= n - 2; i++) {
        f[n - 1][i] = dist (r[n], r[n - 1]) + dist (r[i], r[n]);
    }
    for (int i = n - 2; i > 1; i--) {
        for (int j = 1; j < i; j++) {
            f[i][j] = min (f[i + 1][j] + dist (r[i], r[i + 1]), f[i + 1][i] + dist (r[i + 1], r[j]));
        }
    }
    double ans = f[2][1] + dist (r[1], r[2]);
    cout << setprecision (2) << setiosflags (ios::fixed) << ans;
    return 0;
}