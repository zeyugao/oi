// Olympiad-in-Informatics-Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#define B #ifdef de
#define E #endif
const int maxn = 2000009;
int n, m;
//Watcher
int w[maxn];

//Player
int s[maxn], t[maxn];

int dis_port[maxn];

int ans[maxn];

void out() {
	for (int i = 1; i <= n; i++)
		cout << ans[i] << " ";
	cout << endl;
}
namespace PlayerEdge {
	struct edge {
		int index;
		int to;
		int fr;
		edge * next;
	}e[maxn * 2], *pt = e, *head[maxn];

	void add(int& f, int& t, int& index) {
		pt->index = index; pt->fr = f; pt->to = t; pt->next = head[f]; head[f] = pt++;
	}
	void addedge(int& u, int& v, int& index) { add(u, v, index); add(v, u, index); }
}
namespace Edge {
	struct edge {
		int to;
		edge * next;
	}e[maxn * 2], *pt = e, *head[maxn];

	void add(int& f, int& t) {
		pt->to = t; pt->next = head[f]; head[f] = pt++;
	}
	void addedge(int& u, int& v) { add(u, v); add(v, u); }
}//Edge End
namespace PreDfs {
	int fa[maxn];
	void dfs(int x, int f, int d) {
		dis_port[x] = d;
		fa[x] = f;
		cout << f << " " << fa[x] << endl;
		for (Edge::edge* to = Edge::head[x]; to; to = to->next)
			if (to->to != f) {
				printf("dfs %d %d %d\r\n", to->to, x, d + 1);
				dfs(to->to, x, d + 1);
			}
	}
}//PreDfs End
namespace Core {
	int ancestor;
	int dis_s_t;
	void Calc(int x, bool check);
	int GetDis(int &index) {
		return abs(dis_port[s[index]] + dis_port[t[index]] - 2 * (dis_port[ancestor]));
	}
	void Do(int lparam_index, int lparam_ancestor) {
		ancestor = lparam_ancestor;
		//if (s[lparam_index] == t[lparam_index]) ancestor = s[lparam_index];
		dis_s_t = GetDis(lparam_index);
		B
		printf("Func:Do(int,int) s[i]:%d t[i]:%d dis_s_t:%d\r\n",s[lparam_index],t[lparam_index], dis_s_t);
		cout << lparam_index << " " << lparam_ancestor << endl;
		printf("true\r\n");
		Calc(s[lparam_index], true);
		printf("false\r\n");
		Calc(t[lparam_index], false);
	}
	void Calc(int x, bool check) {
		int b = x;
		int d = 0;
		while (true) {
			printf("calc x:%d PreDfs::fa[x]:%d\r\n", x, PreDfs::fa[x]);
			printf("ancestor:%d\r\n", ancestor);
			printf("x:%d w[x]:%d d:%d\r\n", x, w[x], d);
			int dis;
			if (check)
				dis = d;
			else
				dis = dis_s_t - d;
			if (w[x] == dis/*abs(d - check ? 0 : dis_s_t)*/) {
				printf("x:%d w[x]:%d d:%d abs:%d dis_t:%d dis:%d\r\n", x, w[x], d, abs(d - check ? 0 : dis_s_t), dis_s_t, dis);
				ans[x] ++;
			}
			out();
			//system("pause");
			if (x == ancestor) break;

			//往上一层
			d += 1;


			x = PreDfs::fa[x];
		}
		if (w[x] == d&&check == true)ans[ancestor]--;
	}

}//Core End

namespace Tarjan_LCA {

	int f[maxn];
	bool b[maxn];
	int Find(int x) { return f[x] == x ? x : f[x] = Find(f[x]); }
	bool finished[maxn] = { 0 };
	void Tarjan_LCA(int u) {
		f[u] = u; b[u] = true;
		for (Edge::edge *to = Edge::head[u]; to; to = to->next)
			if (!b[to->to]) {
				Tarjan_LCA(to->to);
				f[to->to] = u;
			}

		for (PlayerEdge::edge * q = PlayerEdge::head[u]; q; q = q->next) {
			int to = (u == q->to) ? q->fr : q->to;
			if (b[to]&&!finished[q->index]) {
				printf("f:%d t:%d lca:%d index:%d\r\n", q->fr, q->to, Find(to),q->index);
				Core::Do(q->index, Find(to));

				finished[q->index] = true;
			}
		}
	}

	/*
	int fa[maxn];
	void Init() {
		for (int i = 1; i <= n; i++) {
			fa[i] = i;
		}
	}
	int FindSet(int x) {
		if (fa[x] != x)fa[x] = FindSet(fa[x]);
		return fa[x];
	}
	void Union(int a, int b) {
		a = FindSet(a), b = FindSet(b);
		if (a != b)
			fa[a] = b;
	}
	bool vs[maxn];
	int ancestor[maxn];
	bool finished[maxn] = { 0 };
	void Tarjan_LCA(int x,int fa) {
		for (Edge::edge *to = Edge::head[x]; to; to = to->next) {
			if (to->to == fa)continue;
			Tarjan_LCA(to->to,x);
			Union(to->to, x);
			ancestor[FindSet(x)] = x;
		}
		vs[x] = true;

		for (int i = 1; i <= m; i++) {
			if (!s[i] && !t[i]) continue;
			int to = (x == s[i]) ? t[i] : s[i];

			if (vs[to]&&!finished[i]) {
				printf("to %d %d\r\n", s[i], t[i]);

				Core::Do(i, ancestor[FindSet(to)]);
				finished[i] = true;
			}
		}
		cout << "End" << endl;
	}*/
}//Tarjan_LCA End



void init() {
	cin >> n >> m;

	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		Edge::addedge(u, v);
	}
	for (int i = 1; i <= n; i++)
		cin >> w[i];
	for (int i = 1; i <= m; i++) {
		cin >> s[i] >> t[i];
		PlayerEdge::addedge(s[i], t[i], i);
	}
	PreDfs::dfs(1, 0, 0);
}
void work() {
	Tarjan_LCA::Tarjan_LCA(1);
	//cout << "end" << endl;
	////system("pause");
}
int main() {

	freopen("e:\\in.txt", "r", stdin);
	freopen("e:\\out.txt", "w", stdout);
	std::ios_base::sync_with_stdio(false);

	init();
	work();
	out();
	//printf("Program End\r\n");
	//system("pause");
	return 0;
}
