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
//	动态规划
//	dp[i][j]，表示当放到第i块水晶的时候，二者的高度差为j，这时候较矮的塔的高度
//
int main() {
	int crystal_num;
	int crystal_height[110] = {0};
	int sum[110] = {0};
	
	cin >> crystal_num;
	for (int i = 1; i <= crystal_num; i++) {
		cin >> crystal_height[i];
		sum[i] = sum[i - 1] + crystal_height[i];
	}
	
	int dp[110][2010];
	
	memset(dp, -0xf, sizeof(dp));
	
	dp[0][0] = 0;
	dp[1][crystal_height[1]] = 0;
	
	for (int i = 1; i <= crystal_num; i++) {
		for (int j = 0; j <= sum[i]; j++) {
			//不放任何一个塔
			dp[i][j] = (std::max)(dp[i][j], dp[i - 1][j]);
			//放其中一个塔上
			
			//放在了矮的塔上
			//这时候，默认的就是当前较矮的的塔就是原来较矮的塔
			//差距缩小了
			dp[i][j] = (std::max)(dp[i][j], dp[i - 1][j + crystal_height[i]] + crystal_height[i]);
			
			//这时候的差距j可能是因为放在了高塔，导致差距增大
			// <==> 差距 > 当前水晶的长度
			//也有可能是因为放在了矮塔，然后导致矮塔高过了高塔
			// <==> 差距 < 当前水晶的长度
			if (j >= crystal_height[i]) {
				dp[i][j] = (std::max)(dp[i][j], dp[i - 1][j - crystal_height[i]]);
			}
			else {
				dp[i][j] = (std::max)(dp[i][j], dp[i - 1][crystal_height[i] - j/*原来的差距*/] + crystal_height[i] - j);
			}
		}
	}
	
	if (dp[crystal_num][0] <= 0) {
		cout << "Impossible" << endl;
	}
	else {
		cout << dp[crystal_num][0] << endl;
	}
	return 0;
}
