#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>

using std::cin;
using std::endl;
using std::cout;

const int kMaxNum = 3000 + 10;

struct Edge {
	int to;
	int cost;
	int next;
}edge[kMaxNum];
int edge_count = 0;
int edge_first[kMaxNum] = { 0 };
void AddEdge(int from, int to, int cost) {
	edge_count++;
	edge[edge_count].to = to;
	edge[edge_count].cost = cost;
	edge[edge_count].next = edge_first[from];
	edge_first[from] = edge_count;
}

int node_num;
int user_num;
int user_fee[kMaxNum];

int dp[kMaxNum][kMaxNum];

int Dfs(int current_node) {
	if (current_node >= node_num - user_num + 1) {//到达用户节点 
		dp[current_node][1] = user_fee[current_node];
		return 1;
	}
	//每次添加一个新的子树，根据前面的dp状态可得，这一棵子树一定是没有添加进状态的
	//在对新的dp状态进行更新时，总是用以前的（没有这一个子树）状态+对新的子树的状态加起来进行更新
	//保证当前的是对新的子树进行加入更新，不会影响前面子树的选择 

	int sum = 0;//统计到第i个子节点，共有多少个叶子节点 
	for (int to = edge_first[current_node]; to; to = edge[to].next) {

		int x = Dfs(edge[to].to);

		sum += x;

		for (int j = sum; j >= 1; j--) {
			for (int k = 1; k <= x; k++) {
				//对于不选择新加入的子树的任意一个节点，就是还没有更新时的dp[current_node][sum-x]
				//如果没有加入新子树反而比加入了新子树收入大，那么这个状态一定可以保存下来

				//current_node的子树分了j-k个，剩下k个由前面的子树来分，类似于完全背包
				dp[current_node][j] = (std::max)(dp[current_node][j], dp[current_node][j - k] + dp[edge[to].to][k] - edge[to].cost);
			}
		}
	}
	return sum;
}

//Summary:
//	dp[i][j]:i节点下选择了j个叶节点时能够产生的最大收入
//	dp[i][j] = max{dp[i][j],dp[i][j-k] + dp[i.son][k] - cost[i]}
//	如果要加入这一条边，则总收入要减去这一条边所花费的价格

int main() {
	cin >> node_num >> user_num;

	for (int current_node = 1; current_node <= node_num - user_num; current_node++) {
		int user_num_temp;
		int next_node;
		int cost;
		cin >> user_num_temp;
		for (int i = 1; i <= user_num_temp; i++) {
			cin >> next_node >> cost;
			AddEdge(current_node, next_node, cost);
		}
	}

	for (int i = node_num - user_num + 1; i <= node_num; i++) {
		cin >> user_fee[i];
	}
	memset(dp, -60, sizeof(dp));

	for (int i = 1; i <= node_num; i++) {
		dp[i][0] = 0;
	}

	Dfs(1);

	for (int i = user_num; i >= 1; i--) {
		//printf("num:%d %d\n", i, dp[1][i]);
	}
	for (int i = user_num; i >= 1; i--) {
		//这里判断的是dp状态大于0即可，所以前面的memset一定要取到负值
		//以后的memset除非特殊要求，要取小的值，就直接取负吧 
		if (dp[1][i] >= 0) {
			cout << i << endl;
			break;
		}
	}
	//system("pause");
	return 0;
}
