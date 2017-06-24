#include <iostream>
using namespace std;
int N, M;

int maxn = 9999999;
int min_Ans = maxn;
void dfs(int n, int v, int s, int r, int h) {
	if (n == 0) {
		if (v == N && min_Ans > s) {
			min_Ans = s;
		}
	}
	if (s > min_Ans) { return; }
	if (v > N) { return; }
	/*
		2Ri+1 * Hi+1{这里略去了pi，因为题目中已经全部可以同除pai} = 2*Ri+1*pai*Hi+1 = Si+1
		2Vi= 2Ri+1 * Ri+1 * Hi+1 + ...+ 2Rm * Rm * Hm= Ri+1 *  Si+1 + ...+ Rm * Sm ≤ Ri+1 * (Si+1+ ...+ Sm)= Ri+1 * FSi
		所以: FSi ≥ 2Vi / Ri+1
		因此剪枝条件为：
		if  Si-1 + 2 * Vi-1 / Ri >当前最优值 then exit
	*/
	//V-v剩下的体积
	if ((s + 2 * (N - v) / r) >= min_Ans) { return; }
	if ((r - 1) < n || (h - 1) < n) { return; }
	int ns, nv;
	for (int i = r - 1; i > 0; --i) {
		for (int j = h - 1; j > 0; --j) {
			nv = v + i * i * j;
			ns = s + 2 * i * j;
			if (n == M/*最上面一层有个顶面*/) { ns += i * i; }
			dfs(n - 1, nv, ns, i, j);
		}
	}
}
int main() {

	cin >> N >> M;
	dfs(M, 0, 0, 100, 100);
	if (min_Ans == maxn) {
		min_Ans = 0;
	}
	cout << min_Ans << endl;
	
	
	return 0;
}
