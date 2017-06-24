/*由于后一个人按最佳策略取数,所以他必将取一个最大值f(i+1,j)或f(i,j-1),那么此时取数的人以后取得的数将是sum(i+1,j)-f(i+1,j)或是sum(i,j-1)-f(i,j-1),此时取数的人按最佳策略取数,他会取Qi或者Qj使得sum(i+1,j)-f(i+1,j)+Qi和sum(i,j-1)-f(i,j-1)+Qj二者能有较大值.这样从游戏的结束向游戏的开始推,可以得到总的最优解.
*/
#include <iostream>
#define Len 1501
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	int n, begin, number[Len] = {0}, dp[Len][Len], sum[Len][Len];
	cin >> n >> begin;
	for (int i = 1; i <= n; i++) {
		cin >> number[i];
		dp[i][i] = number[i];
		sum[i][i] = number[i];
	}
	for (int i = n - 1; i >= 1; i--) {
		for (int j = i + 1; j <= n; j++) {
			sum[i][j] = sum[i][j - 1] + number[j];
			
			dp[i][j] = max(sum[i + 1][j] - dp[i + 1][j] + number[i], sum[i][j - 1] - dp[i][j - 1] + number[j]);
		}
	}
	
	if (begin == 1) {
		cout << dp[1][n] << endl;
	}
	else {
		cout << sum[1][n] - dp[1][n] << endl;
	}
	return 0;
}
