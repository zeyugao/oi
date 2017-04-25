#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>

using std::cin;
using std::endl;
using std::cout;

int n,M,T;
struct Dream{
	int M,T;
}dream[110];
int dp[210][210]={0};
int main(){
	
	memset(dream,0,sizeof(dream));
	
	cin>>n>>M>>T;
	
	for(int i =1;i<=n;i++){
		cin>>dream[i].M>>dream[i].T;
	}
	
	for(int i = 1;i<=n;i++){
		for(int j = M;j>=dream[i].M;j--){
			for(int k = T;k>=dream[i].T;k--){
				dp[j][k] = (std::max)(dp[j][k],dp[j-dream[i].M][k-dream[i].T]+1);
			}
		}
	}
	cout<<dp[M][T];
	return 0;
}
