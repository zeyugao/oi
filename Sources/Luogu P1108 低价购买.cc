#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>

using std::cin;
using std::endl;
using std::cout;

int n;
int stock[5010]={0};
int times[5010]={0};
int case_num[5010]={0};
int main(){
	cin>>n;
	int Max = -1;
	
	for(int i = 1;i<=n;i++){
		cin>>stock[i];
		
		for(int j = 1;j<i;j++){
			if(stock[j]>stock[i]&&	//股票价格更低
				times[j]>times[i]){	//原先可以买的次数更多了
				//用原先的方案来接在现在的前面，一定可以获得更优解
				times[i] = times[j];
			}
		}
		times[i]++;
		if(times[i]==1){
			//原来没有更好的方案，从现在从新开始，方案数置为1
			case_num[i]=1;
		}
		for(int j =1 ;j<i;j++){
			if(times[i] - 1 == times[j] && stock[j] > stock[i]){
				//次数少一次，并且价格以前的更高，再买一次
				//相同的次数
				//方案数当前的就可以直接加上去
				case_num[i]+=case_num[j];
			}
			else if(times[i] == times[j]&&stock[i] == stock[j]){
				//相同次数，相同价格，前面的一定会比后面的更优，至少不会亏
				case_num[j] = 0;
			}
		}
		if(Max<times[i]){
			Max = times[i];
		}
	}
	int ans = 0;
	for(int i = 1;i<=n;i++){
		if(times[i] == Max){
			ans += case_num[i];
		}
	}
	cout<<Max<<" "<<ans<<endl;
	
	
	
	return 0;
}
