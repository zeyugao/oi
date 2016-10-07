/*一、所以先来考虑单栈排序：
在栈的时候，有提到：栈是先进后出的（当然，指的是在它出栈之前如果有元素在它上面，则它是后出的），所以就有：对于i<j，设p[x]为第x个进栈的元素，如果p[i]<p[j]也就是说：按照题目要求的按顺序出栈，小的要先出，p[i]要先出，所以p[i]必须在p[j]进栈前出栈，不然p[i]必须在p[j]出栈后才能出，这样就不能满足按顺序，但同样的，p[i]能够出栈的前提是：所有比它小的元素均已出栈;这时就能发现，如果在j之后存在比p[i]小的元素，则单栈排序不可进行。
//i要在j之前出栈,而如果j后面有比i小的元素k,根据排序原理(?),k一定要在i前面出栈,k又比j小,j就不可避免地要压入栈里,并且此时i已经在栈中了,与前面的前提相违背并且只要不存在这种情况，则单栈排序一定能进行，因为对于任意p[x]在它必须出栈的时候不存在限制它出栈的元素，然后按照进栈顺序进行模拟就可完成排序过程。
二、现在再来看看双栈排序：在写代码之前，必须明确的是：双栈排序就是同时给出两个单栈的进栈顺序，并且没告知哪些元素是一个栈的，哪些元素不是一个栈的，所以代码的首要任务就是对两个单栈进行元素的分配，并且是两个单栈都能进行排序的分配，如果找不出就输出零联系第一步的思考，就是说对于每一对如上述所说的点，如果上述情况存在，那么这两个点不能在同一个单栈里面，所以就可以通过染色对栈进行分配。三、完成分配后：基本就是纯模拟了，同时模拟两个栈的操作，按颜色分成两个栈，然后按操作a>操作b>操作c>操作d的优先级进行贪心模。
注：本代码用的不是这种一个个操作去贪心的科学模拟方法（—>_—>）而是用了一种极不科学的打法（甚至连下标都不小心打错的打法）但是对于任何随机数据和科学打法的结却是一样一样的— —！  并且vijos上总耗时0毫秒AC— —！至今不知为何如此拙计— —！
四、算法实现：
将所有冲突的元素连上一条线（用邻接表、哈希神马都可以，线不会多到那里去，本代码采用哈希），全部连完后，从第一个点开始到第n个点，如果没染色就对它进行染色，并把与它矛盾的点染上另一个颜色，如果染色过程中出现将一个有颜色的点染成另一种颜色的情况，那么就无解，因为至少有其中一个单栈无法进行排序。（其实染色的过程就是在解决最后问题中对元素的分）。最后用贪心模拟一遍就O拉~
*/
#include<cstdio> 
#include<iostream>   
#include<algorithm> 
using namespace std;

int p[1010], col[1010], Min[1010], pai[3][1010], l[3];
//p存进栈顺序  ，col为颜色，Min下文有说;
//pai为两个单栈，l 为两个单栈内的个点数;

int wei[10010], las[10010], too[10010];
//哈希表：wei：点在表中最后记录位置;
//las：某位置在表中上一记录位置;
//too：存冲突对象;

int n, should = 1;
//should为该出栈的点;

void line(int x, int y) {
	//将冲突点连起来
	las[++t] = wei[x]; wei[x] = t; too[t] = y;
	//记录上一记录位置，再更新位置，存取冲突点
	las[++t] = wei[y]; wei[y] = t; too[t] = x;
}

void draw(int x, int c) {
	//将x 染成颜色 c（1~2）
	if (!col[x])  col[x] = c;
	else
		if (col[x] != c)
		{
			printf("0"); exit(0);
		}
		else return;
		//如果x 有颜色且不为 c那么就无解
		//x 的颜色代表了它在哪一个栈中进行过渡,被染了色而颜色又与本次所需要的颜色不相同,说明需要放两个栈中才可以,无解
		for (int i = wei[x]; i; i = las[i])
			draw(too[i], 3 - c);
		//将与它冲突的点，染上另一个颜色
		//让另一个点到另一个栈中,避免冲突
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &p[i]);

	Min[n] = p[n];
	//求第 i ~ n 点中最小的点Min[i] 
	for (int i = n - 1; i >= 1; i--)
		Min[i] = min(Min[i + 1], p[i]);

	pai[1][0] = 1002;  col[n + 1] = 1;
	//初始化栈顶边界、栈底边界
	pai[2][0] = 1002;  p[n + 1] = 1001;
	//对最后一位元素之后那位处理以便最后把所有元素压出栈

	for (int i = 1; i <= n - 2; i++)
		for (int j = i + 1; j <= n - 1; j++)
			if (p[i] < p[j] && Min[j + 1] < p[i]) line(i, j);
	//枚举每对点，如果有冲突，则连线（代表冲突） 

	for (int i = 1; i <= n; i++)
		//进行染色，即分成两个客栈，然后同时进行单栈排序
		if (!col[i])  draw(i, 1);

	//科学的打法是进行abcd优先判定的贪心模拟，以下是伤心病况的不科学打法— —！
	for (int i = 1; i <= n + 1; i++) {
		//模拟单栈排序，两个同时进行，到n+1是为了所有元素出栈
		while (1)
			//能出就出
			if (pai[1][l[1]] == should) { should++; l[1]--; printf("b "); }
			else
				if (pai[2][l[2]] == should) { should++; l[2]--; printf("d "); }
				else break;
				pai[col[i]][++l[col[i]]] = p[i];
				//进栈（就是这行！！！！发现了吗！！！！！！）
				if (i < n + 1) printf("%c ", char(2 * col[i] + 95));
	}
}
/*
有看33行无注释代码的并且有看最后模拟的人应该发现了— —！没错—>_—>下标当时给打错了。。LOOK：
　pai[col[i]][++l[col[i]]]=p[i];
i 是代表第 i 个进栈，但p[ i ]代表的才是第 i 个进栈的元素，在染色的时候是给元素进行染色，而不是对该元素的进栈顺序
进行染色，就是说正确的应该是：pai[col[p[i]]][++l[col[p[i]]]]=p[i];
hehe然后喜感的是上一行下标打对的那个是错的— —，因为想想也知道那样模拟出来的答案不一定是最优的，但把元素改成与它完全无关的它的进栈顺序的颜色（染色染的根本就不是它啊— —！）就可以喜感的AC了— —！  而且做过随机数据— —！与正解对于随机数据的结果目前都一样— —！*/





