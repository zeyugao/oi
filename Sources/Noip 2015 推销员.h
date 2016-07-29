/*
NOIP2015 推销员
阿明是一名推销员，他奉命到螺丝街推销他们公司的产品。螺丝街是一条死胡同，出口与入口是同一个，
街道的一侧是围墙，另一侧是住户。螺丝街一共有 N 家住户，第 i 家住户到入口的距离为 Si 米。
由于同一栋房子里可以有多家住户，所以可能有多家住户与入口的距离相等。阿明会从入口进入，
依次向螺丝街的 X 家住户推销产品，然后再原路走出去。阿明每走 1 米就会积累 1 点疲劳值，
向第 i 家住户推销产品会积累 Ai 点疲劳值。阿明是工作狂，他想知道，对于不同的 X，
在不走多余的路的前提下，他最多可以积累多少点疲劳值。

输入

第一行有一个正整数 N，表示街住户数量，接下来一行有 N 个正整数，
其中第 i 个整数 Si 表示第 i 家住户到入口距离保证 S1<=S2<=S3....<10 的 8 次方。
接下来一行有 N 个整数，其中第 i 个整数 Ai 表示向第 i 个住户推销产品会积累疲劳值。保证 Ai<=10 的 3 次方。
输出
输出 N 行，每行一个正整数，其中第 i 行整数表示当 x=i，阿明积累的疲劳值。
*/

/*
考虑 X = 1 时的选择，显然是所有住户中 Ai + 2Si 中最大的被选，若有多个住户的 Ai + 2Si 相同，则优先选择 Si 最小的（想一想为什么）。
然后序列被划分成左右两个部分，选择左边住户获得 Ai 的贡献，选择右边住户获得 Ai + 2(Si - T) 的贡献，
T 表示当前划分界限到胡同入口的距离，注意右边部分的贡献的大小关系相比最初并没有改变，
只需要重新对左边住户的贡献进行排序。于是可以建一个新优先队列将左边的所有住户加入，
将原优先队列中被划分到左边部分的元素丢掉。因为划分界线是一直往右移的，
所以每个元素至多被加入两次，被删除两次，总时间复杂度为O(nlogn).*/
#include <stdio.h>
#include <queue>
#include <stdlib.h>
#include <iostream>
using namespace std;
#define maxn 1000010
#define LL long long
int n, S[maxn], A[maxn];
bool has[maxn];
const int BufferSize = 1 << 16;
char buffer[BufferSize], *Head, *Tail;
inline char Getchar() {
    if(Head == Tail) {
        int l = fread(buffer, 1, BufferSize, stdin);
        Tail = (Head = buffer) + l;
    }
    return *Head++;
}
int read() {
    int x = 0, f = 1; char tc = getchar();
    while(!isdigit(tc)){ if(tc == '-') f = -1; tc = getchar(); }
    while(isdigit(tc)){ x = x * 10 + tc - '0'; tc = getchar(); }
    return x * f;
}
struct HeapNode {
	int id, x;
	LL val;
	//价值不相同时，按价值降序，否则，按距离升序
	bool operator < (const HeapNode& t) const { return val != t.val ? val < t.val : x > t.x; }
};
HeapNode Max(HeapNode a, HeapNode b) {
	if (a < b) return b;
	return a;
}
priority_queue <HeapNode> Q, Q2;

int main() {
	n = read();
	for (int i = 1; i <= n; i++) S[i] = read();
	for (int i = 1; i <= n; i++) A[i] = read();

	while (!Q.empty()) Q.pop();
	while (!Q2.empty()) Q2.pop();
	
	//所有用户的相对于起点的劳累值
	for (int i = 1; i <= n; i++) Q.push(/*(HeapNode)*/{ i, S[i], (LL)A[i] + 2ll * S[i] });
	int T = 0, Tid = 0; LL ans = 0;
	for (int i = 1; i <= n; i++) {
		HeapNode u; u = /*(HeapNode)*/{ 0, 0, 0 };
		if (!Q.empty()) {
			u = Q.top(); Q.pop();
			//Q这里保存的全部都是在划分界限右边的，此处是为了删除再划分界限以左的元素，相当于划分界线右移
			while (u.x <= T && !Q.empty())u = Q.top(), Q.pop();
			if (u.x > T && Q.empty()) u = /*(HeapNode)*/{ 0, 0, 0 };
			//当u.x>T时而Q不空时，ans+=A[i]+2*(S[i]-T)
			//如果u.x<=T而Q不空时，不会有这种情况
			//如果u.x<=T且Q空时， don't understand
			//如果u.x>T且Q空，     __|
			else u.val -= 2ll * T;
		}
		HeapNode v; v = /*(HeapNode) */{ 0, 0, 0 };
		if (!Q2.empty()) v = Q2.top(), Q2.pop();
		u = Max(u, v); has[u.id] = 1;
		ans += u.val;
		printf("%lld\n", ans);
		if (u.x > T) {
			T = u.x;
			//Tid保存T是第几个数，
			//将在划分线左边的全部收入
			//这里的全部收入就只是普通的推销劳累值，没有加上距离
			for (++Tid; Tid <= n && S[Tid] <= T; Tid++) if (!has[Tid])
				Q2.push(/*(HeapNode)*/{ Tid, S[Tid], A[Tid] });
		}
	}

	return 0;
}