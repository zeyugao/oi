#include "stdafx.h"
/*struct Tree {
	int left, right, size;
}tree[1000];
void LeftRatote(int& x) {
	int y = tree[x].left;
	tree[x].right = tree[y].left;
	tree[y].left = x;
	tree[y].size = tree[x].size;
	tree[x].size = tree[tree[x].left].size + tree[tree[x].left].size + 1; 这里的tree[x].left实际上是tree[y].left
	x = y;
}
void RightRatote(int&x) {
	int y = tree[x].right;
	tree[x].right = tree[y].left;
	tree[y].right = x;
	tree[y].size = tree[x].size;
	tree[x].size = tree[tree[x].right].size + tree[tree[x].left].size + 1;
	x = y;
}
void Maintain(int &x, bool flag) {
	if (flag == false) {
		if (tree[tree[tree[x].left].left].size > tree[tree[x].right].size)
			RightRatote(x);
		else if (tree[tree[tree[x].left].right].size > tree[tree[x].right].size) {
			LeftRatote(tree[x].left);
			RightRatote(x);
		}
		else return;
	}
	else {
		if (tree[tree[tree[x].right].right].size > tree[tree[x].left].size)
			LeftRatote(x);
		else if (tree[tree[tree[x].right].left].size > tree[tree[x].left].size) {
			RightRatote(tree[x].right);
			LeftRatote(x);
		}
		else return;
	}
	Maintain(tree[x].left, false);
	Maintain(tree[x].right, true);
	Maintain(x, true);
	Maintain(x, false);
}*/
struct _Direction {
	int DeltaX, DeltaY;
}Direction[8];
struct Point {
	int dis, color, x, y;
	Point* father;
	bool visited;
};
Point Map[1001][1001];

