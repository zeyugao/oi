#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>

using std::cin;
using std::endl;
using std::cout;

const int kMaxNum = 5005;

int dp[kMaxNum][210];
int volume[210];
int value[210];

//动归时进行合并的辅助变量
int dp_a[210];
int dp_b[210];

int main() {
	//根据名称显而易见的变量
	int capacity;	//容量
	int peo_num;	//人数
	int object_num;	//物件数
	
	
	cin >> peo_num >> capacity >> object_num;
	
	for (int i = 1; i <= object_num; i++) {
		cin >> volume[i] >> value[i];
	}
	
	//将dp数组赋为负值代表无法填满
	for (int i = 0; i <= capacity; i++) {
		for (int j = 1; j <= peo_num; j++) {
			dp[i][j] = -kMaxNum;
		}
	}
	
	dp[0][1] = 0;
	dp_a[peo_num + 1] = dp_b[peo_num + 1] = -1;
	
	for (int i = 1; i <= object_num; i++) {
		for (int j = capacity; j >= volume[i]; j--) {
			if (dp[j - volume[i]][1] > -1) {//还没有填满
				for (int k = 1; k <= peo_num; k++) {
					dp_a[k] = dp[j][k];
					dp_b[k] = dp[j - volume[i]][k] + value[i];
				}
				
				int current_pos = 1;
				int pos_a = 1;
				int pos_b = 1;
				
				while (current_pos <= peo_num &&
						//任意一个数没有到边界
						(dp_a[pos_a] != -1 || dp_a[pos_b] != -1)) {
					if (dp_a[pos_a] > dp_b[pos_b]) {
						dp[j][current_pos] = dp_a[pos_a];
						pos_a++;
					}
					else {
						dp[j][current_pos] = dp_b[pos_b];
						pos_b++;
					}
					//判重
					//由于权值相同（只要求不完全相同），不需要判重
					//if (dp[j][current_pos] != dp[j][current_pos - 1]) {
					current_pos++;
					//}
				}
			}
		}
	}
	
	int ans = 0;
	for (int i = 1; i <= peo_num; i++) {
		ans += dp[capacity][i];
	}
	cout << ans << endl;
	return 0;
}
