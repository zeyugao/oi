#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int main(){
	
	int L,n,m,d[50010]={0};
	
	cin>>L>>n>>m;
	
	d[0]=0;
	d[n+1]=L;
	for(int i =1;i<=n;i++){
		cin>>d[i];
	}
	//不可能跳0，所以从1开始 
	int l=1,r=L,mid;
	while(l<=r){
		mid=(r+l)>>1;
		int pre = 0;
		int remove =0;
		for(int i =1;i<=(n+1);i++){
			if(d[i]-d[pre]>=mid) pre =i;
			else  remove++;
		}
		//刚刚好也算可以跳更远 
		if(remove<=m){
			l = mid+1;
		}
		else{
			r = mid-1;
		}
	}
	// 这里为什么是r而不是l 
	cout<<r<<endl;
	return 0;
}
