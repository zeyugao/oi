#include <iostream>
#include <string.h>
using namespace std;

const int maxn =2001;
int map[maxn][maxn]={0};
int n,m;
int dp[maxn][maxn]={0};
int max_squre(int target,int &ans){
	memset(dp,0,sizeof(dp));
	for(int i =1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(map[i][j]==target){
				dp[i][j] = min(dp[i-1][j],min(dp[i][j-1],dp[i-1][j-1]))+1;
				ans = max(dp[i][j]*dp[i][j],ans);
			}
		}
	}
}


int max_rectangle(int target,int& ans){
	int dpl[2][maxn],dpr[2][maxn],templ[maxn],tempr[maxn];
	memset(dp,0,sizeof(dp));
	memset(dpl,0,sizeof(dpl));
	memset(dpr,0,sizeof(dpr));
	memset(templ,0,sizeof(templ));
	memset(tempr,0,sizeof(tempr));
	
	
	
	int mx =0;
	for(int i =1;i<=m;i++){
		dpl[0][i]=0,dpr[0][i]=m;
	}
	for(int i =1;i<=n;i++){
		//预处理，获取该行的某个点能到达的最左以及最右，展示不考虑dp 
		int tmp =1;
		for(int j =1;j<=m;j++){
			if(map[i][j]!=target) tmp = j+1;
			else templ[j] = tmp;
		}
		tmp =m;
		for(int j=m;j>=1;j--){
			if(map[i][j]!=target) tmp = j-1;
			else tempr[j] = tmp;
		}
		for(int j =1;j<=m;j++){
			if(map[i][j]!=target){
				dp[i&1][j]=0,dpl[i&1][j] =1,dpr[i&1][j] = m;
				continue;
			}
			dp[i&1][j] = dp[(i&1)^1][j]+1;
			//由于是一个矩形 
			dpl[i&1][j] = max(dpl[(i&1)^1][j],templ[j]);
			dpr[i&1][j] = min(dpr[(i&1)^1][j],tempr[j]);
			mx = max((dpr[i&1][j]-dpl[i&1][j]+1/*加上自己*/)*dp[i&1][j],mx);
			
		} 
		
	}
	ans = max(ans,mx);
	
}
int main(){
	cin>>n>>m;
	
	//pre init
	for(int i =1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>map[i][j];
			if((i+j)%2==1){
				map[i][j] = 1-map[i][j];
			}
		}
	}
	
	
	//最大正方形 
	int ans=0;
	
	max_squre(1,ans);
	max_squre(0,ans);
	
	cout<<ans<<endl;
	
	///最大子矩阵 
	max_rectangle(1,ans);
	max_rectangle(0,ans);
	cout<<ans<<endl;
	
	return 0;
}
