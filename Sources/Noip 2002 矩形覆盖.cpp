//Sources:http://www.voidcn.com/blog/qpswwww/article/p-2634025.html 
#include <stdio.h>
#include <stdlib.h>
#define MAXN 100 
#define INF 0x3f3f3f3f 
int ans=INF,n,k;
struct point
{
   int x;//该点的x坐标
   int y;//该点的y坐标 
}dots[MAXN];
struct square
{
   struct point l; //左下角的点l
   struct point r; //右上角的点r 
}sqr[100];
int checkit(int i,int j) //检查第i、j个矩形之间是否有冲突(即两个矩形有重叠区域) 
{
    if(sqr[i].l.x==INF||sqr[i].l.y==INF||sqr[i].r.x==-INF||sqr[i].r.y==-INF)
        return 0;
    if(sqr[j].l.x==INF||sqr[j].l.y==INF||sqr[j].r.x==-INF||sqr[j].r.y==-INF)
        return 0;
    if(sqr[i].l.x>sqr[j].r.x||sqr[i].l.y>sqr[j].r.y)
       return 0;
    if(sqr[j].l.x>sqr[i].r.x||sqr[j].l.y>sqr[i].r.y)
       return 0;
    return 1;
} 
int check() //检查当前所有已知矩形是否都合法。合法返回1 
{
    int i,j;
    for(i=0;i<k;i++)
    {
        for(j=i+1;j<k;j++)
           if(checkit(i,j))
               return 0;
    }
    return 1;
}
int getsqr() //函数获取当前所有矩形覆盖面积之和 
{
    int i,ans=0;
    for(i=0;i<k;i++)
    {
       if(sqr[i].l.x!=INF)
          ans+=(sqr[i].r.x-sqr[i].l.x)*(sqr[i].r.y-sqr[i].l.y);
    }
    return ans;
}
void srch(int now) //寻找第now个点时矩形是否能覆盖 
{
    if(now==n) //搜索完成
    {
        ans=getsqr(); //获取当前所有矩形覆盖面积 
        return;
    }
    int i,j;
    for(i=0;i<k;i++) //从第0个矩形循环搜索到第k-1个矩形，判断矩形是否覆盖了点now
    {
       struct square tmp=sqr[i];  //神奇的深搜后恢复原状态 
       if(sqr[i].l.x>dots[now].x)
           sqr[i].l.x=dots[now].x;
       if(sqr[i].l.y>dots[now].y)
           sqr[i].l.y=dots[now].y;
       if(sqr[i].r.x<dots[now].x)
           sqr[i].r.x=dots[now].x;
       if(sqr[i].r.y<dots[now].y)
           sqr[i].r.y=dots[now].y;
       if(check()&&getsqr()<ans) //如果该步完成后，之前所有矩形都是合法的，且当前所有已求出的矩形面积比当前最优解小，则向深层(下一个点)搜索 
          srch(now+1);
       sqr[i]=tmp;
    }
}
int main()
{
    int i,j;
    scanf("%d%d",&n,&k);
    for(i=0;i<n;i++)
       scanf("%d%d",&dots[i].x,&dots[i].y);
    for(i=0;i<k;i++)
    {
    	//初始化为左下角的点值为（+∞，+∞）
		//右上角的值为(-∞,-∞)，保证第一个点加进来一定会更新 
       sqr[i].l.x=INF;
       sqr[i].l.y=INF;
       sqr[i].r.x=-INF;
       sqr[i].r.y=-INF;
    }
    srch(0);
    printf("%d",ans);
    //system("pause");
    return 0;
}

