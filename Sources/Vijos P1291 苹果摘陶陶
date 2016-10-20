#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
bool cmp(int a,int b){
	return a>b;
}
int main(){
	int n,m;
	int tao[2001],apple[2001];
	memset(tao,0,sizeof(tao));
	memset(apple,0,sizeof(apple));
	cin>>n>>m;
	for(int i= 1;i<=n;i++){
		cin>>apple[i];
	}
	for(int i = 1;i<=m;i++){
		cin>>tao[i];
	}
	sort(tao+1,tao+m+1,cmp);
	int left=m;
	for(int i =1;i<=n;i++){
		for(int j = 1;j<=m;j++){
    //题目中的是"只能在它所能摘到的高度以下的最高的陶陶"，当且仅当苹果的高度严格大于陶陶的高度时，才可以摘到
			if(apple[i]>tao[j]&&tao[j]!=0){
				tao[j]=0;
				left--;
				break;
			}
		}
	}
	cout<<left;
	return 0;
}



///////////////////////////////////////////////////////
//这是我一开始的思路，用优先队列，每次取出最高的陶陶和最高的苹果，两个比较，如果陶陶的高度没有苹果的高度高，那么就可以摘下来，否则，就不断取出第一个比苹果矮的陶陶，由于这是优先队列，比最高的苹果还要高的陶陶一定无法被摘到，就可以被直接pop()掉，为什么无法AC呢

#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
int main(){
	int n,m;
	priority_queue<int> tao;
	priority_queue<int> apple;
	cin>>n>>m;
	int tmp;
	for (int i =1 ;i<=n;i++){
		cin>>tmp;apple.push(tmp);
	}
	for(int i =1;i<=m;i++){
		cin>>tmp;tao.push(tmp);
	}
	int left=0;
	while(!apple.empty()&&!tao.empty()){
		int h_apple =  apple.top();apple.pop();
		int h_tao = tao.top();tao.pop();
		
		if(h_apple<=h_tao){
			left++;
			while(!tao.empty()){
				h_tao = tao.top();tao.pop();
				if(h_tao<h_apple)break;
				left++;
			}
		}
	}
	cout<<left;
	return 0;
}
