#include<iostream>
#include<cstdio>
using namespace std;
struct data1 {
	int lm, rm, mx; //lm 表示tree[i]这个结点包含的区间的最左端必取时的最大值，rm同理，mx表示这个区间中最大值
	int sum;
	int l, r;
} tree[2000001];
int n, m;
int a[500001];
void update(int k) {
	tree[k].sum = tree[k << 1].sum + tree[k << 1 | 1].sum;
	tree[k].lm = max(tree[k << 1].lm, tree[k << 1].sum + tree[k << 1 | 1].lm);
	//k这个节点下，必取左边时最大值：左孩子的lm或者左孩子全部取+右孩子的lm
	tree[k].rm = max(tree[k << 1 | 1].rm, tree[k << 1].rm + tree[k << 1 | 1].sum);
	//rm同理
	tree[k].mx = max(max(tree[k << 1].mx, tree[k << 1 | 1].mx), tree[k << 1].rm + tree[k << 1 | 1].lm);
	//这棵树的最大值：左孩子的lm或右孩子的rm或从中间（这棵树的右孩子的lm+左孩子的rm）保证中间没有中断
}
void build(int k, int s, int t) {
	tree[k].l = s; tree[k].r = t;
	
	if (s == t) { tree[k].sum = tree[k].lm = tree[k].rm = tree[k].mx = a[s]; return; }
	
	int mid = (s + t) >> 1;
	build(k << 1, s, mid);
	build(k << 1 | 1, mid + 1, t);
	//放在最后，要自下而上更新
	update(k);
}
data1 ask(int k, int p, int q) {
	data1 g, h, a;
	int l = tree[k].l, r = tree[k].r;
	
	//二分法，找到区间，满足结点k的范围就是传递下来的范围，可以直接调用
	if (l == p && q == r) { return tree[k]; }
	
	int mid = (l + r) >> 1;
	
	if (q <= mid) { return ask(k << 1, p, q); }
	else if (p > mid) { return ask(k << 1 | 1, p, q); }
	else {
		g = ask(k << 1, p, mid);
		h = ask(k << 1 | 1, mid + 1, q);
		//分别向左右询问
		//这里之所以不能直接调用在update()中应用好的，
		//是因为ask的区间可能并不是update过的，需要二分再次计算
		
		//ask过程原理与update原理相同
		a.mx = max(max(g.mx, h.mx), g.rm + h.lm);
		a.rm = max(h.sum + g.rm, h.rm);
		a.lm = max(g.lm, g.sum + h.lm);
		return a;
	}
}
//修改叶节点值，并update
void change(int k, int x, int y) {
	int l = tree[k].l, r = tree[k].r;
	
	if (l == r) { tree[k].sum = tree[k].lm = tree[k].rm = tree[k].mx = y; return; }
	
	int mid = (l + r) >> 1;
	
	if (x <= mid) { change(k << 1, x, y); }
	else if (x > mid) { change(k << 1 | 1, x, y); }
	
	update(k);
}
int main() {
	scanf("%d%d", &n, &m);
	
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	
	build(1, 1, n);
	
	for (int i = 1; i <= m; i++) {
		int t, x, y;
		scanf("%d%d%d", &t, &x, &y);
		
		if (t == 1) {
			if (x > y) { swap(x, y); }
			
			printf("%d\n", ask(1, x, y).mx);
		}
		
		if (t == 2) { change(1, x, y); }
	}
	
	return 0;
}