Point a[1000001];
int n;
inline Point Find(Point x) {
	if (x.father->x==x.x&&x.father->y==x.y) return x;
	auto temp = Find(*(x.father));
	x.father = &temp;
	return temp;
}
void BFS(Point source);
a:父节点，子结点
inline void Union(Point a, Point b) {
	auto fa_a = Find(a);
	auto fa_b = Find(b);
	if (!(fa_a.x == fa_b.x&&fa_a.y == fa_b.y)) {
		fa_a.father = &fa_b;
	}
}
void DFS(Point source) {
	if (source.visited)return;
	for (int i = 0; i < 8; i++) {
		if (source.x + Direction[i].DeltaX >= 1 && source.x + Direction[i].DeltaX <= n&&
			source.y + Direction[i].DeltaY >= 1 && source.y + Direction[i].DeltaY <= n)
		{
			source.visited = true;
			if (source.color == Map[source.x + Direction[i].DeltaX][source.y + Direction[i].DeltaY].color) {
				Union(source, Map[source.x + Direction[i].DeltaX][source.y + Direction[i].DeltaY]);
				BFS(Map[source.x + Direction[i].DeltaX][source.y + Direction[i].DeltaY]);
			}
			else
				DFS(Map[source.x + Direction[i].DeltaX][source.y + Direction[i].DeltaY]);
		}
	}
}
void BFS(Point source) {
	int head = 0, tail = 1;
	a[head] = source;
	while (head != tail) {
		head++;
		for (int i = 0; i < 8; i++) {
			if ((a[head].x + Direction[i].DeltaX >= 1 && a[head].x + Direction[i].DeltaX <= n) &&
				(a[head].y + Direction[i].DeltaY >= 1 && a[head].y + Direction[i].DeltaY <= n) &&
				(!Map[a[head].x + Direction[i].DeltaX][a[head].y + Direction[i].DeltaY].visited)) {
				if (Map[a[head].x + Direction[i].DeltaX][a[head].y + Direction[i].DeltaY].color == a[head].color) {
					tail++;
					a[tail] = Map[a[head].x + Direction[i].DeltaX][a[head].y + Direction[i].DeltaY];
					Map[a[head].x + Direction[i].DeltaX][a[head].y + Direction[i].DeltaY].visited = true;
					Union(Map[a[head].x + Direction[i].DeltaX][a[head].y + Direction[i].DeltaY], a[head]);
				}
				else
					if (Find(Map[a[head].x + Direction[i].DeltaX][a[head].y + Direction[i].DeltaY]).dis + 1 < Find(a[head]).dis)
						Find(a[head]).dis = Find(Map[a[head].x][a[head].y]).dis = Find(Map[a[head].x + Direction[i].DeltaX][a[head].y + Direction[i].DeltaY]).dis + 1;
			}
			if ((a[head].x + Direction[i].DeltaX >= 1 && a[head].x + Direction[i].DeltaX <= n) &&
				(a[head].y + Direction[i].DeltaY >= 1 && a[head].y + Direction[i].DeltaY <= n) &&
				Map[a[head].x + Direction[i].DeltaX][a[head].y + Direction[i].DeltaY].color != a[head].color&&
				Map[a[head].x + Direction[i].DeltaX][a[head].y + Direction[i].DeltaY].visited&&
				Find(Map[a[head].x + Direction[i].DeltaX][a[head].y + Direction[i].DeltaY]).dis > Find(a[head]).dis + 1)

				Find(Map[a[head].x + Direction[i].DeltaX][a[head].y + Direction[i].DeltaY]).dis = Find(a[head]).dis + 1;
		}
	}
}
inline void initDirection() {
	Direction[0] = { -1,-1 };	Direction[1] = { -1,0 };	Direction[2] = { -1,1 };
	Direction[3] = { 0,-1 };	/*							*/		Direction[4] = { 0,1 };
	Direction[5] = { 1,-1 }; 	Direction[6] = { 1,0 };	Direction[7] = { 1,1 };
}
int main() {
	initDirection();
	int k;
	scanf_s("%d%d", &n,&k);
	int c;
	memset(Map, 0, sizeof(Map));
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			c = getchar();
			while (!isdigit(c))c = getchar();
			Map[i][j].color = c-'0';
			Map[i][j].x = i; Map[i][j].y = j;
			Map[i][j].father = &Map[i][j];
			if (i == 1 || i == n || j == 1 || j == n)Map[i][j].dis = 0;
			else Map[i][j].dis = INF;
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (i == 1 || i == n || j == 1 || j == n) DFS(Map[i][j]);
		}
	}
	int x, y;
	while (k--) {
		scanf_s("%d%d", &x, &y);
		cout << Map[x][y].dis << endl;
	}
	system("pause");
	return 0;
};
/*
int maxx[20][10000];
int minx[20][10000];

void RMQ(int num) {

	int k = (int)log(num) / log(2);
	for (int i = 1; i <= k; ++i) {  枚举数到2^i个数
		for (int j = 1; j <= num; ++j) { 枚举开头
			if (j + (1 << i) - 1 <= num) { 这里要保证j+2^i-1 不超过总数，即往后数的数不越界
				maxx[i][j] = max(maxx[i - 1][j], maxx[i - 1][j + (1 << i >> 1)]);
			}
			else break;
		}
	}
}

int ask(int i, int j) {
	int k = log(j - i + 1) / log(2);
	return printf("%d", max(maxx[k][i], maxx[k][j - (1 << k) + 1]));
}
int main() {
	int a[10] = { 3,5,8,9,1,4,6,7,0,2 };
	for (int i = 0; i < 10; i++) {
		maxx[0][i+1] = a[i];
	}
	RMQ(10);
	int i, j;
	while (scanf_s("%d%d", &i, &j)) {
		ask(i, j);
	}
	return 0;
}*/
/*int a[100001];
struct Tree {
	int Min;
	int Max;
	int size;
	int val;
};
struct ret {
	Tree tree;
	int less_num;
	int bigger_num;
};
Tree tree[100001];
int Ans[100001];
Tree build(int root, int l, int r) {
	if (l == r) {
		tree[root].val = a[l];
		tree[root].Max = a[l];
		tree[root].Min = a[l];
		tree[root].size = 1;
		return tree[root];
	}
	else {
		int mid = (l + r) >> 1;
		auto l_t = build(root << 1, l, mid);
		auto r_t = build(root << 1 | 1, mid + 1, r);
		tree[root].Max = max(l_t.Max, r_t.Max);
		tree[root].Min = min(l_t.Min, r_t.Max);
		tree[root].size = l_t.size + r_t.size;
		return tree[root];
	}
}

ret Query(int root, int l, int r, int k) {
	ret t;
	memset(&t, 0, sizeof(t));
	auto tmp = tree[root];
	if (l==r) {
		if (tmp.val > k)
			t.bigger_num = 1;
		else if(tmp.size <k)
			t.less_num = 1;
		else
			Ans[l] = 0;
		return t;
	}
	if (tmp.Max < k || tmp.Min>k)
		Tree tree;
		t.tree=tree;
		return t;

}
int n, t;
cin >> n;
for (int i = 1; i <= n; i++) {
	cin >> t;
	a[i] = t;
}
memset(tree, 0, sizeof(tree));
*/

