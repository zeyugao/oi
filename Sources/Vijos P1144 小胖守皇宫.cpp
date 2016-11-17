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
		
		dp[x][0] +=min(dp[t->to][1],dp[t->to][0]); 
		dp[x][1] += min(dp[t->to][1],min(dp[t->to][0],dp[t->to][2]));
		dp[x][2] += min(dp[t->to][1],dp[t->to][0]);
		
		
		//根据dp原则，下面的点一定会选择更优解，也就是如果不守比守更优，会选择这个，这时候父节点就会因为子节点是由于子节点的子节点守而导致没有可以防守的
		 
		if(dp[t->to][1]<= dp[t->to][0]){
			flag=0;
		}
		
		if(flag&&dp[t->to][1]- dp[t->to][0]<flag){
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
