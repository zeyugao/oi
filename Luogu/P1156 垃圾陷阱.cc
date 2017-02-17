#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

struct Trash{
	int live;
	int time;
	int height;
};

//Summary:
//	dp[i]：堆到高度为i的时候，所能达到的最大生命值
//	dp[i+h] = max(dp[i],dp[i+h])
int main(){
	int depth;
	int trash_num;
	Trash trash[101]={0};
	
	cin>>depth>>trash_num;
	
	for(int i =1 ;i<=trash_num;i++){
		cin>>trash[i].time>>trash[i].live>>trash[i].height;
	}
	
	int dp[101];
	memset(dp,-1,sizeof(dp));
	dp[0] = 10;
	
	for(int i = trash_num;i++){
		for(int j = depth;j>=0;j--){
			
		}
	}
	
	return 0;
}