/*
#include<iostream>
#include<stdio.h>
#include<string>
#include<cstring>
using namespace std;
string s0, s1;
int n;
long long a0[200], a1[200];
string nn[1000];
char op[1000]; 数字栈，符号栈
int nnn, opn;
bool m[7][7] = {算符优先级
	{ 0,0,0,0,1,0,1 },
	{ 0,0,0,0,1,0,1 },
	{ 1,1,0,0,1,0,1 },
	{ 1,1,1,0,1,0,1 },
	{ 1,1,1,1,1,1,1 },
	{ 0,0,0,0,1,0,0 },
	{ 0,0,0,0,0,0,1 }
};+ - * ^ ( ) #
long long power(long long aa, long long bb)
{
	if (bb == 0) return 1;
	return aa*power(aa, bb - 1);
}
long long comp(long long x, long long y, char c)
{
	switch (c)
	{
	case '+': return x + y;
	case '-': return x - y;
	case '*': return x*y;
	case '^': return power(x, y);
	}
}
void compute(string s, long long a[])
{
	long long sta[100];
	int stan;
	for (long long digit = -80; digit <= 80; digit++)
	{
		stan = 0;
		for (int i = 0; i < s.size();/*在循环体中i会累加**)
		{
			sta[stan++] = 0;
			while (s[i] != '@')
			{
				if (s[i] == 'a')
					sta[stan - 1] = digit;
				else
					sta[stan - 1] = sta[stan - 1] * 10 + (s[i] - '0');
				i++;
			}
			i++;
			while (!(isdigit(s[i]) || s[i] == 'a' || i >= s.size()))
				sta[--stan - 1] = comp(sta[stan - 1], sta[stan], s[i++]);
		}
		a[digit + 80] = sta[0];
	}
}
int cast(char c)
{
	switch (c)
	{
	case '+': return 0;
	case '-': return 1;
	case '*': return 2;
	case '^': return 3;
	case '(': return 4;
	case ')': return 5;
	case '#': return 6;
	}
}
bool pre(char c1, char c2)
{
	return m[cast(c1)][cast(c2)];
}
string postexp(string s)
{
	string tmp;
	nnn = opn = 0;
	op[opn++] = '#';
	for (int i = 0; i < s.size(); ++i)
	{
		if (s[i] == ' ')
			continue;
		if (isdigit(s[i]) || s[i] == 'a')
		{
			tmp = "";
			for (; isdigit(s[i]) || s[i] == 'a'; ++i)
				tmp.append(1, s[i]);
			tmp.append(1, '@');数字之间的分割符号
			--i;
			nn[nnn++] = tmp;
		}
		else
		{
			if (s[i] != ')' && pre(s[i], op[opn - 1]))优先级高压栈  s[i]>op[opn-1]=1
				op[opn++] = s[i];
			else
			{
				while (!pre(s[i], op[opn - 1]))  s[i]<op[n-1]
				{
					nn[--nnn].append(1, op[--opn]);
					nn[nnn - 1] += nn[nnn];
				}
				if (s[i] == ')')
					opn--;
				else
					op[opn++] = s[i];
			}
		}
	}
	return nn[0];得到后缀表达式
}
int main()
{
	freopen("in","r",stdin);
	freopen("out","w",stdout);
	char tt;
	string ans = "";  最终结果
	getline(cin, s0);
	s0 = postexp(s0 + "#");  将s0变成后缀表达
	compute(s0, a0);      代入11个数计算结果存入a0
	cin >> n;
	scanf_s("%c", &tt);
	for (int lll = 0; lll < n; ++lll)
	{
		getline(cin, s1);
		s1 = postexp(s1 + "#"); 将s1变成后缀表达
		compute(s1, a1);
		int i;
		for (i = 0; i < 161; ++i)
			if (a0[i] != a1[i])
				break;
		if (i == 161)
			ans.append(1, 'A' + lll);
	}
	cout << ans << endl;
}*/
/*struct _User {
	int id, dis; long long val; bool sel;
	bool operator < (const _User&t) { return val != t.val ? val < t.val : dis > t.dis; }
};
priority_queue<_User> User;
priority_queue<_User> User_L;
int main() {
	int N;
	cin >> N;
	long long val[1000010] = { 0 }; int dis[1000010] = { 0 };
	for (int i = 1; i <= N; i++)  cin >> dis[i];
	for (int i = 1; i <= N; i++) cin >> val[i];
	for (int i = 1; i <= N; i++) User.push({ i,dis[i],val[i],false });
	int last, ans;
	for (int i = 1; i <= N; i++) {

	}

	return 0;
}*/
/*#include<iostream> include<cstring> include<cstdio>
using namespace std;
long long m, q[100011], w[100011], a[100011], l, s, ans;
long long cut()
{
	int m = a[1], x = 1, y = 2;
	a[1] = a[s];
	s--;
	while (y <= s && (a[x] < a[y] || a[x] < a[y + 1])) { if (y < s&&a[y] < a[y + 1])y++; int t = a[x]; a[x] = a[y]; a[y] = t; x = y; y = 2 * y; } return m;
}
void charu(int k) {
	int x = k, si = ++s;
	while (k > a[si / 2] && si > 1)
	{
		a[si] = a[si / 2];
		si /= 2;
	}
	a[si] = x;
}
int main()
{
	scanf("%lld", &m);
	for (int i = 1; i <= m; i++)
		scanf("%lld", &q[i]);
	for (int i = 1; i <= m; i++)
		scanf("%lld", &w[i]);
	long long b = 0, c = 0, xc = -1;
	for (int i = 1; i <= m; i++)
	{
		for (int j = l + 1; j <= m; j++)
		{
			int k = (q[j] - l) * 2 + w[j];
			if (k > c) { xc = j; c = k; }
		}
		if (c > b)
		{
			ans += c;
			for (int j = l + 1; j < xc; j++)
				charu(w[j]);
			l = xc;
			c = 0;
		}
		else
			ans += b;
		b = cut();
		printf("%lld\n", ans);
	}*/
