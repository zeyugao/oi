// Olympiad-in-Informatics-Test.cpp : 定义控制台应用程序的入口点。
//

#include <iostream>
#include <cstring>
#include <string>
#include <stdlib.h>
#include <cmath>
#include <algorithm>
#include <Windows.h>
using namespace std;

int fa[200010], dis[200010], ans = 0xfffffff;

int Find(int x) {
	if (fa[x] == x) { return x; }
	int temp = fa[x];
	fa[x] = Find(fa[x]);
	dis[x] += dis[temp];
	return fa[x];
}
void Union(int x, int y) {
	int fx = Find(x), fy = Find(y);
	if (fx != fy) {
		fa[fx] = fy;
		dis[x] = dis[y] + 1;
	}
	else {
		ans = min(ans, dis[x] + dis[y] + 1);
	}
}

int main() {
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) { fa[i] = i; }
	for (int i = 1; i <= n; i++) {
		int ti;
		cin >> ti;
		Union(i, ti);
		
	}
	cout << ans;
	//system("pause");
	return 0;
}
