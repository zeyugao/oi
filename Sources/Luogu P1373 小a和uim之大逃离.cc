#include <iostream>
#include <string>
#include <algorithm>
#include <cstdio>

using std::cout;
using std::cin;
using std::endl;

/*  dp
    dp[i][j][k][p]
    走到(i,j)，小a与uim所吸收的魔液差值为k
    k 是 小a-uim
    此时，应该由小a此时，应该由小a(p=0)or uim(p=1)来吸收位于(i,j)位置上的魔液的方案数
*/
int n, m, k;
int map[810][810] = {0};
int dp[810][810][20][2] = {0};
const int mod = 1000000007;
int main() {
	cin >> n >> m >> k;
	//有k的容量,但是只有k的时候是不会溢出的,但是如果k不变的话,就会有问题,所以得要k++
	k++;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> map[i][j];
			dp[i][j][(map[i][j] % k)][0] = 1;
		}
	}
	//cout<<"Done"<<endl;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			for (int delta = 0; delta < k; delta++) {
			
				//现在是小a吸收魔液
				dp[i][j][delta][1] = (dp[i][j][delta][1] +
									  //吸收了map[i][j]那么多，原先就差了delta+map[i][j]这么多
									  //因为是uim吸收的，差距在变小
									  dp[i - 1][j][((delta + map[i][j]) % k + k) % k][0] +
									  dp[i][j - 1][((delta + map[i][j]) % k + k) % k][0]) % mod;
				//printf("dp[%d][%d][%d][1]=%d\n",i,j,delta,dp[i][j][delta][1]);
				
				
				dp[i][j][delta][0] = (dp[i][j][delta][0] +
									  //因为是小a吸收的，差距在变大
									  dp[i - 1][j][((delta - map[i][j]) % k + k) % k][1] +
									  dp[i][j - 1][((delta - map[i][j]) % k + k) % k][1]) % mod;
				//printf("dp[%d][%d][%d][0]=%d\n\n",i,j,delta,dp[i][j][delta][0]);
			}
		}
	}
	long long ans = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			ans = (ans + dp[i][j][0][1]) % mod;
		}
	}
	cout << ans;
	return 0;
}