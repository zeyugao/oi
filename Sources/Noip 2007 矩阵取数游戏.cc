#include <iostream>
#include <string.h>
#include "BigNum.h"
using namespace std;

int main(){
	long long n,m,num[81][81]={0};
	
	cin>>n>>m;
	
	for(int i =1;i<=n;i++){
		for(int j=1;j<=m;j++){
			
			cin>>num[i][j];
			
			
		}
	}
	BigNum dp[81][81];
	memset(dp,0,sizeof(dp));
	
	BigNum ans =0;
	for(int row =1;row<=n;row++){
		memset(dp,0,sizeof(dp));
		for(int j =1;j<=m;j++){
			dp[j][j] = num[row][j]*2;
		}
		
		//长度的循环在外层,保证每一段一定长度的数字先被处理完,而不能是定开始,改长度,这样会导致有一些最优解没有被记录
		for(int i =1;i<m;i++){
			for(int j =1;j<=m;j++){
				if(i+j>m)break;
				dp[j][j+i] = max(dp[j+1][j+i]+num[row][j],dp[j][j+i-1]+num[row][i+j])*2;
			}
		}
		ans += dp[1][m];
	}
	cout<<ans<<endl;
	return 0;
}
