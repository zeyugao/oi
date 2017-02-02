/*学校实行学分制。每门的必修课都有固定的学分，同时还必须获得相应的选修课程学分。学校开设了N（N<300）门的选修课程，每个学生可选课程的数量M是给定的。学生选修了这M门课并考核通过就能获得相应的学分。

在选修课程中，有些课程可以直接选修，有些课程需要一定的基础知识，必须在选了其它的一些课程的基础上才能选修。例如《Frontpage》必须在选修了《Windows操作基础》之后才能选修。我们称《Windows操作基础》是《Frontpage》的先修课。每门课的直接先修课最多只有一门。两门课也可能存在相同的先修课。每门课都有一个课号，依次为1，2，3，…。 例如:


1是2的先修课，2是3、4的先修课。如果要选3，那么1和2都一定已被选修过。 　　你的任务是为自己确定一个选课方案，使得你能得到的学分最多，并且必须满足先修课优先的原则。假定课程之间不存在时间上的冲突。
输入格式 Input Format

输入文件的第一行包括两个整数N、M（中间用一个空格隔开）其中1≤N≤300,1≤M≤N。
以下N行每行代表一门课。课号依次为1，2，…，N。每行有两个数（用一个空格隔开），第一个数为这门课先修课的课号（若不存在先修课则该项为0），第二个数为这门课的学分。学分是不超过10的正整数。

 

有些课程可能有先修课且最多只有一门先修课，而这些有先修课的课程必须是选了先修课才能选，求限选M课的情况下所能达到的最大学分。
题目一读完，显然可以反应出这是一个带有依赖的背包问题。因为每门课程最多只有一门先修课程，所以这些课程的依赖关系可以由森林来表示。
这样我们就可以把森林中的每一棵树看成是一个泛化物品.这样我们就可以对这些泛化物体作01背包从而得到最优解。
先设h[i][k]表示泛化物体i在花费代价k时所能得到的最大价值，再设s[i][j]表示仅考虑前i件泛化物体且背包容量为j时所能得到的最大价值，
可得状态转移方程s[i][j]=max{s[i-1][j-k]+h[i][k] (0<=k<=j)}。边界条件和普通01背包类似，就不再赘述了。
现在想必大家最关心的问题是h[i][k]如何得到，其实这个并不困难，我们知道，如果将一棵树的根去掉，
那么这个根原来的子树就会形成一座森林，这个性质给了我们启发，实际上要求一棵树的h[i][k]我们可以递归的求这棵树的每个子树的h[i][k]
（即把该树根的所有子树看成一座森林像上面一样按泛化物体的思想做01背包），因为子树对根的依赖关系，每个子树的h[i][k]求出以后可以
很容易的求到当前树的h[i][k]。这样h[i][k]的问题就解决了，按照这种递归的思想就能比较容易写出代码了。关键要注意的地方就是在计算
某个子树的h[i][k]时，根是必须选的，所以在动态规划的时候要为根留出空间，DP结束过后要将根的值加到结果中*/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <memory>
#include <string>
#include <algorithm>
#include <cmath>
#include <queue>
	using namespace std;
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>

struct Tree {
	int nWeight;
	Tree*pChild, *pBrother;
};
void Solve(Tree *pNodes, int nCost, int nWeight[]) {
	int nCnt = 0;
	Tree*NodesPt[300];

	//提取所有兄弟
	for (Tree*p = pNodes->pChild; p != nullptr; p = p->pBrother) {
		NodesPt[nCnt++] = p;
	}

	//初始化
	for (int i = 0; i <= nCnt; i++) {
		nWeight[i] = 0;
	}
	////未知
	//nWeight=0，空出根节点位置
	nCost = pNodes->nWeight == 0 ? nCost : nCost - 1;
	for (int i = 0; i < nCnt; i++) {
		int W[301];

		//递归，进入更下层进行dp
		Solve(NodesPt[i], nCost, W);

		//dp
		for (int j = nCost; j >= 1; j--) {
			for (int k = 1; k <= j; k++) {
				//泛化物体，nWeight[j]当花费为j时最大值，W[j]为花费为j时的价值
				//=max(当花费为j-k时所取到的最大值+当花费为k时的价值)，
				nWeight[j] = max(nWeight[j], nWeight[j - k] + W[k]);
			}
		}
	}
	//nWeight=0说明没有结点，直接返回
	if (pNodes->nWeight == 0)return;
	//以上得到的只是花费i元时，其子树的最大值，要加上父节点，变为最终最大值
	for (int i = nCost + 1; i >= 1; i--) {
		nWeight[i] = nWeight[i - 1] + pNodes->nWeight;
	}
}

int main() {
	Tree Nodes[301];
	memset(Nodes, 0, sizeof(Nodes));
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
	{
		int nParent;
		cin >> nParent >> Nodes[i].nWeight;
		if (Nodes[nParent].pChild == NULL)
			Nodes[nParent].pChild = Nodes + i;
		else
		{
			Tree *pNode = Nodes[nParent].pChild;
			while (pNode->pBrother != NULL)
				pNode = pNode->pBrother;
			pNode->pBrother = Nodes + i;
		}
	}
	int nWeight[301];
	Solve(Nodes, m, nWeight);
	cout << nWeight[m] << endl;
	getchar();
	getchar();
	return 0;
}
