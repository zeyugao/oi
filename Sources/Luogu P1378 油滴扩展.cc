#include <iostream>
#include <string>
#include <algorithm>
#include <cstdio>
#include <string.h>
#include <cmath>

using std::cout;
using std::cin;
using std::endl;
using std::string;

#define DEBUG(x) //cout<<#x<<" "<<x <<endl

int n;
int rect_x, rect_y, rect_x_a, rect_y_a;

double pi = 3.141592653589;
double ans = 0.0;
#define INF  10e9;

struct Point {
	int x, y;
} point[7] = {0};
int my_index[7] = {0};

struct Circle {
	int x, y;
	double radius;
} circle[7];

inline double GetCenterDistance(int x, int y, int circle_index) {
	return sqrt((x - circle[circle_index].x) * (x - circle[circle_index].x) + (y - circle[circle_index].y) * (y - circle[circle_index].y));
}

double GetMinDistance(int x, int y, int pre_num) {
	double min_distance = INF;
	DEBUG(min_distance);
	//求到边的最短距离
	min_distance = (std::min)(min_distance, (double)(std::min)(abs(x - rect_x), abs(x - rect_x_a)));
	DEBUG(min_distance);
	min_distance = (std::min)(min_distance, (double)(std::min)(abs(y - rect_y), abs(y - rect_y_a)));
	DEBUG(min_distance);
	for (int i = 1; i <= pre_num; i++) {
		DEBUG(i);
		//该点到各个已经确定的圆的圆心的距离-该圆的半径
		min_distance = (std::min)(min_distance, GetCenterDistance(x, y, i) - circle[i].radius);
		DEBUG(min_distance);
	}
	return min_distance;
}

double GetArea() {
	double ret_area = 0.0;
	for (int i = 1; i <= n; i++) {
		DEBUG(i);
		DEBUG(point[my_index[i]].x);
		DEBUG(point[my_index[i]].y);
		double min_radious = GetMinDistance(point[my_index[i]].x, point[my_index[i]].y, i - 1);
		circle[i].x = point[my_index[i]].x;
		circle[i].y = point[my_index[i]].y;
		circle[i].radius = min_radious;
		if (min_radious >= 0) {
			ret_area += min_radious * min_radious * pi;
		}
	}
	return ret_area;
}

int main() {

	cin >> n;
	cin >> rect_x >> rect_y >> rect_x_a >> rect_y_a;
	for (int i = 1; i <= n; i++) {
		my_index[i] = i;
		
		cin >> point[i].x >> point[i].y;
	}
	
	do {
		memset(circle, 0, sizeof(circle));
		ans = (std::max)(GetArea(), ans);
	}
	while (std::next_permutation(my_index + 1, my_index + n + 1));
	
	cout << (int)(abs(rect_y - rect_y_a)*abs(rect_x - rect_x_a) - ans + 0.5) << endl;
	return 0;
}