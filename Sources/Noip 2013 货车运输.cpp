/*这个要使路径上最小边权最大，所以一定是在最大生成树（森林）上找（反证法：如果能在最大生成树以外另找出一条路径，且这条路径上最小边权更大一些，则原来的树必然不是最大生成树）
非常轻松愉快的Kruskal求出最大生成树（森林）
然后用倍增法求lca：同时维护p[i][j]和dist[i][j]，分别表示第i个点的2^j祖先,及从第i个点走到它的2^j祖先这条路径上的最小边权。



拿到这道题以后，是个图论题很高兴的说！

给定一个无向图，要求无向图上任意两点u，v之间路径的最小值

读完题各种花哨：

网络流，SPFA，二分答案，树链剖分？？？

等等：树！

想一下，如果现在新加入一条边，如果这条边比u，v之间的路径上的最小权值还要小，那么这条边就木有用了是不是！

嗯。我们就要求一棵最大生成树！！

u，v询问怎么搞？。。额，这。。直接BFS？

还是要涨姿势的，套一下LCA模板吧！

结果因为构最大生成树的时候没有Add两次导致哇哩哇啦红一片。。
还有就是LCA模板不熟练
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define maxn 50010
using namespace std;
int cnt;
struct Edge {
	int from, to, dis;
	bool operator<(const Edge &k)const {return dis > k.dis;}
} e[maxn * 2];
void add(int u, int v, int dis) {
	cnt++; e[cnt].from = u; e[cnt].to = v; e[cnt].dis = dis;
}

int n, m;
int fa[maxn];
int getfa(int x) {return x == fa[x] ? x : fa[x] = getfa(fa[x]);}

struct EDGE {
	int next, to, dis;
} edge[maxn];
int h[maxn], num;
void Add(Edge &k) {
	++num; int u = k.from;
	edge[num].to = k.to;
	edge[num].next = h[u];
	edge[num].dis = k.dis;
	h[u] = num;
}

int F[maxn], dep[maxn];
//anc 从i向上走2^j个到达的元素
//
ancmin 从i向上走2 ^ j个边中最小的边权, 即向上走2 ^ j 个元素时, 通过路径中边权最小的
int anc[10010][14], ancmin[10010][14];
void dfs_buildtree(int u, int fa) {
	F[u] = fa;
	if (fa > 0) { dep[u] = dep[fa] + 1; }
	for (int i = h[u]; i; i = edge[i].next) {
		int v = edge[i].to;
		if (v != fa) {
			ancmin[v][0] = edge[i].dis;
			dfs_buildtree(v, u);
		}
	} return;
}

void Kruscal() {
	sort(e + 1, e + 1 + cnt);
	for (int i = 1; i <= cnt; i++) {
		int u = getfa(e[i].from), v = getfa(e[i].to);
		//双向路径
		//
		//在形成最大生成树时,会通过v!=fa 进行避免重复,形成单向的二叉树
		if (u != v) {fa[v] = u; Add(e[i]); swap(e[i].from, e[i].to); Add(e[i]);}
	}
	cnt = 0;
	memset(ancmin, 127, sizeof ancmin);
	for (int i = 1; i <= n; i++) {
		fa[i] = getfa(fa[i]);
		if (fa[i] == i) { dfs_buildtree(i, -1); }
	}
}


void GET_LCA() {
	memset(anc, -1, sizeof anc);
	for (int i = 1; i <= n; i++) { anc[i][0] = F[i]; }
	//要推ancmin[i][j]时,需要所有的ancmin[i][j-1]都推完,所以j在外层循环
	for (int j = 1; (1 << j) <= n; j++)
		for (int i = 1; i <= n; i++) {
			int a = anc[i][j - 1];
			if (a != -1) {
				anc[i][j] = anc[a][j - 1];
				ancmin[i][j] = min(ancmin[a][j - 1], ancmin[i][j - 1]);
			}
		}
}
int ASK_LCA(int p, int q) {
	if (getfa(p) != getfa(q)) { return -1; }
	int log, i, ans = 0x7ffffff;
	if (dep[p] < dep[q]) { swap(p, q); }
	for (log = 1; (1 << log) <= dep[p]; log++); log--;
	for (i = log; i >= 0; i--)
		//不断提升某一个点,直到它们的高度相同
		if (dep[p] - (1 << i) >= dep[q]) {
			ans = min(ans, ancmin[p][i]);
			p = anc[p][i];
		}
	//在同一边的子树上,可以直接调用ancmin,
	//一个点可以一直通过往上走到另一个点
	if (p == q) { return ans; }
	for (i = log; i >= 0; i--) //LCA不要越界QAQ~
		if (anc[p][i] != -1 && anc[p][i] != anc[q][i]) {
			ans = min(ans, ancmin[p][i]); p = anc[p][i];
			ans = min(ans, ancmin[q][i]); q = anc[q][i];
		}
	ans = min(ans, ancmin[p][0]); ans = min(ans, ancmin[q][0]);
	return ans;
}
int main() {
	freopen("truck.in", "r", stdin);
	freopen("truck.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) { fa[i] = i; }
	int u, v, d;
	for (int i = 1; i <= m; i++) {
		scanf("%d%d%d", &u, &v, &d);
		add(u, v, d); //add(v,u,d);
	}
	Kruscal();
	GET_LCA();
	int Q;
	scanf("%d", &Q);
	for (int i = 1; i <= Q; i++) {
		scanf("%d%d", &u, &v);
		printf("%d\n", ASK_LCA(u, v));
	}
	return 0;
}


/////////////////////////////////////////

题意：n个点，m条边，要求从x到y点路上最小的边权最大的值。
做法：求一次最大生成树，因为对于2个联通块，最大生成树的边一定是最大的，故其他边都可以删去。之后就是一棵树了。可以用树链剖分，不过这里由于只有查询没有修改，故学习了下代码量比较短的树上倍增。其实树上倍增就像区间问题上的RMQ，而树链剖分就像区间问题上的线段树（自认为比喻比较恰当）。
我们用f[i][j]代表i这个点之上2 ^ j个点（不包括自己）是谁。那么只需要先dfs或者bfs遍历得到f[i][0]，就可以递推出所有的f[i][j]，递推方程是：f[i][j] = f[ f[ i ][ j - 1 ] ][ j - 1 ]。大的j依赖与小的j，所以要按照j从小到大来递推。
		这题是要求边最小，那么我们还可以类似f数组维护一个dis数组，意义类似f数组，预处理得到dis[i][0]这个是i这个点其上一条边的权值。递推方程是dis[i][j] = max(dis[i][j - 1], dis[ f[ i ][ j - 1 ] ][ j - 1 ])，一开始我还以为有重复（就是同样的边被算了2次，不过如果只是求最大值那么重了也没有问题，我是想如果是求和）。画了一下才发觉没有重。
				在算完这个求好办了，先求出lca，求lca的前提是要把2个点深度深的那个挪到浅的那里，然后再算，比如差为5，那么我们分解2进制，5 = （101）2 ，那么我们就可以根据f数组往上走。
						在走到同样深度时，如果x == y，那么lca就是x。反之。他们的lca一定是他们2者往上走同样深度相同的第一个点，仔细理解这句话。
						所以我们可以从j的最大值遍历到0，碰到f[x][i] != f[y][i]，那么就要爬上去，因为如果是相等的话，不一定是lca，说不定是lca其上的点。
						所以我们不停的爬，直到最后x和y就变成了lca其下的2个点，所以f[x][0]或者f[y][0]就是答案。
#define ll long long
#define ull unsigned long long
#define eps 1e-8
#define NMAX 10000000
#define MOD 1000000007
#define lson l,mid,rt<<1
#define rson mid+1,r,rt<<1|1
#define PI acos(-1)
#define mp make_pair
						template<class T>
inline void scan_d(T &ret) {
	char c;
	int flag = 0;
	ret = 0;
	while (((c = getchar()) < '0' || c > '9') && c != '-');
	if (c == '-') {
		flag = 1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') { ret = ret * 10 + (c - '0'), c = getchar(); }
	if (flag) { ret = -ret; }
}
const int maxn = 10000 + 10;
const int maxm = 50000 + 10;
int fa[maxn], tot;

struct line {
	int from, to, w;
	bool operator<(const line &t) const {
		return w > t.w;
	}
} e[maxm];

int findit(int x) {
	return x == fa[x] ? x : fa[x] = findit(fa[x]);
}

vector<pair<int, int>>v[maxn];
int f[maxn][17], dis[maxn][17];
int depth[maxn];
bool vis[maxn];
void dfs(int u, int fa, int dep) {
	int sz = v[u].size();
	vis[u] = 1;
	depth[u] = dep;
	for (int i = 0; i < sz; i++) if (v[u][i].first != fa) {
			int to = v[u][i].first;
			f[to][0] = u;
			dis[to][0] = v[u][i].second;
			dfs(to, u, dep + 1);
		}
}

int lca(int x, int y) {
	if (depth[x] < depth[y]) { swap(x, y); }
	int cha = depth[x] - depth[y];
	for (int i = 0; i <= 16; i++)
		if ((1 << i)&cha) { x = f[x][i]; }
	if (x == y) { return x; }
	for (int i = 16; i >= 0; i--) {
		if (f[x][i] != f[y][i]) {
			x = f[x][i];
			y = f[y][i];
		}
	}
	return f[x][0];
}

int getans(int x, int lc) {
	int cha = depth[x] - depth[lc];
	int ret = NMAX;
	for (int i = 0; i <= 16; i++) if ((1 << i)&cha) {
			ret = min(ret, dis[x][i]);
			x = f[x][i];
		}
	return ret;
}

int main() {
#ifdef GLQ
	freopen("input.txt", "r", stdin);
//    freopen("o.txt","w",stdout);
#endif
	int n, m;
	while (~scanf("%d%d", &n, &m)) {
		for (int i = 0; i < m; i++) {
			scanf("%d%d%d", &e[i].from, &e[i].to, &e[i].w);
		}
		sort(e, e + m);
		for (int i = 1; i <= n; i++) {
			fa[i] = i;
			v[i].clear();
		}
		for (int i = 0; i < m; i++) {
			int x = findit(e[i].from), y = findit(e[i].to);
			if (x != y) {
				v[e[i].from].push_back(mp(e[i].to, e[i].w));
				v[e[i].to].push_back(mp(e[i].from, e[i].w));
				fa[x] = y;
			}
		}
		memset(vis, 0, sizeof(vis));
		for (int i = 1; i <= n; i++) if (!vis[i]) {
				f[i][0] = i;
				dis[i][0] = NMAX;
				dfs(i, i, 1);
			}
		for (int j = 1; j <= 16; j++)
			for (int i = 1; i <= n; i++) {
				f[i][j] = f[f[i][j - 1]][j - 1];
				dis[i][j] = min(dis[i][j - 1], dis[f[i][j - 1]][j - 1]);
			}
		int q;
		scanf("%d", &q);
		while (q--) {
			int x, y;
			scanf("%d%d", &x, &y);
			if (findit(x) != findit(y)) { printf("-1\n"); }
			else {
				int lc = lca(x, y);
				int ans = min(getans(x, lc), getans(y, lc));
				printf("%d\n", ans);
			}
		}
	}
	return 0;
}