const int BufferSize = 1 << 16;
char buffer[BufferSize], *Head, *Tail;
inline char Getchar() {
	if (Head == Tail) {
		int l = fread(buffer, 1, BufferSize, stdin);
		Tail = (Head = buffer) + l;
	}
	return *Head++;
}
int read() {
	int x = 0, f = 1; char tc = getchar();
	while (!isdigit(tc)) { if (tc == '-') f = -1; tc = getchar(); }
	while (isdigit(tc)) { x = x * 10 + tc - '0'; tc = getchar(); }
	return x * f;
}

#define maxn 1000010
#define LL long long
int n, S[maxn], A[maxn];
bool has[maxn];
struct HeapNode {
	int id, x;
	LL val;
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
	for (int i = 1; i <= n; i++) Q.push(/*(HeapNode)*/{ i, S[i], (LL)A[i] + 2ll * S[i] });
	int T = 0, Tid = 0; LL ans = 0;
	for (int i = 1; i <= n; i++) {
		HeapNode u; u = /*(HeapNode)*/{ 0, 0, 0 };
		if (!Q.empty()) {
			u = Q.top(); Q.pop();
			while (u.x <= T && !Q.empty())u = Q.top(), Q.pop();
			if (u.x > T && Q.empty()) u = /*(HeapNode)*/{ 0, 0, 0 };
			else u.val -= 2ll * T;
		}
		HeapNode v; v = /*(HeapNode) */{ 0, 0, 0 };
		if (!Q2.empty()) v = Q2.top(), Q2.pop();
		u = Max(u, v); has[u.id] = 1;
		ans += u.val;
		printf("%lld\n", ans);
		if (u.x > T) {
			T = u.x;
			for (++Tid; Tid <= n && S[Tid] <= T; Tid++) if (!has[Tid])
				Q2.push(/*(HeapNode)*/{ Tid, S[Tid], A[Tid] });
		}
	}

