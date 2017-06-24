/*核心算法:不管是通过是什么方法,求出出发和结束点的lca,以此来求出那两点的最短距离,
二分答案,
在所有大于ans的路径上取一个交集,在这个交集中选取一条最长的边,如果最长的路径-这条最长公共边(由于是公共边,最长的路径减去了最长边后,其小于了ans,那么其他大于ans而小于最长路径的路径在减去了这条边后,肯定也会小于ans)后仍然大于ans,说明不可行,要扩大ans,否则缩小ans找最优解
*/


/*一遍LCA，存LCA和dis，二分答案，dfs找最长路；
这个算法在BZOJ上能A，其他评测网站就呵呵了，把vector改成邻接表表示应该会快一些
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <iostream>
using namespace std;
#define N 300005
struct Edge {int fr, to, d;}; struct qEdge {int fr, to, lca, dis;};
vector<Edge> edge; vector<int> g[N]; vector<qEdge> qedge; vector<int> qs[N];
int d[N], v[N]; int f[N], p[N]; int n, m, k, l, r, mid, t, maxn, maxl; bool b[N];

void Add_Edge(int fr, int to, int dis) {
	edge.push_back((Edge) {fr, to, dis}); edge.push_back((Edge) {to, fr, dis});
	k = edge.size(); g[fr].push_back(k - 2); g[to].push_back(k - 1);
}
void Add_qEdge(int fr, int to) {
	qedge.push_back(qEdge{fr, to, 0});
	k = qedge.size(); qs[fr].push_back(k - 1); qs[to].push_back(k - 1);
}
int in() {
	int x = 0; char ch = getchar();
	while (ch > '9' || ch < '0') { ch = getchar(); }
	while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0', ch = getchar(); }
	return x;
}
int Find(int x) {return f[x] == x ? x : f[x] = Find(f[x]);}
long long abs(long long x) {return x < 0 ? -x : x;}

//没有加入dis的最短路径,是因为lca时,不用管路径长了多少,lca会将公共部分全部删除,只留下两点间距离
//仅仅保留了dfs的历遍顺序
void dfs(int u, int f, long long w) {
	d[u] = w; int l = g[u].size();
	for (int i = 0; i < l; i++) {
		Edge &e = edge[g[u][i]];
		if (e.to == f) { continue; }
		dfs(e.to, u, w + e.d);
	}
}
void dfs2(int x, int f) {
	p[x] = f; int l = g[x].size();
	for (int i = 0; i < l; i++) {
		Edge &e = edge[g[x][i]];
		if (e.to != f) { dfs2(e.to, x); }
	}
}
void Tarjan_Lca(int u) {
	f[u] = u; b[u] = true; int to, l; l = g[u].size();
	for (int i = 0; i < l; i++) {
		Edge &e = edge[g[u][i]];
		if (!b[e.to]) {
			//tarjanlca应该要在每一层lca递归后立刻保存该层的lca信息
			Tarjan_Lca(e.to); f[e.to] = u;
		}
	}
	l = qs[u].size();
	for (int i = 0; i < l; i++) {
		qEdge &e = qedge[qs[u][i]];
		to = (u == e.to ? e.fr : e.to);
		//查询u结点到其要完成的路径的另一个点的lca,并从中获取这两个点的最短路径
		if (b[to]) { e.lca = Find(to), e.dis = abs(d[to] + d[u] - 2 * d[e.lca]); }
	}
}
/*这里说明距离大于mid的路径在这里(x~p[x])这条边有公共交集了

这里证明试试看
如果一个路径在这点下有一个端点,在这点以上才有另一个端点及lca,则这个点的sum就会增加1,直到lca才会减2,这点的sum就代表了有多少个路径在这个点以下以及这些路径的另一个端点在这一个点以上

如果有一个路径的端点都在这个点以下,由lca的定义,lca的点也一定会在这个点一下,将开始与终止的值所抵消,累加到这个点的sum也没有总共的边数那么多

如果lca就在这个点上,sum也没有那么多,lca导致这条边不会经过(x,p[x])这条边,也就是不经过公共部分
*/
int work(int x, int f) {
	int sum = v[x]; int l = g[x].size();
	for (int i = 0; i < l; i++)
		if (edge[g[x][i]].to != f) { sum += work(edge[g[x][i]].to, x); }
	if (sum == t) { maxn = max(maxn, d[x] - d[p[x]]); }
	return sum;
}
int cmp(qEdge x, qEdge y) {return x.dis > y.dis;}
void init() {
	n = in(), m = in(); int x, y, z;
	for (int i = 1; i < n; i++) {
		x = in(), y = in(), z = in();
		Add_Edge(x, y, z);
	}
	for (int i = 0; i < m; i++) {
		x = in(), y = in();
		Add_qEdge(x, y);
	}
	for (int i = 1; i <= n; i++) { f[i] = i; }
	memset(d, 0, sizeof(d)); memset(b, 0, sizeof(b));
	//所有的点到根节点距离
	dfs(1, 0, 0); Tarjan_Lca(1); dfs2(1, 1);
	sort(qedge.begin(), qedge.end(), cmp);
	maxl = qedge[0].dis; l = 0, r = maxl;
	/* for(int i=0;i<m;i++){ qEdge &e=qedge[i]; printf("%d %d %d %d\n",e.fr,e.to,e.lca,e.dis); }*/
	while (l < r) {
		t = maxn = 0; mid = (l + r) >> 1;
		memset(v, 0, sizeof(v));
		for (int i = 0; i < m; i++) {
			qEdge &e = qedge[i];
			if (e.dis > mid) {
				t++, v[e.fr]++, v[e.to]++, v[e.lca] -= 2;
			}
			else { break; }
		}
		work(1, 0);
		//删除了公共部分中最长的一条边后,最长路径仍然大于ans,说明ans过大,使用二分的方法得到ans
		if (maxl - maxn <= mid) { r = mid; }
		else { l = mid + 1; }
	}
	printf("%d\n", l);
}
int main() {
	init(); return 0;
}


