/*政府在某山区修建了一条道路，恰好穿越总共m个村庄的每个村庄一次，没有回路或交叉，任意两个村庄只能通过这条路来往。
已知任意两个相邻的村庄之间的距离为di（为正整数），其中，0 < i < m。为了提高山区的文化素质，
政府又决定从m个村中选择n个村建小学（设 0 < n < = m < 500 ）。请根据给定的m、n以及所有相邻村庄的距离，
选择在哪些村庄建小学，才使得所有村到最近小学的距离总和最小，计算最小值。*/

/*
状态：f[i][j] 前i个村庄已经建了j个学校
转移：f[i][j]=min（f[i][j],f[ii][j-1]+s[ii+1][i]） 1<=ii<=i-1
*/
using namespace std;
int n, m, a[505], h[505], s[505][505], f[505][505], ans;
int Dfs(int nn, int mm) {
	int i, j, k;
	if (f[nn][mm] < 0x3f3f3f3f) { return f[nn][mm]; } //记忆化(如果10000000 会TLE)
	if (nn <= mm) { return f[nn][mm] = 0; } //每个村都可以建 返回0
	if (mm == 1) { return f[nn][mm] = s[1][nn]; } //只建一个 返回最大（此时建在中点）
	for (i = 1; i <= nn - 1; i++) {
		f[nn][mm] = min(f[nn][mm], Dfs(i, mm - 1) + s[i + 1][nn]);
	}
	// 转移式表示在区间i+1..nn的中点建立一所学校使这个区间内的所有村庄都到这里上学，其中s为最小距离之和。
	//可以转化为两重for循环，但由于有一些判断不好写，采用DFS方式
	return f[nn][mm];
}
int main() {
	int i, j, k, mm;
	cin >> n >> m;
	for (i = 1; i <= n - 1; i++) {
		cin >> a[i];
	}
	for (i = 1; i <= n; i++) {
		h[i] = h[i - 1] + a[i - 1];    //前缀和
	}
	memset(f, 0x3f, sizeof(f));
	for (i = 1; i <= n; i++)
		for (j = i; j <= n; j++) {
			mm = (i + j) / 2;
			for (k = i; k <= j; k++) {
				s[i][j] += abs(h[mm] - h[k]);    //i-->j建一个学校最少路程和（默认建在（i+j）/2处）
			}
		}
	ans = Dfs(n, m);
	cout << ans;
	return 0;
}