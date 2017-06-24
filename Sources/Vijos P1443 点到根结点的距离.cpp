#include <cstdio>
#include<cmath>
const int Max = 30001;
int t, father[Max], x, y, r[Max], root[Max];
char ch;
int find(int k) {
	if (k == father[k]) { return k; }
	
	int temp = find(father[k ]);
	
	//1.如果前一个步骤是合并，此时，father[k]由father[k] = temp;可知这个是根结点，
	//             根节点已经更新为前一大段的距离，此时r[k]=r[father[k]]+r[k]就是本段树的相对本段根节点距离+本段根结点到前一大段根结点的距离
	//             即总距离
	//2.如果前一次操作是查询，r[father[k]]=0，r[k]值不变
	//3.第一次查询，r[k]=0，r[father[k]]=0
	r[ k] = r[father[k ]] + r[k];
	
	//将本节点直接挂在根节点上，便于下一次的find时r[]更新
	father[ k] = temp;
	return temp;
}
int main() {
	scanf("%d", &t);
	
	for (int i = 1; i < Max; i++) {
		father[i] = i; r[i] = 0, root[i] = 1; //r表示到根节点的距离
	} //root 表示该树节点个数
	
	while (t--) {
		getchar();
		scanf("%c%d%d", &ch, &x, &y);
		int tempx = find(x), tempy = find(y);
		
		if (ch == 'M') {
			father[tempx] = tempy; //X 接到 y
			r[tempx] = root[tempy]; //更新距离
			root[tempy] += root[tempx]; //更新树节点个数
		}
		else if (tempx != tempy) { printf("-1\n"); }
		else { printf("%d\n" , (int)fabs(r[x] - r[y]) - 1); }
		
		//直接相减去头/尾，再减1去掉剩下的
	}
	
	return 0;
};