	return 0;
}
int main() {
	int Distance[100011];
	int Value[100011];
	bool bSelected[100011];
	/*memset(bSelected, 0, sizeof(bSelected));
	memset(Value, 0, sizeof(Value));
	memset(Distance, 0, sizeof(Distance));*/
	int N;
	cin >> N;
	for (int i = 1; i <= N; i++) {
		int dis;
		cin >> dis;
		Distance[i] = dis;
	}
	for (int i = 1; i <= N; i++) {
		int val;
		cin >> val;
		Value[i] = val;
	}
	int Output[100001] = { 0 };
	int _max = 0;
	int last = 0;
	for (int i = 1; i <= N; i++) {
		if (_max <= Distance[i] * 2 + Value[i]) {
			_max = Distance[i] * 2 + Value[i];
			last = i;
		}
	}
	Output[1] = _max;
	bSelected[last] = true;
	int now_last = 0;
	for (int m = 2; m <= N; m++) {
		_max = 0;
		for (int i = 1; i < last; i++) {
			if (_max <= Output[m - 1] + Value[i] && bSelected[i] != true) {
				_max = Output[m - 1] + Value[i];
				now_last = i;
			}
		}
		for (int i = last + 1; i <= N; i++) {
			if (_max <= Output[m - 1] + Value[i] + (Distance[i] - Distance[last]) * 2 && bSelected[i] != true) {
				_max = Output[m - 1] + Value[i] + (Distance[i] - Distance[last]) * 2;
				now_last = i;
			}
		}
		bSelected[now_last] = true;
		Output[m] = _max;
		last = now_last;
	}
	for (int i = 1; i <= N; i++) {
		cout << Output[i] << endl;
	}
	system("pause");
	return 0;
	/*int s[100100], a[100100];
	int Next[100100], Last, Now;
	int n, t, sum;
	priority_queue<int>Q;
	scanf_s("%d", &n);
	for (int i = 1; i <= n; i++)scanf_s("%d", &s[i]);
	for (int i = 1; i <= n; i++)scanf_s("%d", &a[i]);
	Next[n + 1] = n + 1;
	s[n + 1] = a[n + 1] = 0;
	for (int i = n; i >= 1; i--)
	{
		t = Next[i + 1];
		if (a[i] + s[i] * 2>a[t] + s[t] * 2)
			Next[i] = i;
		else Next[i] = t;
	}
	sum = 0;
	Last = Now = 0;
	for (int k = 1; k <= n; k++)
	{
		Last = Now;
		t = Next[Last + 1];
		if (Q.empty() || Q.top() + s[Last] * 2<a[t] + s[t] * 2)
		{
			sum += a[t];
			printf("%d\n", sum + s[t] * 2);
			Now = t;
		}
		else
		{
			sum += Q.top();
			Q.pop();
			printf("%d\n", sum + s[Last] * 2);
		}
		for (int i = Last + 1; i<Now; i++)
			Q.push(a[i]);
	}
	return 0;*/
}