/*
这道题我们用树链剖分做。
思路大致是这样的：
首先题目要求最大值中最小的那个，考虑二分，
那么问题来了， check(mid)check(mid) 怎么个流程呢？
我们在所有的路径中，找出lenlen大于midmid的路径，对这些路径在树上取一个交集MM，
然后在MM中找到长度最大的那条边ee，然后看看路径中最长的那条减去边ee的长度和midmid大小就可以了。
怎么取交集呢？
我们可以先进行一遍树链剖分，用一遍差分就可以了。*/
void sol(int u, int v) {
	while (top[u] != top[v]) {
		if (dep[top[u]] < dep[top[v]]) { swap(u, v); }
		d[tid[top[u]]]++;
		d[tid[u] + 1]--;
		u = fat[top[u]];
	}
	if (dep[u] < dep[v]) { swap(u, v); }
	d[tid[v] + 1]++;
	d[tid[u] + 1]--;
	return;
}/*
差分代码，注意细节，第一个差分
d[tid[top[u]]]++;
我是图
看左边的那一支和右边的那一支，求路径的时候有中间那条轻链。
因此上边的那个玩意不用加。
（原谅我没学过美术的画图水平。。。）
下面是代码：*/
/**************************************************************
    Problem: 4326
    User: MagHSK
    Language: C++
    Result: Accepted
    Time:3952 ms
    Memory:31592 kb
****************************************************************/

