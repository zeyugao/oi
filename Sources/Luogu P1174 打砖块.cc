#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>

using std::cin;
using std::endl;
using std::cout;

//Summary:
//	dp+预处理
//	预处理：预处理出第i列打了j发子弹，所能获得的最大分数
//		pre[i][j][t]：
//			t=1，要往后借一颗子弹
//
//	dp：
//		dp[i][j][t]：
//			前i列打了j颗子弹所能获得的最大分数，
//			t=1，要往后借一颗子弹
//
//	借子弹的理解：借子弹，就说明是一定要能够还回去的咯！
//	那就是，在某一行，如果打了j发子弹，并且当第j发子弹打完以后，就出现了Y，
//		那么，想要打但又没有子弹了，这时候，往后借一颗子弹就可以继续打，
//		并且，由于是Y，可以获得奖励，那么当打完了借来的子弹后，就可以获得奖励换回去，
//		仍然打了j发子弹，但就可以多获得一些分数
//
//
//比较神奇，怎么想到用这种预处理了
//两个状态的使用以及推导要考虑细节
int main() {
	int row_num, col_num, bullet_num;
	int score[210][210] = { 0 };
	char reward[210][210] = { 0 };
	
	cin >> row_num >> col_num >> bullet_num;
	
	for (int i = 1; i <= row_num; i++) {
		for (int j = 1; j <= col_num; j++) {
			scanf("%d %c", &score[i][j], &reward[i][j]);
		}
	}
	//预处理
	int pre[210][210][2] = { 0 };
	int current_calc_row;
	for (int col = 1; col <= col_num; col++) {
		current_calc_row = row_num;
		//处理bullet = 0的情况
		while (current_calc_row > 0 && reward[current_calc_row][col] == 'Y') {
			//有作为奖励的砖块在最下面，那么，就直接打就行了，不需要，花费子弹
			//当然，这是需要借一颗子弹来打的
			pre[col][0][1] += score[current_calc_row][col];
			current_calc_row--;
		}
		//计算打了bullet发子弹的情况，打的子弹不可能多过行数
		for (int bullet = 1; bullet <= row_num && current_calc_row >= 1; bullet++) {
		
			//多了一个子弹，并且不用还回去，就相当于少了一个子弹并还要还回去的分数+
			//	因为不需要还回去，可以多打一个了
			pre[col][bullet][0] = pre[col][bullet - 1][1] + score[current_calc_row][col];
			//还回去的情况，就相当于可以把后面的所有是Y的砖块都打下来
			//
			//如果后面没有Y，就相当于借不借都一样
			//由于这个是向后面借的一颗子弹，如果打的不是Y而是N的话，那么就无法得到奖励还回去了
			//唯有打的是Y，才能还回去
			pre[col][bullet][1] = pre[col][bullet][0];
			
			current_calc_row--;
			while (reward[current_calc_row][col] == 'Y' && current_calc_row >= 1) {
				//还是得要借了子弹才能打
				pre[col][bullet][1] += score[current_calc_row][col];
				current_calc_row--;
			}
		}
	}
	int dp[210][210][2] = { 0 };
	
	for (int col = 1; col <= col_num; col++) {
		for (int bullet = 0; bullet <= bullet_num; bullet++) {
			for (int bullet_current_col = 0; bullet_current_col <= row_num; bullet_current_col++) {
				if (bullet_current_col <= bullet) {
				
					//当前列需要往后借，前面的列也要往后借，那就是这一列直接往后借，打完前面的列，再打这一列，还回去
					//总体来就是当前列需要往后借
					dp[col][bullet][1] = (std::max)(dp[col][bullet][1],
													dp[col - 1][bullet - bullet_current_col][1] + pre[col][bullet_current_col][1]);
													
					if (bullet_current_col < bullet) {
						//前面的列不需要往后借，那就是打完可以获得一个子弹
						//刚好补在了当前列
						//总体来就是当前列不需要往后借
						
						//要在前面的列获得子弹，一定要有子弹打==>bullet-bullet_current_col >= 1
						dp[col][bullet][0] = (std::max)(dp[col][bullet][0],
														dp[col - 1][bullet - bullet_current_col][0] + pre[col][bullet_current_col][1]);
					}
					
					if (bullet_current_col > 0) {
						//前面的列需要往后借一颗子弹
						//这一列不需要借子弹，那就是可以获得一颗奖励的子弹
						//这一颗子弹可以补回给前面那一列
						//总体来就是不用往后借
						
						//这一列要获得一颗子弹，一定有子弹在这一列打出==>bullet_current_col > 0
						dp[col][bullet][0] = (std::max)(dp[col][bullet][0],
														dp[col - 1][bullet - bullet_current_col][1] + pre[col][bullet_current_col][0]);
					}
				}
			}
		}
	}
	cout << dp[col_num][bullet_num][0];
	return 0;
}