/*分析条件，我们把问题抽象为数学模型。设输入序列为S，考虑S[i],S[j]两个元素不能进入同一个栈的条件.注意,这里所说的"S[i],S[j]两个元素不能进入同一个栈",不是说仅仅不能同时在一个栈中,而是自始至终不能进入一个栈,即如果有解,那么S[i],S[j]一定进入过的栈不同.

结论P: S[i],S[j]两个元素不能进入同一个栈 <=> 存在k,满足i<j<k,使得S[k]<S[i]<S[j]. 证明略过,请参考sqybi.尝试后可以发现结论P是正确的.

把每个元素按照输入序列中的顺序编号,看作一个图中的每个顶点.这时,我们对所有的(i,j)满足i<j,判断是否满足结论P,即S[i],S[j]两个元素能否进入同一个栈.如果满足P,则在i,j之间连接一条边.

我们对图染色,由于只有两个栈,我们得到的图必须是二分图才能满足条件.由于要求字典序最小,即尽量要进入栈1,我们按编号递增的顺序从每个未染色的顶点开始染色,相邻的顶点染上不同的色,如果发生冲突,则是无解的.否则我们可以得到每个顶点颜色,即应该进入的栈.

接下来就是输出序列了,知道了每个元素的决策,直接模拟了.

在判断数对(i,j)是否满足P时,枚举检查是否存在k的时间复杂度是O(n),则总的时间复杂度是O(n^3),对于n=1000是太大了.这原因在于过多得枚举了k,我们可以用动态规划把枚举k变为O(1)的算法.

设F[i]为Min{S[i],S[i+1],S[i+2]..S[n-1],S[n]},状态转移方程为F[i]=Min{ S[i] , F[i+1] }.边界为F[N+1]=极大的值.

判断数对(i,j)是否满足P,只需判断(S[i]<S[j] 并且 F[j+1]<S[i])即可.时间复杂度为O(n^2).*/


/*
* Problem: NOIP2008 twostack
* Author: Guo Jiabao
* Time: 2008.12.9 21:22:52
* State: Solved
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>

using namespace std;

const int MAXN = 1002;
const int INF = 0x7FFFFFFF;

class tStack
{
private:
	int top;
	int S[MAXN];
public:
	tStack() : top(0) {}
	void ins(int k)
	{
		S[++top] = k;
	}
	int tp()
	{
		return S[top];
	}
	void pop()
	{
		top--;
	}
};

int S[MAXN], F[MAXN], bel[MAXN];
bool adjm[MAXN][MAXN];
int N, top1, top2;
tStack T[3];

void init()
{
	int i;
	freopen("twostack.in", "r", stdin);
	freopen("twostack.out", "w", stdout);
	scanf("%d", &N);
	for (i = 1; i <= N; i++)
	{
		scanf("%d", &S[i]);
	}
}

void noanswer()
{
	printf("0");
	exit(0);
}

void color(int i, int c)
{
	bel[i] = c;
	int j;
	for (j = 1; j <= N; j++)
	{
		if (adjm[i][j])
		{
			if (bel[j] == c) //conflict : not a bipartite graph
			{
				noanswer();
			}
			if (!bel[j])
			{
				color(j, 3 - c); // color the opposite color 1<->2
			}
		}
	}
}

void dye()
{
	int i, j;
	F[N + 1] = INF;
	//找的是在j后面有一个k(i<j<k)，如果有k满足S[k]<S[i]<S[j]就不能符合条件，这里只要一个满足即可，可以取从j+1开始的最小值，如果最小值都大于了S[j]，就说明这个序列是可以的
	for (i = N; i >= 1; i--)
	{
		F[i] = S[i];
		if (F[i + 1] < F[i])
			F[i] = F[i + 1];
	}
	for (i = 1; i <= N - 1; i++)
	{
		for (j = i + 1; j <= N; j++)
		{
			if (S[i] < S[j] && F[j + 1] < S[i])
			{
				adjm[i][j] = adjm[j][i] = true;
			}
		}
	}
	for (i = 1; i <= N; i++)
	{
		if (!bel[i])
		{
			color(i, 1);
		}
	}
}

void solve()
{
	int i, should = 1, s;
	for (i = 1; i <= N; i++)
	{
		//should 为当前应该为哪一个数字出队，如果top就是should，那么，直接出队即可
		s = bel[i];
		if (s == 1)
		{
			T[1].ins(S[i]);
			printf("a ");
		}
		else
		{
			T[2].ins(S[i]);
			printf("c ");
		}
		while (T[1].tp() == should || T[2].tp() == should)
		{
			//should 为当前应该为哪一个数字出队，如果top就是should，那么，直接出队即可
			if (T[1].tp() == should)
			{
				T[1].pop();
				printf("b");
				if (should != N)
					printf(" ");
				should++;
			}
			else
			{
				T[2].pop();
				printf("d");
				if (should != N)
					printf(" ");
				should++;
			}
		}
	}
}

int main()
{
	init();
	dye();
	solve();
	return 0;
}