#include <cstdio>
#include <algorithm>
int getint() {
	int r = 0, k = 1;
	char c;
	for (c = getchar(); c < '0' || c > '9'; c = getchar()) if (c == '-') { k = -1; }
	for (; '0' <= c && c <= '9'; c = getchar()) { r = r * 10 - '0' + c; }
	return r * k;
}
const int maxn = 300005;
int n, m;
struct edge_type {
	int to, next, val;
} edge[maxn << 1];
struct plan_type {
	int x, y, len;
} plan[maxn];
int h[maxn], cnte = 0;
void ins(int u, int v, int w) {
	edge[++cnte].to = v;
	edge[cnte].next = h[u];
	edge[cnte].val = w;
	h[u] = cnte;
}
int fat[maxn], top[maxn], tid[maxn], tmp[maxn], cos[maxn], dep[maxn], dis[maxn], siz[maxn], son[maxn];
void fhe(int x, int father, int depth, int nd) {
	dep[x] = depth;
	dis[x] = nd;
	fat[x] = father;
	siz[x] = 1; son[x] = 0;
	for (int i = h[x]; i; i = edge[i].next) {
		if (edge[i].to == father) { continue; }
		tmp[edge[i].to] = edge[i].val;
		fhe(edge[i].to, x, depth + 1, nd + edge[i].val);
		siz[x] += siz[edge[i].to];
		if (son[x] == 0 || siz[son[x]] < siz[edge[i].to]) {
			son[x] = edge[i].to;
		}
	}
}
int dfs_clock = 0;
void che(int x, int tp) {
	top[x] = tp; tid[x] = ++dfs_clock; cos[dfs_clock] = tmp[x];
	if (son[x]) {
		che(son[x], tp);
		for (int i = h[x]; i; i = edge[i].next) {
			if (edge[i].to == fat[x] || edge[i].to == son[x]) { continue; }
			che(edge[i].to, edge[i].to);
		}
	}
}
int TTT;
void swap(int &a, int &b) {
	TTT = a; a = b; b = TTT;
}
int lca(int a, int b) {
	while (top[a] != top[b]) {
		if (dep[top[a]] < dep[top[b]]) { swap(a, b); }
		a = fat[top[a]];
	}
	if (dep[a] < dep[b]) { return a; }
	return b;
}
bool cmp(plan_type a, plan_type b) {
	return a.len < b.len;
}
int q[maxn], cfsz[maxn];
int max(int a, int b) {
	return a > b ? a : b;
}
void cf(int u, int v) {
	while (top[u] != top[v]) {
		if (dep[top[u]] < dep[top[v]]) { swap(u, v); }
		cfsz[tid[top[u]]]++;
		cfsz[tid[u] + 1]--;
		u = fat[top[u]];
	}
	if (dep[u] < dep[v]) { swap(u, v); }
	cfsz[tid[v] + 1]++;
	cfsz[tid[u] + 1]--;
	return;
}
int max_plan_len = 0;
bool check(int x) {
	int i, j, sz;
	for (i = 0; i < m; ++i) if (plan[i].len > x) { break; }
	sz = m - i;
	if (q[sz] != 0) { return max_plan_len <= x + q[sz]; }
	for (j = 1; j <= n; ++j) { cfsz[j] = 0; }
	for (j = i; j < m; ++j) { cf(plan[j].x, plan[j].y); }
	int T = 0;
	for (j = 1; j <= n; ++j) {
		T += cfsz[j];
		if (T == sz) { q[sz] = max(q[sz], cos[j]); }
	}
	return max_plan_len <= x + q[sz];
}
int main() {
	n = getint(); m = getint();
	int u, v, w;
	for (int i = 1; i < n; ++i) {
		u = getint(); v = getint(); w = getint();
		ins(u, v, w); ins(v, u, w);
	}
	fhe(1, 0, 0, 0);
	che(1, 1);
	for (int i = 0; i < m; ++i) {
		u = getint(); v = getint();
		plan[i].x = u; plan[i].y = v;
		plan[i].len = dis[u] + dis[v] - (dis[lca(u, v)] << 1);
		max_plan_len = max(plan[i].len, max_plan_len);
	}
	std::sort(plan, plan + m, cmp);
	int l = 0, r = max_plan_len, mid;
	while (l < r) {
		mid = (l + r) >> 1;
		if (check(mid)) { r = mid; }
		else { l = mid + 1; }
	}
	printf("%d\n", r);
	return 0;
}

/*
结清一些陈年老账……

考虑如果最终答案为ansans，则所有路径长度大于ansans的运输计划必有一条边被改造成虫洞，且这条边的权值ww应满足max(val_i)-w≤ans

于是就可以二分答案，转化成判定性问题。若答案为ans，则我们先对所有路径长度大于ans的运输计划求一个交，判断交集中是否存在一条边使得w≥max(val_i)-ans

求路径交可以采用树链剖分维护差分序列的方法，比较直观，时间复杂度O(nlogn)。还有二分答案的复杂度，故总复杂度为O(nlognlogw)。

据说本题还有O(nlogn)的做法，膜拜一下～～*/
/**************************************************************
    Problem: 4326
    User: frank_c1
    Language: C++
    Result: Accepted
    Time:4304 ms
    Memory:32348 kb
****************************************************************/

#include <set>
#include <map>
#include <queue>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <vector>
#include <string>
#include <cctype>
#include <bitset>
#include <cstring>
#include <cstdlib>
#include <utility>
#include <iostream>
#include <algorithm>
#define REP(i,a,b) for(int i=(a);i<=(b);i++)
#define PER(i,a,b) for(int i=(a);i>=(b);i--)
#define RVC(i,S) for(int i=0;i<(S).size();i++)
#define RAL(i,u) for(int i=fr[u];i!=-1;i=e[i].next)
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;

template<class T> inline
void read(T &num) {
	bool start = false, neg = false;
	char c;
	num = 0;
	while ((c = getchar()) != EOF) {
		if (c == '-') { start = neg = true; }
		else if (c >= '0' && c <= '9') {
			start = true;
			num = num * 10 + c - '0';
		}
		else if (start) { break; }
	}
	if (neg) { num = -num; }
}
/*============ Header Template ============*/

