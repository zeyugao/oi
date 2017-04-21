#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>

using std::cin;
using std::endl;
using std::cout;
int map[110][110]={0};

int dp[110][110]={0};
int main(){
	
	int n,m;
	cin>>n>>m;
	for(int i = 1;i<=n;i++){
		for(int j = 1;j<=m;j++){
			cin>>map[i][j];
		}
	}
	
	for(int i = 1;i<=n;i++){
		for(int j = 1;j<=m;j++){
			if(map[i][j] == 1){
				//要有不包含0的正方形
				//由于增加了两条小边，就要考虑这两条小边能够到达哪里
				
				dp[i][j] = (std::min)(dp[i-1][j],(std::min)(dp[i][j-1],dp[i-1][j-1]))+1;
			}
		}
	}
	
	int ans = 0;
	for(int i = 1;i<=n;i++){
		for(int j = 1;j<=m;j++){
			ans = (std::max)(ans,dp[i][j]);
		}
	}
	cout<<ans<<endl;
	return 0;
}