#define N 1005
int t, l; int f[N];
char a[N];
bool pdhw(int i, int j) {
	i--, j--;
	while (i < j) {
		if (a[i] != a[j]) return false;
		i++, j--;
	}
	return true;
}
int main() {
	scanf_s("%d", &t);
	while (t--) {
		memset(a, 0, sizeof(a)); memset(f, 127, sizeof(f)); f[0] = -1;
		scanf_s("%s", a); l = strlen(a);
		for (int i = 1; i <= l; i++)
			for (int j = 1; j <= i; j++)
				if (pdhw(j, i)) f[i] = min(f[i], f[j - 1] + 1);
		printf_s("%d\n", f[l]);
	}
	return 0;
}
#define MAX_LEN_ 100001
int _max[MAX_LEN_], _min[MAX_LEN_], men[MAX_LEN_], f[MAX_LEN_];
int N;
int c_min = 1, c_max = 1;
void init() {
	scanf_s("%d", &N);
	for (int i = 1; i <= N; i++) {
		scanf_s("%d", men[i]);
	}
	if (men[1] > men[2]) {
		_max[1] = men[1];
		c_max++;

	}
	else {
		_min[1] = men[1];
		c_min++;
	}

}
int main() {
	int T;
	cin >> T;
	for (int t = 0; t < T; t++) {
		init();
		for (int j = 1; j < )
	}

	return 0;
}
#define MAX_LEN_ 100005
int t, n, ans; int men[MAX_LEN_], a[MAX_LEN_];
int main() {
	scanf_s("%d", &t);
	while (t--) {
		scanf_s("%d", &n); memset(men, 0, sizeof(men)); ans = 0;
		for (int i = 1; i <= n; i++) scanf_s("%d", &a[i]);
		for (int i = 1; i <= n; i++) {
			men[i] = max(men[i - 2] + a[i], men[i - 3] + a[i]);
			ans = max(ans, men[i]);
		}
		printf_s("%d\n", ans);
	}
	return 0;
}
int _N;
int _Crash[10001];
int men[10001];
int max_plus(int a, int b, int c) {
	int d;
	if (a > b)d = a; else d = b;
	if (d <= c) { d = c; }
	return d;
}
//_all:到第_i个（不含）的总数，_i第几个，_b第_i + 1个有没有被打劫
int inline dfs(int _i, bool _b) {
	if (_i == 0)return 0;
	int a = -1, b = -1, c = -1;
	if (_b == true) {
		a = dfs(_i - 1, false);
	}
	else {
		b = dfs(_i - 1, true) + _Crash[_i];
		c = dfs(_i - 1, false);
	}
	men[_i] = max_plus(a, b, c);
	return men[_i];
}
int main() {
	int _T;
	int a = max_plus(1, 3, 5);
	_N = 0;
	for (int i = 0; i < 10001; i++) {
		men[i] = -1;
	}
	cin >> _T;
	for (int i = 0; i < _T; i++) {
		for (int i = 0; i <= _N; i++) {
			men[i] = -1;
		}
		cin >> _N;
		for (int i = 1; i <= _N; i++) {
			cin >> _Crash[i];
		}
		men[1] = _Crash[1];
		dfs(_N, false);
		cout << men[_N] << endl;
	}
	return 0;
}

int map[101][101];
int MAX_LEN_;
int m[101][101];
int main()
{
	cin >> MAX_LEN_;
	for (int i = 1; i <= MAX_LEN_; i++) {
		for (int j = 1; j <= MAX_LEN_; j++) {
			cin >> map[i][j];
		}
	}
	m[MAX_LEN_][MAX_LEN_] = map[MAX_LEN_][MAX_LEN_];
	for (int i = MAX_LEN_ - 1; i >= 1; i--)
		m[i][MAX_LEN_] = m[i + 1][MAX_LEN_] + map[i][MAX_LEN_];
	for (int j = MAX_LEN_ - 1; j >= 1; j--)
		m[MAX_LEN_][j] = m[MAX_LEN_][j + 1] + map[MAX_LEN_][j];
	for (int i = MAX_LEN_ - 1; i >= 1; i--) {
		for (int j = MAX_LEN_ - 1; j >= 1; j--) {
			int t1 = m[i + 1][j] + map[i][j];
			int t2 = m[i][j + 1] + map[i][j];
			m[i][j] = min(t1, t2);
		}
	}
	cout << m[1][1];
	return 0;
}

int sel[20];
int num[20];
int n;
int t;
int res;
void a(int _k, int _r, int _i) {

	if (_k > n)return;
	for (int i = _i; i <= n; i++) {
		if (_r + num[i] == t) { res++; }
		else {
			a(_k + 1, _r + num[i], i + 1);
		}
	}
}
void a_do() {
	res = 0;
	cin >> n >> t;

	for (int i = 0; i <= n; i++) {
		sel[i] = 0;
		num[i] = 0;
	}
	for (int i = 1; i <= n; i++) {
		cin >> num[i];
	}
	sort(num, num + n + 1);
	a(1, 0, 1);
	cout << res;
}