struct edge {
	int next, to, dist;
};

const int maxn = (int)(3e5) + 5;
int fr[maxn];
int rk[maxn];
int ds[maxn], ev[maxn];
int st[maxn], ed[maxn], val[maxn];
int cnt[maxn], sum[maxn];
int siz[maxn], dep[maxn], fa[maxn];
int tp[maxn], son[maxn], id[maxn];
edge e[maxn << 1];
int n, m, tote = 0, idx = 0;

inline void addone(int u, int v, int d) {
	++tote;
	e[tote].next = fr[u]; fr[u] = tote; e[tote].to = v; e[tote].dist = d;
}
inline void addedge(int u, int v, int d) {
	addone(u, v, d); addone(v, u, d);
}

void dfs(int x, int f, int d) {
	fa[x] = f; dep[x] = d; son[x] = 0; siz[x] = 1;
	RAL(i, x) if (e[i].to != f) {
		ev[e[i].to] = e[i].dist;
		ds[e[i].to] = ds[x] + e[i].dist;
		dfs(e[i].to, x, d + 1);
		siz[x] += siz[e[i].to];
		if (siz[e[i].to] > siz[son[x]]) { son[x] = e[i].to; }
	}
}

void link(int x, int tx) {
	id[x] = ++idx; tp[x] = tx;
	if (son[x]) { link(son[x], tx); }
	RAL(i, x) if (e[i].to != fa[x] && e[i].to != son[x]) { link(e[i].to, e[i].to); }
}

inline int LCA(int u, int v) {
	while (1) {
		if (dep[u] > dep[v]) { swap(u, v); }
		int tu = tp[u], tv = tp[v];
		if (tu == tv) { break; }
		else if (dep[tu] < dep[tv]) { v = fa[tv]; }
		else { u = fa[tu]; }
	}
	return u;
}

inline void modify(int u, int v, int k) {
	while (1) {
		if (dep[u] > dep[v]) { swap(u, v); }
		int tu = tp[u], tv = tp[v];
		if (tu == tv) {
			if (son[u]) { cnt[son[u]] += k; }
			if (son[v]) { cnt[son[v]] -= k; }
			break;
		}
		else if (dep[tu] < dep[tv]) {
			cnt[tv] += k;
			if (son[v]) { cnt[son[v]] -= k; }
			v = fa[tv];
		}
		else {
			cnt[tu] += k;
			if (son[u]) { cnt[son[u]] -= k; }
			u = fa[tu];
		}
	}
}

bool in[maxn];
int tot = 0;

bool solve(int x) {
	int mx = 0;
	REP(i, 1, m) {
		if (val[i] > x) {
			if (!in[i]) { modify(st[i], ed[i], 1), tot++, in[i] = 1; }
			mx = max(mx, val[i]);
		}
		else if (in[i]) {
			modify(st[i], ed[i], -1); tot--; in[i] = 0;
		}
	}
	REP(i, 1, n) sum[i] = cnt[i];
	REP(i, 1, n) if (son[rk[i]]) {
		sum[son[rk[i]]] += sum[rk[i]];
		if (sum[rk[i]] == tot && ev[rk[i]] >= mx - x) { return 1; }
	}
	return 0;
}

queue<int> Q;
int main() {
	read(n); read(m);
	if (n == 1) {
		printf("0\n");
		return 0;
	}
	memset(fr, -1, sizeof(fr));
	REP(i, 1, n - 1) {
		int u, v, d;
		read(u); read(v); read(d);
		addedge(u, v, d);
	}
	dfs(1, 0, 1);
	link(1, 1);
	Q.push(1); idx = 0;
	while (!Q.empty()) {
		int x = Q.front(); Q.pop();
		rk[++idx] = x;
		RAL(i, x) if (e[i].to != fa[x]) { Q.push(e[i].to); }
	}
	REP(i, 1, m) {
		read(st[i]); read(ed[i]);
		int c = LCA(st[i], ed[i]);
		val[i] = ds[st[i]] + ds[ed[i]] - 2 * ds[c];
	}
	int l = 0, r = (int)(3e8), mid;
	while (l < r) {
		mid = (l + r) >> 1;
		if (solve(mid)) { r = mid; }
		else { l = mid + 1; }
	}
	printf("%d\n", l);
	return 0;
}

