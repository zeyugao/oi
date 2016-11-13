// Olympiad-in-Informatics-Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int ok[10010] = { 0 };
int s, t;
int n, m;
vector<int> g[10011], gl[10011];
void predfs(int n) {
	if (ok[n]) return;
	ok[n] = 1;
	for (int i = 0; i < gl[n].size(); i++) {
		predfs(gl[n][i]);
	}
}
void make_enable() {
	//需要用chg数组记录，不能直接改，这里只需要修改相连的点即可，避免多次修改
	int chg[10011] = { 0 };
	for (int i = 1; i <= n; i++) {
		if (ok[i] == 0)
			for (int j = 0; j < gl[i].size(); j++) {
				chg[gl[i][j]] = 1;
			}
	}
	for (int i = 1; i <= n; i++) {
		if (chg[i])
			ok[i] = 0;
	}
}
int d[10010];
void spfa() {
	//一开始spfa打错了，样例都过不了，什么回事，
	//以后打这种代码得要开git储存
	memset(d, 0x3f, sizeof(d));
	queue<int> q;
	q.push(s);
	d[s] = 0;
	int inque[10011] = { 0 };
	inque[s] = 1;
	int t;
	while (!q.empty()) {
		t = q.front(); q.pop(); inque[t] = 0;
		for (int i = 0; i < g[t].size(); i++) {
			int to = g[t][i];
			if (d[t] + 1 < d[to]) {
				d[to] = d[t] + 1;
				if (!inque[to] && ok[to]) {
					q.push(to);
					inque[to] = 1;
				}
			}
		}
	}

}
int main() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int f, t;
		cin >> f >> t;
		g[f].push_back(t);
		gl[t].push_back(f);
	}
	cin >> s >> t;
	predfs(t);
	make_enable();
	spfa();
	if (d[t] < 1061109567) {
		cout << d[t] << endl;
	}
	else
		cout << "-1" << endl;
	return 0;
}