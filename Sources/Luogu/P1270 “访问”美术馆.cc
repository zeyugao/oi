#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>

using std::cin;
using std::endl;
using std::cout;

const int kMaxNum = 1000+1;

//Summary:
//	树形dp
//	dp[i][j] ：**回到**i节点时，在该节点及其子节点花费了j的时间
//	dp[i][j] = max{dp[i][j],dp[left_node][time]+dp[right_node][j-time]
//	因为这个是二叉树，所以可以直接对左右两个节点进行合并，而不用一个一个子节点进行对前面的节点的合并
//	

int dp[kMaxNum][kMaxNum];
int max_time;

//cnt是在后序遍历中进行编号的递加序号
//加1即为左子树
//当进行过一次完整的（到底了的）遍历后，编号已经将所有的（以这个节点为根的）的左子树都标记了
//这时候的在这个节点上cnt+1的才是右子树 
int cnt = 0;

void Dfs(){
	int time,painting_num;
	cin>>time>>painting_num;
	
	int root = ++cnt;
	//这个的二叉树结构有些不同，这里的二叉树是从某一个节点先走完这一条边，才进行分叉，分叉就是直接进入到下一个节点中了 
	//而不是先分叉，再走完各自的可能不相同的变得距离 
	time <<=1;
	//走廊从当前位置到下一个走廊的尽头再回来需要双倍的时间
	//<=>当前节点到下一个节点需要双倍的边距离代价 
	
	if(painting_num){//为叶子节点 
		for(int i = time;i<=max_time;i++){
			dp[root][i] = (std::min)(painting_num,(i - time)/5);
			//判断能取多少 
		}
	}
	else{
		int left = cnt + 1;
		Dfs();
		int right = cnt + 1;
		Dfs();
		
		//总共在这颗父节点上花费的时间，至少为time（走完走廊的时间）
		for(int all_time = time;all_time<=max_time;all_time++){
			//花在左子树上的时间，不允许超过总时间(这是肯定的）-通过走廊的双倍时间（ 这点时间是不能用在子树上的）
			//<=>available_time_on_child = all_time - time
			for(int left_time = 0;left_time <= all_time - time;left_time++){
				//dp[root][all_time]
				//
				//dp[left][left_time] + 
				//dp[right][all_time - time - left_time]
				//all_time - time - left_time
				//available_time_on_child - left_time = right_time 
				dp[root][all_time] = (std::max)(dp[root][all_time],dp[left][left_time] + dp[right][all_time - time - left_time]);
			}
		} 
		
	}
}

int main(){
	
	memset(dp,0,sizeof(dp));
	cin>>max_time;
	
	//因为要在警察来到之前，所以在max_time-1的时候就要回到出口以逃脱 
	max_time--;
	Dfs();
	
	cout<<dp[1][max_time];
	
	return 0;
}
