aliens

框架
1. 找出当前块的左下角
2. 找出m
3. 找出左下块

第 1, 2 步需要用到一个过程：findBorder(x, y)。它是用来求(x, y)所在块的边界的。

首先，倍增地检查如下这些格子：
(x, y), (x + 1, y), (x + 2, y), … , (x + 2^s, y), (x + 2^(s + 1), y)
设(x + 2^(s + 1), y)是第一个不在块内的格子。
这步的目的是确定边界的范围，该范围内满足一定单调性。

可以证明，这样的倍增检查序列，不会跨过一整个空块，以至于导致错误。
即不存在k，使得
x + 2^k <= m
x + 2^(k + 1)>=2m + 1
解不等式，得 x < 0
这与起始点一定在块内矛盾。

这样边界就一定在(x + 2^s, y), (x + 2^(s + 1), y)之间。二分查找即可。
#include <cstdio>
#include <cstring>
using namespace std;

int n, m;

bool examine(long long x, long long y)
{
	if (!(1 <= x && x <= n && 1 <= y && y <= n))
	return false;
	printf("examine %d %d\n", (int) x, (int) y);
	fflush(stdout);
	char response[16];
	scanf("%s", response);
	return (strcmp(response, "true") == 0);
}
long long findBorder(long long x, long long y, long long dx, long long dy)
{
	long long s = 1;
	while (examine(x + s * dx, y + s * dy))
	s *= 2;
	long long left = s / 2;
	long long right = s;
	while (left < right)
	{
		long long mid = (left + right + 1) / 2;
		if (examine(x + mid * dx, y + mid * dy))
			left = mid;
		else
			right = mid - 1;
	}
	return left;
}
int main()
{
	int x, y;
	scanf("%d%d%d", &n, &x, &y);
	x -= findBorder(x, y, -1, 0);
	y -= findBorder(x, y, 0, -1);
	m = findBorder(x, y, 1, 0) + 1;
	while (examine(x - m * 2, y))
		x -= m * 2;
	while (examine(x, y - m * 2))
		y -= m * 2;
	if (examine(x - m, y - m))
		x -= m, y -= m;
	x += m * 2 + m / 2;
	y += m * 2 + m / 2;
	printf("solution %d %d\n", x, y);
	fflush(stdout);
	return 0;
}
