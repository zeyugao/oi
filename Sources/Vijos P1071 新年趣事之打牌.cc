#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>

using std::cin;
using std::endl;
using std::cout;

//
//Summary:
//	装箱问题，这么多个物品，用其中几件装刚刚好剩余的重量
//
//	dp[i] += dp[i-weight[j]]
//

int dp[100001] = {0};	//记录方案数 
int pre[100001] = {0};	//记录dp转移而来的质量
int pos[100001] ={0};
int ans[101]={0};

void find(int current_weight){
	
	if(!current_weight){
		return;
	}
	
	find(pre[current_weight]);
	
	ans[pos[current_weight]] = 1;
	
}
int main(){
	
	int total_weight;
	int card_num;
	int card_weight[101]={0}; 
	
	cin>>total_weight>>card_num;
	
	for(int i = 1;i<=card_num;i++){
		cin>>card_weight[i];
	}
	dp[0] = 1;
	for(int i = 1;i<= card_num;i++){
		for(int j = total_weight;j>=card_weight[i];j--){//01背包的循环顺序 
			if(dp[j-card_weight[i]]){
				//条件判断是成功的
				//dp[j-card_weight[i]]>=1
				dp[j] += dp[j-card_weight[i]];
				//dp[j]如果是1，那就只有可能是dp[j]原先是不可到达的，而dp[j-w]的状态是可以到达的
				//说明，w是需要的
				if(dp[j] == 1){
					pre[j] = j - card_weight[i];	//记录转移而来的重量 
					pos[j] = i;						//记录当前选择了的牌 
				}
			}
		}
	} 
	
	if(dp[total_weight]>1){
		cout<<"-1"<<endl;
	}
	else if(dp[total_weight] == 0){
		cout<<"0"<<endl;
	}
	else{
		find(total_weight);//获取total_weight的质量的需要哪些card
		for(int i = 1;i<=card_num;i++){
			if(!ans[i]){
				cout<<i<<" ";
			}
		} 
	}
	return 0;
	
}
