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
//先转化为切尔雪夫距离,将一个菱形范围的个数转化为一个矩形的范围的个数
//按照x的大小递增排序
//依次加入到“队列”中来这个队列用树状数组实现,每监测一个,先将在前面加入的不符合的点先删去,用top值来维护,top总是刚好满足上一个点的最左端,监测这个点时可以直接从top开始找,因为这是由x递增排序的,上一个点都不满足要求,这一个点也同样不可能满足要求
inline void run2(){
    register int i;
    for(i=1;i<=n;i++)j=read(),k=read(),a[i].x=j+k,a[i].y=j-k+m;
    sort(a+1,a+1+n,cmp);int top=1;
    for(i=1;i<=n;i++){
		//删除所有在这个点前面而横坐标大于d的点,
		//这个树状数组记录的是满足条件的点的纵坐标,在每次循环开始时,最先进行的是剔除不满足条件的点,其此查询在需要的区间的点的个数,最后在加入当前这个点(自己肯定不能和自己连线呀)
		//关于会不会直接一进来就删树状数组到负的情况:
        while(a[top].x+D<a[i].x)del(a[top].y),top++;
		//查询纵坐标为范围内的有多少个
        ans+=query(a[i].y+D)-query(a[i].y-D-1),
		//这里的add是在循环第一步时有一个先行条件过滤过的,没有加入后面的符合条件的点,是为了避免重复计算点对数,保证这个横坐标上的点只会计算到与前面的前面的关系,而后面的点由后面的点进行查询
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
		//获取从这个平面的原点到(x,y)中总共有多少个点
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