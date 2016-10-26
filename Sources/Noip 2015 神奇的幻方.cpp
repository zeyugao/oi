//审题不仔细是大坑
//鄙视Vijos的g++，连个std::hash与我的hashw都没法好好区别
#include <iostream>
#include <cstring>
using namespace std;
struct _hash{
	int x,y;
};
int k;
int map[40][40]={0};
_hash myhash[40*40]={0};
	int n;
void set(int k,int x,int y){
	myhash[k].x = x;
	myhash[k].y = y;
	map[x][y]=k;
}
void out(){
	for(int x=1;x<=n;x++){
		for(int y = 1;y<=n;y++){
			cout<<map[x][y]<<" ";
		}
		cout<<endl;
	}
}
void work(){
	for(k =2;k<=n*n;k++){
		if(myhash[k-1].x==1&&myhash[k-1].y!=n){
			set(k,n,myhash[k-1].y+1);
		}
		else if(myhash[k-1].y==n&&myhash[k-1].x!=1){
			set(k,myhash[k-1].x-1,1);
		}
    //这里原来看成最后一列 ,.x==n ......
		else if(myhash[k-1].x==1&&myhash[k-1].y==n){
			set(k,2,n);
		}
		else if(myhash[k-1].x!=1&&myhash[k-1].y!=n){
			
			if(map[myhash[k-1].x-1][myhash[k-1].y+1]==0){
				set(k,myhash[k-1].x-1,myhash[k-1].y+1);
			}
			else{
        //原来写成set(k,myhash[k-1].x+1,myhash[k-1].y-1);
        //将"否则将 K填在(K- 1) 的正下方"以为和上面一样，填在左下方
				set(k,myhash[k-1].x+1,myhash[k-1].y);
			}
		}
		else{}
	}
}
int main(){
	cin>> n;
	memset(map,0,sizeof(map));
	memset(myhash,0,sizeof(myhash));
	set(1,1,n/2+1);
	work();
	out();
	
	
	return 0;
}
