//http://www.lai18.com/content/2171691.html
/*
悬线法，时间复杂度为O(nm)（还有一种扫描法，时间复杂度为O(S^2)，S为障碍点个数，二者空间相同，可以分情况使用）

一开始我用的是标程的方法，把sum,l,r,maxl,maxr,height全部预处理出来。听OJ讲了之后，把那种方法和OJ的方法取长补短，总时间快了1s之多、空间少了一半

只预处理sum。l,r都只需要存储当前行的，maxl和maxr01滚动，height就地滚动（绝对位置）。需要注意的是，递推的时候如果不是障碍点，最左边能到达为l[j]和max[i-1,j]的最大值，最右边类似。如果是障碍点，则最把他maxl设为0，maxr设为m+1。因为到了下一行的时候，悬线高度变成1，maxl和maxr只由这一行决定，而和上一行无关，因此把上一行设为极值。

OJ的方法有一点不同的是对于maxl和maxr的处理方式，没有用递推的方法，而是向左右扫描的第一根比这一根悬线短的。我没有采用。
*/
#include <cstdio>

#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))

long n; long m;
long num[1010][1010];
long sum[1000][1010];
long l[1010];
long r[1010];
long maxl[2][1010];
long maxr[2][1010];
long height[1010];

int main() {
	freopen("candy_box.in", "r", stdin);
	freopen("candy_box.out", "w", stdout);
	scanf("%ld%ld", &n, &m);
	
	for (long i = 1; i < n + 1; i++)
		for (long j = 1; j < m + 1; j++) {
			scanf("%ld", num[i] + j);
			sum[i][j] = num[i][j] + sum[i][j - 1];
		}
		
	for (long i = 1; i < n + 1; i++)
		for (long j = 1; j < m + 1; j++) {
			sum[i][j] += sum[i - 1][j];
		}
		
	long ans = 0;
	
	for (long j = 1; j < m + 1; j++) {
		maxl[0][j] = 0;
		maxr[0][j] = m;
	}
	
	for (long i = 1; i < n + 1; i++) {
		//i&1 是滚动操作，减少空间复制度
		for (long j = 1; j < m + 1; j++) {
			maxl[i & 1][j] = maxr[i & 1][j] = 0;
		}
		
		l[0] = 0;
		r[m + 1] = m;
		
		for (long j = 1; j < m + 1; j++) {
			if (num[i][j]) {
				l[j] = l[j - 1];
				maxl[i & 1][j] = MAX(l[j], maxl[(i & 1) ^ 1][j]);
			}
			else {
				height[j] = i;
				
				l[j] = j;
				maxl[i & 1][j] = -1;
			}
		}
		
		for (long j = m; j > 0; j--) {
			if (num[i][j]) {
				//这里之所以用r[j]=j-1而前面的是l[j]=j;是因为在最后减去的时候，会把j列的也算上，一并减去，而r的不会
				r[j] = r[j + 1];
				maxr[i & 1][j] = MIN(r[j], maxr[(i & 1) ^ 1][j]);
			}
			else {
				r[j] = j - 1;
				maxr[i & 1][j] = m + 1;
			}
		}
		
		for (long j = 1; j < m + 1; j++)
			//看同名图片解析
		{
			ans = MAX(ans, sum[i][maxr[i & 1][j]] + sum[height[j]][maxl[i & 1][j]] - sum[height[j]][maxr[i & 1][j]] - sum[i][maxl[i & 1][j]]);
		}
	}
	
	printf("%ld", ans);
}
