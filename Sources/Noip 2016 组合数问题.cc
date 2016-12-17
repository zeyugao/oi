#include <iostream>
using namespace std;
const int maxn = 2010;
long ans[maxn + 1][maxn + 1] = { 0 };
int C[maxn + 1][maxn + 1] = { 0 };
int k;
void calc() {

	C[0][0] = 1;
	for (int i = 1; i <= maxn; i++) {
		C[i][0] = C[i][1] = C[i][i] = 1;
	}
	for (int i = 2; i <= maxn; i++) {
		for (int j = 1; j < i; j++) {
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1])%k;
		}
	}
	//out();
	for (int i = 1; i <= maxn; i++) {
		for (int j = 1; j <= maxn; j++) {
			ans[i][j] = (i >= j/*i>=j时才有组合数*/&&C[i][j] % k == 0) + ans[i - 1][j] + ans[i][j - 1] - ans[i - 1][j - 1]/*像前缀和一样，分别减去前面的*/;
			/*图:
			---*.
			---*.
			---*.
			****.
			.....

			所有的.组成ans[i][j],最下面的4个.（从左往右数）加上倒数第二列的*组成ans[i-1][j]
			倒数第二行的的4个*（从上往右下数）加上最后1列的.组成ans[i][j-1]
			所有的*组成ans[i-1][j-1]，易知ans[i][j] = ans[i-1][j]+ans[i][j] -ans[i-1][j-1]

			//复制到等距字体的编辑器下看
			*/
		}
	}
}

int main() {
	int t;
	cin >> t >> k;
	calc();
	while (t--) {
		int n, m;
		cin >> n >> m;
		//这里可以直接调用ans[n][m]是因为在上面已经通过一些方法使其可以支持
		cout << ans[n][m]<<endl;
	}
	return 0;
}