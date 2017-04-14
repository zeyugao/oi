#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>

using std::cin;
using std::endl;
using std::cout;

//Summary:
//	组合数
//	每一列，每一行最多只能放两个
//	dp[i][j][k]
//		放完了前i行，每一列有一个棋子的有j列，每一列有2个棋子的有k列
//		那么，显然，每一列没有棋子的有m-j-k列


const long long kMod = 9999973;


//首先，大变量不要放在局部函数中，直接放在全局变量中
//	防止栈溢出
long long dp[110][110][110];
int n,	//行
	m;	//列
void debug(){
	for(int i = 0;i<= n;i++){
		for(int j = 0;j<=m;j++){
			for(int k = 0;j+k<=m;k++){
				printf("dp[%d][%d][%d]=%d\n\r",i,j,k,dp[i][j][k]);
			}
		}
	}
}

long long C(long long i){
	return (i * (i-1))/2;
}
int main(){
	
	
	cin>>n>>m;
	
	memset(dp,0,sizeof(dp));
	dp[0][0][0] = 1;
	for(int i = 1;i <= n;i++){	//放第i行
		for(int j = 0;j <= m;j++){			//有j列只有1个棋子
			for(int k = 0;j+k <= m;k++){
				
				//不在第i行放棋子
				dp[i][j][k] += dp[i-1][j][k];
				
				//dp转移方程中，dp转移的限定条件
				//	与dp的是否会使用到负地址都要考虑呀
				
				//为什么，这一题，考虑了dp转移的限制条件就爆炸了
				
				//在空白的列上放1个棋子
				if(j>=1 /*&& m-(j-1)-k>=1*/){
					//放了之后，会导致有一个棋子的列增多1个
					dp[i][j][k] += dp[i-1][j-1][k] * (m-(j-1)-k);
				}
				
				//在两个空白列上分别放上1个棋子
				if(j>=2 /*&& m-(j-2)-k>=2*/){
					//放了之后，会导致有一个棋子的列增多2个
					dp[i][j][k] += dp[i-1][j-2][k] * C(m-(j-2)-k);
				}
				
				//在有一个棋子的列上放1个棋子
				if(k>=1 /*&& j>=1*/){
					//放了之后，会导致有一个棋子的列减少一个
					//	有两个棋子的增多一个
					dp[i][j][k] += dp[i-1][j+1][k-1] * (j+1);
				}
				
				//在有一个棋子的两列上各放1个棋子
				if(k>=2 /*&& j>=2*/){
					//放了之后，会导致有一个棋子的列减少两个
					//	有两个棋子的增多两个
					
					//从j个元素中选出2个进行组合
					dp[i][j][k] += dp[i-1][j+2][k-2] * C(j+2);
				}
				
				//在一列只有1个棋子的列以及没有棋子的列各放上一个棋子
				if(k>=1 /*&& j>=1 && m-(j-2)-k >= 1*/){
					//放了之后，会导致有一个棋子的列不变（增加一个又减少一个）
					//	有两个棋子的增多一个
					dp[i][j][k] += dp[i-1][j][k-1] * (m-j-(k-1)) * (j);
				}
				dp[i][j][k] %= kMod;
				//debug();
			}
		}
	}
	
	long long ans = 0;
	for(int i = 0;i<= m;i++){
		for(int j = 0;i+j <= m;j++){
			ans = (ans + dp[n][i][j]) % kMod;
		}
	}
	
	cout<<ans<<endl;
	return 0;
}
