#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>

char num_str[41];
int GetNum(int b, int e) {
	int ret = num_str[b - 1] - '0';
	
	for (int i = b; i <= e - 1; i++) {
		ret = ret * 10 + num_str[i] - '0';
	}
	return ret;
}

//Summary:
//	dp[i][j] 前i个数字加入i个乘号
//	dp[i][j] = max{dp[t][j-1] * GetNum(t+1,i)} j<=t<i
int main() {

	int num, k_part;
	std::cin >> num >> k_part;
	
	std::cin >> num_str;
	
	int dp[41][41] = { 0 };
	
	int str_len = strlen(num_str);
	
	//不加任何乘号的预处理
	for (int i = 1; i <= str_len; i++) {
		dp[i][0] = GetNum(1, i);
	}
	
	for (int i = 1; i <= str_len; i++) {
		for (int k = 1; k <= (std::min)(k_part, i - 1); k++) {
			for (int t = k; t < i; t++) {
				dp[i][k] = (std::max)(dp[i][k], dp[t][k - 1] * GetNum(t + 1, i)); //是用了k-1个乘号，所以是从k开始而不是k+1
			}
		}
	}
	std::cout << dp[str_len][k_part];
	//system("pause");
	return 0;
}