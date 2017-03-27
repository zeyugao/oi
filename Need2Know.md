##需要知道&复习的
- 矩阵乘法
- 扩展欧几里得算法
- 树状数组
- 树链剖分
- Splay
- 线段树 (Lazy Tag)
- 二分图的最大匹配、完美匹配和匈牙利算法
- AC自动机
- 树规 http://www.lai18.com/content/6120790.html
- 邻接表（原先版本的邻接表好像在历遍的时候会通过指针修改路径）

```cpp
const int kMaxNum = 0xfffff+10;//这里大小单独修改
struct{
  int from;	//来自的节点
  int to;	//前往的节点
  int weight;//路径的边权
  int next;	//同出发点中的下一条边的index
}edge[kMaxNum * 2];//如果是双向路径则需要*2，单向的则不需要
int edge_count = 0;
int edge_first[kMaxNum * 2] = { 0 };//同上

void AddSingleEdge(int from,int to,int weight){//单向路径
  edge[edge_count++].from = from;
  edge[edge_count].to = to;
  edge[edge_count].weight = weight;
  edge[edge_count].next = edge_first[from];
  edge_first[from] = edge_count;
}

void AddBilateralEdge(int from,int to,int weight){//双向路径
  AddSingleEdge(from,to,weight);
  AddSingleEdge(to,from,weight);
}
```
- 节点到根的距离
```cpp
int Find(int x){
	if(x==f[x]) retunr x;
	int temp = f[x];
	f[x] = Find(fa[x]);
	dis[x] += dis[temp];
	return f[x];
}
void Union(int a,int b){
	int fa = Find(a),b = Find(b);
	if(fa!=fb){
		f[fa] = fb;
		dis[a]= dis[b]+1;
	}else{
		//TODO
	}
}
```
- ~~Tarjan LCA~~（这个版本的好像有问题）
```cpp
int Find(int x){
	if(x!=f[x]) f[x] = Find(f[x]);
	return f[x];
}


void Union(int a,int b){
	int fa = Find(a),b = Find(b);
	if(x==y) return;
	if(rnk[fa]>rnk[fb]) f[fb] = fa;
	else f[fa] =fb,rnk[fb] += rnk[fa]==rnk[fb];
}

int ancestor[1000];
bool visited[1000];
void Tarjan(int x){
	for(int i =0;i<tree[x].size();i++){
		Tarjan(tree[x][i]);
		Union(x,tree[x][i]);
		ancestor[Find(x)] =x;
	}
	visited[x]=true;
	for(int i =0;i<query[x].size();i++){
		if(visited[query[x][i]]){
			dis[anotherpoint] = abs(d[x] + d[query[x]] - 2* d[ancestor[Find(query[x][i])]]);
		}
	}
}
```

- dfs和bfs到搜索完成时，判断了更优值并更新了之后，要记得`return;`，不然就卡循环了
