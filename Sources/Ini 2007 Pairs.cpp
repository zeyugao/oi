#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#define ll long long
using namespace std;
const int maxn=100233;
int x[maxn];
struct zs{int x,y,z;}a[maxn];
ll ans;
int i,j,k,n,m,D,id,M;
 
bool cmp(zs a,zs b){return a.x<b.x;}
int ra;char rx;
inline int read(){
    rx=getchar(),ra=0;
    while(rx<'0'||rx>'9')rx=getchar();
    while(rx>='0'&&rx<='9')ra*=10,ra+=rx-48,rx=getchar();return ra;
}
 
inline void run1(){
    register int i,l=1;
    for(i=1;i<=n;i++)x[i]=read();
    sort(x+1,x+1+n);
    for(i=2;i<=n;ans+=i-l,i++)while(x[i]-x[l]>D)l++;
}
 
int t[75233<<1];
inline void del(int x){while(x<=M)t[x]--,x+=x&-x;}
inline void add(int x){while(x<=M)t[x]++,x+=x&-x;}
inline ll query(int x){
    if(x<=0)return 0;
    if(x>M)x=M;
    ll sm=0;
    while(x)sm+=t[x],x-=x&-x;
    return sm;
}
inline void run2(){
    register int i;
    for(i=1;i<=n;i++)j=read(),k=read(),a[i].x=j+k,a[i].y=j-k+m;
    sort(a+1,a+1+n,cmp);int top=1;
    for(i=1;i<=n;i++){
        while(a[top].x+D<a[i].x)del(a[top].y),top++;
        ans+=query(a[i].y+D)-query(a[i].y-D-1),
        add(a[i].y);
    }
}
 
ll mp[77][77<<1][77<<1];
inline ll getsm(int x,int x1,int y1,int x2,int y2){
    if(x1<1)x1=1;if(y1<1)y1=1;
    if(x2>M)x2=M;if(y2>M)y2=M;
    return mp[x][x2][y2]-mp[x][x1-1][y2]-mp[x][x2][y1-1]+mp[x][x1-1][y1-1];
}
inline void run3(){
    register int i,j,k;int x;ll tmp=0;
    for(i=1;i<=n;i++)a[i].x=read(),j=read(),k=read(),a[i].y=j+k,a[i].z=j-k+m;
    sort(a+1,a+1+n,cmp);
    for(i=1;i<=n;){
        x=a[i].x;
        for(j=i;a[j+1].x==x;j++);
        while(i<=j)mp[x][a[i].y][a[i].z]++,i++;
        for(j=1;j<=M;j++)for(k=1;k<=M;k++)mp[x][j][k]+=mp[x][j-1][k]+mp[x][j][k-1]-mp[x][j-1][k-1];
    }
    for(i=1;i<=n;i++){
        for(j=a[i].x+1;j<=m&&j-a[i].x<=D;j++)
            k=D-(j-a[i].x),ans+=getsm(j,a[i].y-k,a[i].z-k,a[i].y+k,a[i].z+k);
        tmp+=getsm(a[i].x,a[i].y-D,a[i].z-D,a[i].y+D,a[i].z+D)-1;
    }
    tmp>>=1;
    ans+=tmp;
}
int main(){
    id=read(),n=read(),D=read(),m=read();M=m<<1;
    if(D>=m*id){printf("%lld\n",(ll)n*(n-1)/2);}
    if(id==1)run1();
    if(id==2)run2();
    if(id==3)run3();
    printf("%lld\n",ans);
    return 0;
} 
