#include <iostream>
#include <cstring>
#include <string>
#include <stdlib.h>
#include <stdio.h>
//Summary:
//	以每个点进行深搜，param为第几个点（先排好序）+ 当前举个矩形的参数
//	往下一层后，先枚举4个点（如果有），用一个一个矩形进行尝试（剪枝），看用某个矩形进行覆盖（先check），可以的话，就往下一层
//	一直搜索直到now_point == n
#define INF 1000
struct Point {
	int x, y;
};
struct MyRectangle {
	int left, right, top, bottom;
};
struct PointStruct {
	MyRectangle rect;
	PointStruct() {
		rect.bottom = rect.top = rect.right = rect.left = -1;
	}
};
int point_num, rect_num;
Point point[51];

//这里用4个结构体优于4个数组，至少
PointStruct globe_point_struct[5];
int ans = INF*INF;
bool check_one(int first, int second) {
	//未被使用or未完全使用
	if (globe_point_struct[first].rect.bottom == INF ||
		globe_point_struct[first].rect.right == -INF ||
		globe_point_struct[first].rect.left == INF ||
		globe_point_struct[first].rect.top == -INF) {
		return true;
	}
	if (globe_point_struct[second].rect.bottom == INF ||
		globe_point_struct[second].rect.right == -INF ||
		globe_point_struct[second].rect.left == INF ||
		globe_point_struct[second].rect.top == -INF) {
		return true;
	}
	if (//一个的左边在另一个的右边的右边
		globe_point_struct[first].rect.left > globe_point_struct[second].rect.right ||
		//一个的右边在另一个的左边的左边
		globe_point_struct[first].rect.right < globe_point_struct[second].rect.left ||
		//一个的上面在另一个的下面的下面
		globe_point_struct[first].rect.top<globe_point_struct[second].rect.bottom ||
		//一个的下面在另一个的上面的上面
		globe_point_struct[first].rect.bottom>globe_point_struct[second].rect.top) {
		return true;
	}
	return false;
}
bool check() {
	for (int i = 1; i <= rect_num; i++) {
		for (int j = i + 1; j <= rect_num; j++) {
			if (!check_one(i, j)) {
				return false;
			}
		}
	}
	return true;
}
int get_acreage() {
	int ret_acreage = 0;
	for (int i = 1; i <= rect_num; i++) {
		if (globe_point_struct[i].rect.bottom == INF ||
			globe_point_struct[i].rect.left == INF ||
			globe_point_struct[i].rect.right == -INF ||
			globe_point_struct[i].rect.top == -INF) {
			continue;
		}
		ret_acreage += (globe_point_struct[i].rect.right - globe_point_struct[i].rect.left)*(globe_point_struct[i].rect.top - globe_point_struct[i].rect.bottom);
	}
	return ret_acreage;
}
void dfs_try_next_point(int now_point) {
	if (now_point == point_num + 1) {
		ans = min(ans, get_acreage());
		return;
	}
	for (int i = 1; i <= rect_num; i++) {

		PointStruct point_struct_backup = globe_point_struct[i];
		if (globe_point_struct[i].rect.bottom > point[now_point].y) {
			globe_point_struct[i].rect.bottom = point[now_point].y;
		}
		if (globe_point_struct[i].rect.top < point[now_point].y) {
			globe_point_struct[i].rect.top = point[now_point].y;
		}
		if (globe_point_struct[i].rect.left > point[now_point].x) {
			globe_point_struct[i].rect.left = point[now_point].x;
		}
		if (globe_point_struct[i].rect.right < point[now_point].x) {
			globe_point_struct[i].rect.right = point[now_point].x;
		}
		//debug_output();
		if (check() && get_acreage() < ans) {
			//cout << "check:" << now_point << endl;
			dfs_try_next_point(now_point + 1);
		}
		globe_point_struct[i] = point_struct_backup;
	}
}
int main() {
	cin >> point_num >> rect_num;
	for (int i = 1; i <= point_num; i++) {
		cin >> point[i].x >> point[i].y;
	}
	for (int i = 1; i <= rect_num; i++) {
		globe_point_struct[i].rect.bottom = INF;
		globe_point_struct[i].rect.left = INF;
		globe_point_struct[i].rect.right = -INF;
		globe_point_struct[i].rect.top = -INF;
	}
	dfs_try_next_point(1);
	cout << ans << endl;
	system("pause");
	return 0;
}


