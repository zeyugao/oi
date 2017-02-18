#include <iostream>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>

using namespace std;

struct Trash {
	int live;
	int time;
	int height;
};

bool cmp(Trash a, Trash b) {
	return a.time < b.time;
}

//Summary:
//	dp[i][j]:第i个垃圾堆到高度为j时的最大生命值
//	dp[i][j] = max{	dp[i][j],
//					dp[i-1][j] - (time[i] - time[i-1] + live[i]),	//吃掉第i个垃圾
//					dp[i-1][j - height[i]] - (time[i] - time[i-1])}	//不吃第i个垃圾

int main() {
	int depth;
	int trash_num;
	Trash trash[101] = { 0 };

	cin >> depth >> trash_num;

	int max_height = 0;

	for (int i = 1; i <= trash_num; i++) {
		cin >> trash[i].time >> trash[i].live >> trash[i].height;
		max_height += trash[i].height;
	}

	sort(trash + 1, trash + trash_num + 1, cmp);

	int dp[101][2501];
	memset(dp, -1, sizeof(dp));
	dp[0][0] = 10;

	for (int i = 1; i <= trash_num; i++) {
		for (int j = 0; j <= max_height; j++) {
			if (dp[i - 1][j] - (trash[i].time - trash[i - 1].time) >= 0) {//确保还有生命值，保证在吃第i个垃圾的时候还有剩余时间
				dp[i][j] = max(dp[i][j], dp[i - 1][j] - (trash[i].time - trash[i - 1].time) + trash[i].live);
			}
			if (j - trash[i].height >= 0) {//确保不访问负地址
				dp[i][j] = max(dp[i][j], dp[i - 1][j - trash[i].height] - (trash[i].time - trash[i - 1].time));
			}
			if (dp[i][j] >= 0 && j >= depth) {
				cout << trash[i].time;
				//不管是吃了还是没吃垃圾导致的dp[i][j]>=0，都在前面判断过了
				//如果到达不了这个状态，前面第一个判断可以将dp[i][j]<0的情况保持到现在
				//为什么一定是某个trash的time，如果这个的trash没丢下来，并且还够不到洞顶，那么一定要在这个垃圾丢下来后才可以到达洞顶
				//而堆垃圾不消耗时间，那么，当这个垃圾丢下来
				return 0;
			}
		}
	}

	//如果上述操作成功完成，这返回，否则说明返回到洞顶
	//把所有的垃圾都拿来吃

	int life = 10;//剩余生命
	for (int i = 1; i <= trash_num; i++) {
		if (life - (trash[i].time - trash[i - 1].time) < 0) {//吃不到第i个垃圾了
			cout << life + trash[i - 1].time;
			return 0;
		}
		life = life - (trash[i].time - trash[i - 1].time) + trash[i].live;
	}
	cout << life + trash[trash_num].time;//吃完了还有剩余时间
	return 0;
}



#include <iostream>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>

using namespace std;

struct Trash {
	int live;
	int time;
	int height;
};

bool cmp(Trash a, Trash b) {
	return a.time < b.time;
}

//Summary:
//	dp[i][j]：高度为i，生命值为j的状态能否达到
//	dp[i+height[t]][j] = dp[i][j]
//	dp[i][j+live[t] = dp[i][j]

int main() {
	int depth;
	int trash_num;
	Trash trash[101] = { 0 };

	cin >> depth >> trash_num;

	int max_height = 0;
	int max_live = 10;
	for (int i = 1; i <= trash_num; i++) {
		cin >> trash[i].time >> trash[i].live >> trash[i].height;
		max_height += trash[i].height;
		max_live += trash[i].live;
	}
	
	sort(trash + 1, trash + trash_num + 1, cmp);
	bool dp[2501][3001] = { 0 };
	dp[0][10] = true;
	for (int current_trash_no = 1; current_trash_no <= trash_num; current_trash_no++) {
		for (int i = depth - 1; i >= 0; i--) {
			for (int j = max_live; j >= trash[current_trash_no].time; j--) {//小于当前判断的垃圾的丢下时间的状态一定不会存在
				if (dp[i][j]) {
					dp[i + trash[current_trash_no].height][j] = true;//更新状态：堆了这个垃圾，高度增加，剩余时间不变

					//当堆了第current_trash_no个垃圾后，可以到达洞顶
					//时间也是第current_trash_no个垃圾扔下的时间
					if (i + trash[current_trash_no].height >= depth) {
						cout << trash[current_trash_no].time;
						return 0;
					}

					dp[i][j + trash[current_trash_no].live] = true;//更新状态：吃了了这个垃圾，高度不变，剩余时间增加
				}
			}
		}
	}
	for (int i = max_live; i >= 1; i--) {
		if (dp[0][i]) {
			cout << i;
			return 0;
		}
	}
	return 0;
}