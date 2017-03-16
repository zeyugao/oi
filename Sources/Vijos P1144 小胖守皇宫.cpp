#include <iostream>
#include <algorithm>
#include <string.h>

//这里要×2，为的是双向路径
const int maxn =1510*2;

using namespace std;

struct edge{
	int to;
	edge *next;
}e[maxn],*pt =e,*head[maxn];
void addedge(int f,int t){
	pt->to = t;
	pt->next = head[f];
	head[f] = pt++;
}

void add(int f,int t){
	addedge(f,t);
	addedge(t,f);
}
int cost[maxn];
int dp[maxn][3];
//0:由子节点守，1:由自己守，2:由父节点守 
void dfs(int x,int fa){
	
	dp[x][1] = cost[x];
	//一开始这里只初始化了一个，只过了三个点
	dp[x][2] =dp[x][0]=0;
	int flag = 0xffff;
	for(edge *t =head[x];t;t=t->next){
		if(t->to == fa) continue;
		dfs(t->to,x);
		
		//这里如果是前者更优，那么状态是确定的，由子节点守卫是可行的
		//但是，如果由子节点的子节点守卫，就会产生歧义
		//后面就是要进行对这个的状态修改，使其满足条件 
		dp[x][0] +=min(dp[t->to][1],dp[t->to][0]); 
		
		
		dp[x][1] += min(dp[t->to][1],min(dp[t->to][0],dp[t->to][2]));
		dp[x][2] += min(dp[t->to][1],dp[t->to][0]);
		
		
		//这一个条件判断为真的话，那就是所明前面的
		//dp[x][0] +=min(dp[t->to][1],dp[t->to][0]);
		//中选择的是前者，状态就是确定的
		//flag直接判为0，不需要进行后面的判断 
		if(dp[t->to][1]<= dp[t->to][0]){
			flag=0;
		}
		
		//如果dp[x][0] +=min(dp[t->to][1],dp[t->to][0]);
		//选择的是后者，就是说明状态未确定，不可能由子节点的子节点进行守卫
		//就说明必须要将其中一个子节点守卫
		//
		//如果在判断的过程中，遇到了能使dp[t->to][1]<= dp[t->to][0]的节点，直接用就可以了
		//
		//否则，flag里面，就储存了将全部的子节点中的其中一个变为守卫状态的最小代价 
		if(flag&&dp[t->to][1] - dp[t->to][0]<flag){
			flag = dp[t->to][1]- dp[t->to][0];
		}
	}
	dp[x][0] +=flag;
	
}

int main(){
	
	int n;
	cin>>n;
	memset(dp,0x3f,sizeof(dp));
	int temp_get_root[maxn]={0};
	for(int i =1;i<=n;i++){
		int index,m;
		
		cin>>index;
		cin>>cost[index]>>m;
		for(int j =1;j<=m;j++){
			int t;
			cin>> t;
			add(t,index);
			temp_get_root[t]=1;
		}
	}
	int root;
	for(int i =1;i<=n;i++){
		if(!temp_get_root[i]){
			root =i;
			break;
		}
	}
	dfs(root,-1);
	cout<<min(dp[root][0],dp[root][1]);
	return 0;
	
}
