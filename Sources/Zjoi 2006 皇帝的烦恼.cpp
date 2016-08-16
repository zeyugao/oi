#include<cstdio>

#define maxn 100001
int n;

inline int in()
{
	int x = 0; char ch = getchar();
	while (ch<'0' || ch>'9')ch = getchar();
	while (ch <= '9'&&ch >= '0')x = x * 10 + ch - '0', ch = getchar();
	return x;
}
//f[i]表示和1存在相同勋章个数的最小值，g[i]表示最大值
int a[maxn + 1], f[maxn], g[maxn], n;


//判断ans是否能让全部将军都满意
bool judge(int ans)
{
	f[1] = a[1]; g[1] = a[1];
	for (int i = 2; i <= n; i++)
	{
		//任意相邻两个人的要求>ans，一定不可以
		if (a[i] + a[i - 1] > ans)return 0;

		//与1存在相同勋章的个数，要么是1有勋章的个数-前一个与1有相同勋章的个数的最大值
		//（i与1的相同个数与i-1与1的相同个数应该等于1的个数，如果小于，说明1中存在还有元素没有分配到i与i-1中，不可能为最优解，所以当i-1与1的相同个数最多的时候，i与1的相同个数最少），
		//或者是i与1全部相同
		//这是要求最小值
		f[i] = min(a[1] - g[i - 1], a[i]);

		//要么是一个都不相同，相同个数为0
		//ans-a[i-1]=给第i-1个将军后，剩下多少个
		//a[1]-f[i-1]=1与i（暂时）最多有这么多个相同

		//要求i与1最多有多少个相同，就是要求
		g[i] = max(0, a[i] - (ans - a[i - 1] - (a[1] - f[i - 1])));
		if (f[i] < g[i])return 0;
	}
	return g[n] == 0;
}

int main()
{
	int l = 1, r = 0, ans;
	n = in();
	for (int i = 1; i <= n; i++)a[i] = in(), r += a[i], r = min(r, 250000);
	while (l <= r)
	{
		int mid = (l + r) >> 1;
		//judge==0：ans不能让将军满意，需要扩大范围
		//judge==1：可以让将军满意，通过二分缩小能让其满意的范围
		if (judge(mid))r = mid - 1, ans = mid;
		else l = mid + 1;
	}
	printf("%d", ans);
	return 0;
}