/*
最远的最短显然是二分权值
于是使用树链剖分给每个点打上记号顺便可以求求lca
二分check时
开始时借鉴了LXF队长的思想：用线段树给每个大于mid的路径的都打上标记，假设有s个，然后nlogn释放所有标记，o（n）查找一个点被s条路径经过且最大
然后95分跪于最后一个点 将近2s
所以就想到了差分 既然要释放标记不如直接差分
最后一个点卡时过
优化一：读入优化
优化二：记忆化 同一个s的话所能求到的最大点是一定的
为什么是取s条路径的交呢？
证明：
因为如果只取s-1条那么必然有一个路径是无法被减到mid以下。
然后时间复杂度 树链剖分（logn）*二分（logn）*枚举边（n）=nlognlogn
空间复杂度 0(n)*/
#include<cstdio>
#include<algorithm>
#include<cstring>
const int maxn = 664144;
struct range {
	int x, y, len;
} d[maxn];
bool cmp(range x, range y) {return x.len > y.len;}
int root, n, m, x, y, tot, next[maxn], last[maxn], e[maxn], dep[maxn], fa[maxn], size[maxn], son[maxn], top[maxn], pos[maxn];
int pos2[maxn], val[maxn], cost[maxn], MAX[maxn], dist[maxn], s[maxn], node, ans, q[maxn];
int read() { //优化之一
	int x = 0, f = 1; char ch = getchar();
	while (ch < '0' || ch > '9') {if (ch == '-') { f = -1; } ch = getchar();}
	while (ch >= '0' && ch <= '9') {x = x * 10 + ch - '0'; ch = getchar();}
	return x * f;
}
void add(int x, int y, int v) {
	next[++tot] = last[x];
	last[x] = tot;
	val[tot] = v;
	e[tot] = y;
}
void dfs1(int x) {
	dep[x] = dep[fa[x]] + 1;
	size[x] = 1;
	for (int i = last[x]; i; i = next[i]) {
		int v = e[i];
		if (v == fa[x]) { continue; }
		fa[v] = x;
		dist[v] = dist[x] + val[i];
		cost[v] = val[i];
		dfs1(v);
		size[x] += size[v];
		if (size[v] > size[son[x]]) { son[x] = v; }
	}
}
void dfs2(int x, int tp) { //树链剖分
	top[x] = tp; pos[x] = ++node; pos2[node] = cost[x];
	if (son[x] == 0) { return; }
	dfs2(son[x], tp);
	for (int i = last[x]; i; i = next[i]) {
		int v = e[i];
		if (v == fa[x] || v == son[x]) { continue; }
		dfs2(v, v);
	}
}
int query(int x, int y) { //lca
	int a = x, b = y;
	while (top[a] != top[b]) {
		if (dep[top[a]] < dep[top[b]]) { std::swap(a, b); }
		a = fa[top[a]];
	}
	if (dep[a] < dep[b]) { return a; }
	else { return b; }
}
void work(int x, int y) { //差分
	int a = x, b = y;
	while (top[a] != top[b]) {
		if (dep[top[a]] < dep[top[b]]) { std::swap(a, b); }
		s[pos[top[a]]] += 1; s[pos[a] + 1] -= 1;
		a = fa[top[a]];
	}
	if (a == b) { return; }
	if (dep[a] > dep[b]) { std::swap(a, b); }
	s[pos[a] + 1] += 1; s[pos[b] + 1] -= 1;;
}
int check(int mid) {
	int sz = 0;
	while (d[sz + 1].len > mid) { sz++; }
	if (q[sz] != 0) { return q[sz]; } //优化之一 记忆化
	std::memset(s, 0, sizeof(s));
	for (int i = 1; i <= sz; i++) { work(d[i].x, d[i].y); }
	int Maxx = 0, tott = 0;
	for (int i = 1; i <= n; i++) {tott += s[i]; if (tott == (sz)) { Maxx = std::max(Maxx, pos2[i]); }}
	q[sz] = Maxx;
	return Maxx;
}
int main() {
	n = read(); m = read();
	for (int i = 1; i < n; i++) {
		int v;
		x = read(); y = read(); v = read();
		add(y, x, v); add(x, y, v);
	}
	dfs1(1);
	dfs2(1, 1);
	for (int i = 1; i <= m; i++) {
		d[i].x = read(); d[i].y = read();
		d[i].len = dist[d[i].x] + dist[d[i].y] - 2 * dist[query(d[i].x, d[i].y)];
	}
	std::sort(d + 1, d + 1 + m, cmp);
	int l = 0, r = d[1].len;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (d[1].len - check(mid) > mid) {
			l = mid + 1;
		}
		else { r = mid - 1, ans = mid; }
	}
	printf("%d", ans);
	return 0;
}