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
- 邻接表

```cpp
//用struct实现，不用数组e了
const int maxn=10000;
struct edge{
	int to;
	edge* next;
}e[maxn],*pt=e,*head[maxn];

void addedge(int f,int t){
	//当前指针pt，当前创建的边 
	pt->to=t;
	//当前创建的边的下一个同属于f父节点的边 
	pt->next = head[f];
	//将下一个同属于f父节点的边设为本此创建的边，为下一次创建新的同属于f的边做准备 
	head[f] = pt++;
}

//历遍x为父节点的边:
for(edge * t = head[x];t;t=t->next){
  //TODO
  //use:
  t->to; // ok!
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