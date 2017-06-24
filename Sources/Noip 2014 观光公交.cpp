/*每个人在车上的时间 等于 车到达目的站的时间 减去 这个人到达起始站的时间
由于人到达起始站的时间题目给出不会变化
所以求解一个最优的车到达目的站的时间即可
假设到达第i+1站的时间是time[i]
从前往后逐个求解到站时间
可以得出time[i] = max{time[i-1], last[i]} + d[i]
其中last[i]为从第i站上车的旅客中最后到达的一个到达的时间 可以用O(n+m)的时间预处理得出
d[i]为从i走到i+1所用的时间
很明显的 我们可以利用这个递推关系式用O(n)的时间求解time[i]
当我们令d[i]减少1时
time[1..i-1]不会变化
time[i]会减少1
考虑time[i+1]
由前面的式子得出time[i+1] = max{time[i], last[i+1]} + d[i+1]
若我们令d[i]减少之前 存在time[i] > last[i+1]则time[i+1]会减少1 否则time[i+1]就会不变
若time[i+1]减少了1 我们可以用同样的方法判断time[i+2]直到最后是否变化
若time[i+1]不变 则time[i+2]及之后的time值都不会变化
**所以 当我们令某个d[i]减少1时 从time[i]开始会有一段区间的time值均减少1
这个区间的左端为i 我们令右端为range[i]
对于j属于从i+1到range[i] 均存在time[j-1] > last[j] 且对于range[i]+1不存在time[j-1] > last[j]
说到这里 大家应该发现求解range[i]的方法了
若range[i+1] = t 则对于从i+2到t前不等式均成立且对于t+1不成立
所以我们求解range[i]只需判断对于i+1前不等式是否成立即可
若成立则 range[i] = range[i+1] 不成立则 range[i] = i
若我们修改每个值所减少的时间为reduce[i] 则reduce[i] = v[i] + v[i+1] + ... + v[range[i]]
v[i]表示到达第i+1个车站的人的数量
很明显的 reduce[i] = v[i] + reduce[i+1] 或 v[i]
现在 我们可以用O(n)的时间求解reduce了
然后每次选择一个令reduce[i]最大的i 令d[i]减少即可
注意每次修改d[i]之后 要重新计算新的time[i]
时间复杂度O(kn)
*/
program bus;
var n, m, k, i, j, tt, tz, dd, da, dz, mn: longint;
a, b, c, d, mm, num, time, yx: array[0..10000] of longint;
ans: longint;
function max(q, p: longint): longint;
	begin
	if q > p then exit(q);
	exit(p);
	end;
	function min(q, p: longint): longint;
	begin
	if q > p then exit(p);
	exit(q);
	end;
	function sum(q, p: longint): longint;
var i, ans: longint;
	begin
ans: = 0;
for i : = p + 1 to q do {
	inc(ans, num[i]);
	}
exit(ans);
end;
begin
assign(input, 'bus.in'); reset(input);
assign(output, 'bus.out'); rewrite(output);
readln(n, m, k);
for i : = 1 to n - 1 do { read(d[i]); }           //记录从i站到达i+1站所用时间
for i : = 1 to m do                           //记录每个人旅行的信息
			  begin
			  readln(a[i], b[i], c[i]);
if mm[b[i]] { < a[i] then mm[b[i]]: = a[i]; }   //统计最后一个从b[i]站上车的时间
	inc(num[c[i]]);                             //统计从c[i]站下车的人数
end;
while true do
	begin
time[1]: = 0;
for i : = 2 to n do {                      //递推到达i站的时间
time[i]: = max(time[i - 1], mm[i - 1]) + d[i - 1];
	}
yx[n]: = n;                                //判断修改i到i+1所用时间影响的范围
for i : = n - 1 downto 1 do
			  begin
		  yx[i]: = yx[i + 1];
if time[i + 1] { <= mm[i + 1] then yx[i]: = i + 1; }
	end;
tt: = 1;
while (d[tt] = 0) and (tt <= n - 1) do {
		inc(tt);
	}
if (tt = n) { or (k = 0)then break; }
for i : = tt + 1 to n - 1 do               //找出影响范围最大的(影响的人的个数)
if (d[i]<>0) { and (sum(yx[tt], tt) < sum(yx[i], i)) then tt: = i; }
if sum(yx[tt], tt) { = 0 then break; }
dd: = maxlongint;   //减去最小的time[i]-mm[i]，使后面不会出现mm[i]>time[i]的情况
for i : = tt + 1 to yx[tt] - 1 do {
dd: = min(dd, time[i] - mm[i]);
	}
dd: = min(dd, k)
	  dd: = min(dd, d[tt]);
k: = k - dd;
d[tt]: = d[tt] - dd;
end;
for i : = 1 to m do {
	inc(ans, time[c[i]] - a[i]);    //统计每个人旅行的时间
	}
writeln(ans);
close(input); close(output);
end.

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<cstdlib>
using namespace std;
int n, m, k, ans = 0;
int D[1005], T[10005], qi[10005], zhong[10005];
int late[1005], ari[1005], sum[1005], maxn[1005];
int up[1005], down[1005];
int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i < n; i++) {
		scanf("%d", &D[i]);
	}
	for (int i = 1; i <= m; i++) {
		scanf("%d%d%d", &T[i], &qi[i], &zhong[i]);
		maxn[qi[i]] = max(maxn[qi[i]], T[i]); //人最晚到达某个景点的时间 ；
		up[qi[i]]++;//上车的人数 ；
		down[zhong[i]]++;//下车的人数；
	}
	for (int i = 1; i <= n; i++) {
		ari[i] = late[i - 1] + D[i - 1]; //车到达每个景点的时间；
		late[i] = max(ari[i], maxn[i]); //最后一个到达这个景点的时间
		sum[i] = down[i + 1]; //要下车的人数；
	}
	for (int i = 1; i <= m; i++) {
		ans += (ari[zhong[i]] - T[i]);    //不使用加速器花费的总时间；
	}
	for (int i = n - 2; i >= 1; i--)
		if (ari[i + 1] > maxn[i + 1])
			//求下车人数,因为在这一个人等车的区间中,如果i车站使用了加速器,那么这整一个区间的人都会受益
		{
			sum[i] += sum[i + 1];    //找最大的 人等车的区间的 下车的人数；
		}
	while (k > 0) {
		int x = 0;
		for (int i = 1; i < n; i++)
			if (sum[i] > sum[x] && D[i] > 0) {
				x = i;    //找下车人数最多的区间，（加速的效果最好）
			}
		//x=0说明没有人车人数大于0的了,即没有人要坐车,直接结束即可
		if (x == 0) { break; }
		D[x]--;//两个景点间的时间——；
		k--;//加速装置的个数——；
		ans -= sum[x]; //减去节省的时间；（有几个要下车人就节省几分钟）；
		for (int j = x; j <= n; j++) {
			ari[j] = late[j - 1] + D[j - 1];
			late[j] = max(ari[j], maxn[j]);
			sum[j] = down[j + 1];
		}
		for (int j = n - 2; j >= x; j--)
			if (ari[j + 1] > maxn[j + 1]) {
				sum[j] += sum[j + 1];    //用完一个加速装置后重新统计区间；
			}
	}
	printf("%d", ans);
	return 0;
}