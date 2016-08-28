const int mx = 10000; //最大顶点数
int n, root;//实际顶点个数，树根节点
int indeg[mx];//顶点入度，用来判断树根
vector<int> tree[mx]; //树的邻接表（不一定是二叉树）

void inputTree() //输入树
{
	scanf("%d", &n); //树的顶点数
	for (int i = 0; i < n; i++) //初始化树，顶点编号从0开始
		tree[i].clear(), indeg[i] = 0;

	for (int i = 1; i < n; i++) //输入n-1条树边
	{
		int x, y; scanf("%d%d", &x, &y); //x->y有一条边
		tree[x].push_back(y); 
		indeg[y]++;//加入邻接表，y入度加一
	}

	for (int i = 0; i < n; i++) //寻找树根，入度为0的顶点
		if (indeg[i] == 0) { root = i; break; }
}
vector<int> query[mx]; //所有查询的内容
void inputQuires() //输入查询
{
	for (int i = 0; i < n; i++) //清空上次查询
		query[i].clear(); 

	int m; scanf("%d", &m); //查询个数
	while (m--)
	{
		int u, v; scanf("%d%d", &u, &v); //查询u和v的LCA
		query[u].push_back(v); query[v].push_back(u);
	}
}int father[mx], rnk[mx]; //节点的父亲、秩
void makeSet() //初始化并查集
{
	for (int i = 0; i < n; i++) father[i] = i, rnk[i] = 0;
}
int findSet(int x) //查找
{
	if (x != father[x]) father[x] = findSet(father[x]);
	return father[x];
}
void unionSet(int x, int y) //合并
{
	x = findSet(x), y = findSet(y);
	if (x == y) return;
	if (rnk[x] > rnk[y]) father[y] = x;
	else father[x]  = y, rnk[y] += rnk[x] == rnk[y];
}//再就是Tarjan算法的核心代码。

//在调用Tarjan之前已经初始化并查集给每个节点创建了一个集合，并且把集合的祖先赋值为自己了，因而这里不用给根节点x单独创建。

int ancestor[mx]; //已访问节点集合的祖先
bool vs[mx];	  //访问标志
void Tarjan(int x) //Tarjan算法求解LCA
{
	for (int i = 0; i < tree[x].size(); i++)
	{
		Tarjan(tree[x][i]); //访问子树
		unionSet(x, tree[x][i]);//将子树节点与根节点x的集合合并 
		ancestor[findSet(x)] = x;//合并后的集合的祖先为x
	}
	vs[x] = 1; //标记为已访问
	for (int i = 0; i < query[x].size(); i++)//与根节点x有关的查询
		if (vs[query[x][i]])
//如果查询的另一个节点已访问，则输出结果
			printf("%d和%d的最近公共祖先为：%d\n", x, 
			//要查询a与b的lca,不断递归下去,直到dfs到了其中一个点,那么等它的子树也走完了,开始往上在回退的时候,那个点会被标记,并且fa设为它的父结点,这时候,父结点会对另一个子结点进行tarjanlca,如果在回退的时候,退到了另一个点,这时候就可以直接询问前者的fa(因为这是在前者的子树走完,从其fa引出的路径,它们两个的lca也一定是这一个fa
			//如果前者的fa引出的tarjanlca没有到另一个点,说明它们两个的lca一定不是这个fa,这时候将前者的fa设为父结点的父结点,并从其引出的lca中找,没有的话,继续提升fa直到到了前面所说的情况

					query[x][i], ancestor[findSet(query[x][i])]);
}