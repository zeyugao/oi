#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>

using std::cin;
using std::endl;
using std::cout;

//Summary
//	区间dp
//	dp[i][j][0/1]表示除了i~j部分的没有完成，其他的都完成了
//		这时候，需要完成的是i(0),j(1)
//	大区间推小区间
struct TeachersRoom {
	int X,	//办公室的坐标
		T;	//开放时间
}teachers_room[1010];

bool ComapreFunc(TeachersRoom a, TeachersRoom b) {
	return a.X < b.X;
}
int main() {
	std::ios_base::sync_with_stdio(false);


	int C,	//选修了几门课程
		H,	//走廊的长度
		B;	//车站的坐标

	cin >> C >> H >> B;
	for (int i = 1; i <= C; i++) {
		cin >> teachers_room[i].X >> teachers_room[i].T;
	}
	(std::sort)(teachers_room + 1, teachers_room + C + 1, ComapreFunc);

	int dp[1010][1010][2];
	memset(dp,0xf, sizeof(dp));
cout<<dp[1]<<endl;
	//初始化中，已经将她从起点走到该位置的时间算入
	dp[1][C][0] = (std::max)(teachers_room[1].X, teachers_room[1].T);
	dp[1][C][1] = (std::max)(teachers_room[C].X, teachers_room[C].T);

	for (int i = 1; i <= C; i++) {
		for (int j = C; j >= i; j--) {
			//状态方程走完，代表i(0),j(1)是完成了的

			//从i-1=>i或者j+1=>i
			dp[i][j][0] = (std::min)(dp[i][j][0],
				//走到哪里的时间，可能还没有开门
				(std::max)(dp[i - 1][j][0] + teachers_room[i].X - teachers_room[i - 1].X, teachers_room[i].T));
			dp[i][j][0] = (std::min)(dp[i][j][0],
				(std::max)(dp[i][j + 1][1] + teachers_room[j + 1].X - teachers_room[i].X, teachers_room[i].T));

			//从i-1=>j或者j+1>j
			dp[i][j][1] = (std::min)(dp[i][j][1],
				(std::max)(dp[i - 1][j][0] + teachers_room[j].X - teachers_room[i - 1].X, teachers_room[j].T));
			dp[i][j][1] = (std::min)(dp[i][j][1],
				(std::max)(dp[i][j + 1][1] + teachers_room[j + 1].X - teachers_room[j].X, teachers_room[j].T));
		}
	}
	int ans = 0xffff;
	for (int i = 1; i <= C; i++) {
		ans = (std::min)(ans, (std::min)(dp[i][i][0], dp[i][i][1]) + (std::abs)(B - teachers_room[i].X));
	}
	cout << ans << endl;
	return 0;
}