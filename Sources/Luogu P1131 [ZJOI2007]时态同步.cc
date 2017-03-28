#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>

using std::cin;
using std::endl;
using std::cout;

//Summary
//	自下而上
//	同一个父节点的叶子节点到这个节点的时间必定是一样的
//	就直接强制每个叶子节点到父节点的时间一样
//	

const int kMaxNum = 500000;
struct Edge{
	int from;
	int to;
	int weight;
	int next;
}edge[kMaxNum*2+10];
int edge_count = 0;
int edge_first[kMaxNum*2+10] = {0};
void AddSingleEdge(int from,int to,int weight){
	edge[edge_count++].from = from;
	edge[edge_count].to = to;
	edge[edge_count].weight = weight;
	edge[edge_count].next = edge_first[from];
	edge_first[from] = edge_count;
}
void AddEdge(int from,int to,int weight){
	AddSingleEdge(from,to,weight);
	AddSingleEdge(to,from,weight);
}

int node_num;

int time_from_leaf[kMaxNum+10];	//从这个节点的所有叶子节点到这个节点的时间的最大值

long long ans = 0;
void dfs(int x,int fa){
	for(int i = edge_first[x];i;i=edge[i].next){
		if(edge[i].to != fa){
			dfs(edge[i].to,x);
			time_from_leaf[x] = (std::max)(time_from_leaf[x],time_from_leaf[edge[i].to]+edge[i].weight);
		}
	}
	for(int i = edge_first[x];i;i=edge[i].next){
		if(edge[i].to != fa){
			//强制同步边权，将走的时间短的全部同步到最长的时间
			//因为子节点的子节点已经被同步了边权，time_from_leaf[edge[i].to]就是所有的子节点的边权了
			ans += time_from_leaf[x] - time_from_leaf[edge[i].to] - edge[i].weight;
		}
	}
}
int main(){
	int root;
	cin>>node_num>>root;
	for(int i =1;i<=node_num-1;i++){
		int a,b,weight;
		cin>>a>>b>>weight;
		AddEdge(a,b,weight);
	}
	dfs(root,0);
	
	cout<<ans;
	return 0;
}
