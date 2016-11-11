#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int check[10010]={0},enable[10010]={0};
int s,t;
int n,m;
vector<int> g[10010],gl[10010];
void predfs(int n){
	if(check[n])return;
	check[n]=1;
	for(int i = 1;i<=gl[n].size();i++){
		predfs(g[n][i]);
	}
}
void make_enable(){
	for(int i = 1;i<=10010;i++){
		if(enable[i])continue;
		bool ok=true;
		for(int j =1;j<=g[i].size();j++){
			if(!check[g[i][j]]){
				ok=false;
				break;
			}
		}
		if(ok) enable[i]=1;
	}
}
int dis[10010];
int spfa(){
	queue<int> q;
	memset(dis,0x3f,sizeof(dis));
	int vis[10010]={0};
	q.push(s);
	vis[s]=1;
	while(!q.empty()){
		int x = q.front();q.pop();vis[x] = 0;
		for(int k = 1;k<=g[x].size();i++){
			int y = g[x][i];
			if(d[x]+1<d[y]){
				d[y] = d[x]+1;
				if(!vis[y]){
					vis[y] = 1;
					q.push(y);
				}
			}
		}
	}
}
int main(){
	
	
	cin>>n>>m;
	for(int i = 1;i<=m;i++){
		int f,t;
		cin>>f>>t;
		g[f].push_back(t);
		gl[t].push_back(f);
	}
	cin>>s>>t;
	predfs(t);
	make_enable();
	
	spfa();
	
	return 0;
}
