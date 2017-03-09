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
int main(){

	int row_num,col_num,bullet_num;
	int score[210][210]={0};
	int reward[210][210] ={0};

	for(int i = 1;i<=row_num;i++){
		for(int j = 1;j<=col_num;j++){
			char reward_tmp;
			scanf("%d %c",score[i][j],reward_tmp);
			if(reward_tmp == 'Y'){
				reward[i][j] = 1;
			}
			else{
				reward[i][j] = 0;
			}
		}
	}

	//预处理
	int pre[210][210][2]={0};
	int current_calc_row;
	for(int col=1;col<=col_num;col++){
		current_calc_row = row_num;
		//处理bullet = 0的情况
		while(reward[current_calc_row][col]){
			//有作为奖励的砖块在最下面，那么，就直接打就行了，不需要，花费子弹
			pre[col][0][0] += score[current_calc_row][col];
			current_calc_row--;
		}
		//计算打了bullet发子弹的情况，打的子弹不可能多过行数
		for(int bullet = 1;bullet <= row_num&&current_calc_row >=1;bullet++){
			pre[col][bullet][0] = pre[col][bullet-1][0] + score[current_calc_row][col];

			//如果后面没有Y，就相当于借不借都一样
			//由于这个是向后面借的一颗子弹，如果打的不是Y而是N的话，那么就无法得到奖励还回去了
			//唯有打的是Y，才能还回去
			pre[col][bullet][1] = pre[col][bullet][0];

			current_calc_row--;
			while(reward[current_calc_row][col] == 1&& current_calc_row >=1){
				pre[col][bullet][1] += score[current_calc_row][col];
				current_calc_row--;
			}
		}
	}

	int dp[210][210][2]={0};

	memset(dp,-111,sizeof(dp));

	for(int col=1;col<=col_num;col++){
		for(int bullet = 0;bullet <= bullet_num;bullet++){
			for(int bullet_current_col;bullet_current_col<= row_num;bullet_current_col++){
				if(bullet_current_col<= bullet){

					//当前列需要往后借，前面的列也要往后借，那就是这一列直接往后借，打完前面的列，再打这一列，还回去
					//总体来就是当前列需要往后借
					dp[col][bullet][1] = (std::max)(dp[col][bullet][1],
						dp[col-1][bullet-current_calc_row][1] + pre[col][current_calc_row][1]);

					if(bullet_current_col<bullet){
							//前面的列不需要往后借，那就是打完可以获得一个子弹
							//刚好补在了当前列
							//总体来就是当前列不需要往后借

							//要在前面的列获得子弹，一定要有子弹打==>bullet-bullet_current_col >= 1
							dp[col][bullet][0] = (std::max)(dp[col][bullet][0],
								dp[col-1][bullet - bullet_current_col][0] + pre[col][current_calc_row][1]);
					}

					if(current_calc_row>0){
						//
						dp[col][bullet][0] = (std::max)(dp[col][bullet][0],
							dp[col-1][bullet - current_calc_row][1] + pre[col][current_calc_row][0]);
					}
				}
			}
		}
	}


	return 0;
}
