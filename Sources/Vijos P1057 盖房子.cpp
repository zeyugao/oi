#include <iostream>
using namespace std;
int map[1001][1001]={0};
int dp[1001][1001]={0};
int main(){
	int n,m;
	
	cin>>n>>m;
	for(int i =1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>map[i][j];
		}
	}
	
	int ans=0;
	for(int i =1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(map[i][j]){
        //向左向上向左上所能延伸的最大值
        //三个方向的延伸长度要保持一样长，于是就取最小值
				dp[i][j] = min(dp[i-1][j],min(dp[i][j-1],dp[i-1][j-1]))+1;
				ans = max(dp[i][j],ans);
			}
		}
	}
	cout<<ans<<endl;
	
	return 0;
}
