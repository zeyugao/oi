//还没过，是不是邻接表的问题？
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

struct

void AddEdge(int from, int to,int cost){
	pt->to = to;
	pt->next = head[from];
	pt->cost = cost;
	head[from] =pt++;
}

int node_num;
int user_num;
int user_fee[kMaxNum];

int dp[kMaxNum][kMaxNum];


//Summary:
//	dp[i][j]:i节点下选择了j个叶节点时能够产生的最大收入
//	dp[i][j] = max{dp[i][j],dp[i][j-k] + dp[i.son][k] - cost[i]}
//	如果要加入这一条边，则总收入要减去这一条边所花费的价格

 
int Dfs(int current_node){
	if(current_node >= node_num-user_num + 1){//到达用户节点 
		dp[current_node][1]  = user_fee[current_node];
		return 1;
	}
	//每次添加一个新的子树，根据前面的dp状态可得，这一棵子树一定是没有添加进状态的
	//在对新的dp状态进行更新时，总是用以前的（没有这一个子树）状态+对新的子树的状态加起来进行更新
	//保证当前的是对新的子树进行加入更新，不会影响前面子树的选择 
	
	int sum =0;//统计到第i个子节点，共有多少个叶子节点 
	for(Edge * to = head[current_node];to;to = to->next){
		
		int x = Dfs(to->to);
		
		sum+=x;
		
		for(int j = sum;j>=1;j--){
			for(int k = 1;k<=x;k++){
				//对于不选择新加入的子树的任意一个节点，就是还没有更新时的dp[current_node][sum-x]
				//如果没有加入新子树反而比加入了新子树收入大，那么这个状态一定可以保存下来 
				dp[current_node][j] = (std::max)(dp[current_node][j],dp[current_node][j-k] + dp[to->to][k] - to->cost);
			}
		}
	}
	return sum;
}

int main(){
	cin>>node_num>>user_num;
	
	for(int current_node =1;current_node<= node_num-user_num;current_node++){
		int user_num_temp;
		int next_node;
		int cost;
		cin>>user_num_temp;
		for(int i = 1;i<= user_num_temp;i++){
			cin>>next_node>>cost;
			AddEdge(current_node,next_node,cost);
		}
	}
	
	for(int i = node_num-user_num+1;i<=node_num;i++){
		cin>>user_fee[i];
	}
	memset(dp,-60,sizeof(dp));
	
	for(int i = 1;i<=node_num;i++){
		dp[i][0] = 0;
		
	}
	
	Dfs(1);
	
	for(int i = user_num;i>=1;i--){
		printf("num:%d %d\n",i,dp[1][i]);
	}
	for(int i = user_num;i>=1;i--){
		//这里判断的是dp状态大于0即可，所以前面的memset一定要取到负值
		//以后的memset除非特殊要求，要取小的值，就直接取负吧 
		if(dp[1][i]>=0){
			cout<<i<<endl;
			break;
		}
	}
	
	return 0;
}
