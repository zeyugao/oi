/*　　【宽搜】或【并查集】
　　正面的如果有线就把端点连正边，反面连负边。
　　一针就是从正边到反边再到正边这样循环下去。用宽搜写floodfill（或者并查集）把一次走到线路抠出来，线路上|正边数-反边数|/2为该线路的针数。
　　感觉自己说不太清楚，引用大牛zhymaoiing的话：
　　　　将正面的边视为正边，反面的则视为负边。用floodfill将由正边和负边交替连接的结点组成一个块。对于每一个块，其中的所有结点的正边数目和负边数目之差的绝对值（定为dep）之后div 2后就为这个块的所需针数。
在一个块中只用一针就可完成，假设该针由v1出发，到vn结束，那么v1到vn中间的点的dep为0，而v1和vn则为1。也就是说块中的那一针在v1有一个入口，在vn有一个出口，而每一对入口和出口就代表了一针，那么就可以通过dep之和除以2得到所需针数。由此可以拓宽到多针。
*/

//
//by coolxxx
//
#include<iostream>
#include<algorithm>
#include<string>
#include<iomanip>
#include<memory.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define abs(a) ((a)>0?(a):(-(a)))
#define lowbit(a) (a&(-a))
#define sqr(a) ((a)*(a))
#define swap(a,b) ((a)^=(b),(b)^=(a),(a)^=(b))
#define eps 1e-8
#define J 10
#define MAX 0x7f7f7f7f
#define PI 3.1415926535897
#define N 207
using namespace std;
int n,m,lll,ans,cas;
char map[2][N][N];
bool u[N][N];
bool f;
void floodfill(int i,int j)
{
	//不停围绕着(i,j)这个块左上角的顶点判断
	//在这里每一个能够进入下一层floodfill的，在下一层的四个情况都可以与上一层的任意一种情况构成符合条件的点
	//这下面每一个都满足的
	
	//不考虑反向的，是因为反向的边在其他的floodfill中一定会考虑
	int t=0,k;
	if(u[i][j])return;
	u[i][j]=1;
	if(i>1 && j>1)
	{
		for(k=0;k<2;k++)
		{
			if(map[k][i-1][j-1]=='\\' || map[k][i-1][j-1]=='X')
			{
				t=t+(-2)*k+1;
				f=1;
				floodfill(i-1,j-1);
			}
		}
	}
	if(i>1 && j<=m)
	{
		for(k=0;k<2;k++)
		{
			if(map[k][i-1][j]=='/' || map[k][i-1][j]=='X')
			{
				t=t+(-2)*k+1;
				f=1;
				floodfill(i-1,j+1);
			}
		}
	}
	if(i<=n && j>1)
	{
		for(k=0;k<2;k++)
		{
			if(map[k][i][j-1]=='/' || map[k][i][j-1]=='X')
			{
				t=t+(-2)*k+1;
				f=1;
				floodfill(i+1,j-1);
			}
		}
	}
	if(i<=n && j<=m)
	{
		for(k=0;k<2;k++)
		{
			if(map[k][i][j]=='\\' || map[k][i][j]=='X')
			{
				t=t+(-2)*k+1;
				f=1;
				floodfill(i+1,j+1);
			}
		}
	}
	lll+=abs(t);
}
int main()
{
	#ifndef ONLINE_JUDGE
//	freopen("1.txt","r",stdin);
//	freopen("2.txt","w",stdout);
	#endif
	int i,j,k;
//	while(~scanf("%s",s1))
	while(~scanf("%d",&n))
//	for(scanf("%d",&cas),l=1;l<=cas;l++)
	{
		memset(u,0,sizeof(u));
		ans=0;
		scanf("%d",&m);
		for(k=0;k<2;k++)
			for(i=1;i<=n;i++)
				scanf("%s",map[k][i]+1);
		for(i=1;i<=n+1;i++)
		{
			for(j=1;j<=m+1;j++)
			{
				lll=f=0;
				floodfill(i,j);
				//有符合的条件，并且刚刚好，正面的边个数等于反面边的个数，这是，显而易见，只需一针即可
				if(f && lll==0)ans++;
				//lll不为0或f为0
				//f为0，即没有一个条件满足
				else ans+=lll/2;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}

/*
//

//
*/

//
//by coolxxx
//
#include<iostream>
#include<algorithm>
#include<string>
#include<iomanip>
#include<memory.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define abs(a) ((a)>0?(a):(-(a)))
#define lowbit(a) (a&(-a))
#define sqr(a) ((a)*(a))
#define swap(a,b) ((a)^=(b),(b)^=(a),(a)^=(b))
#define eps 1e-8
#define J 10
#define MAX 0x7f7f7f7f
#define PI 3.1415926535897
#define N 207
using namespace std;
int n,m,lll,ans,cas,cass;
int a[N*N],b[N*N],fa[N*N],c[N*N];
bool u[N*N],v[N*N];
char map[2][N][N];
int zhao(int aa)
{
	if(fa[aa]==-1)return aa;
	return fa[aa]=zhao(fa[aa]);
}
int main()
{
	#ifndef ONLINE_JUDGE
//	freopen("1.txt","r",stdin);
//	freopen("2.txt","w",stdout);
	#endif
	int i,j,k,x,y,fx,fy;
//	while(~scanf("%s",s1))
	while(~scanf("%d",&n))
//	for(scanf("%d",&cas),cass=1;cass<=cas;cass++)
	{
		memset(fa,-1,sizeof(fa));
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		memset(u,0,sizeof(u));
		memset(v,0,sizeof(v));
		ans=0;c[0]=0;
		scanf("%d",&m);
		for(k=0;k<2;k++)
			for(i=0;i<n;i++)
				scanf("%s",map[k][i]);
		for(k=0;k<2;k++)
		{
			for(i=0;i<n;i++)
			{
				for(j=0;j<m;j++)
				{
					if(map[k][i][j]=='\\' || map[k][i][j]=='X')
					{
						x=i*(m+1)+j;y=(i+1)*(m+1)+j+1;
						fx=zhao(x);fy=zhao(y);
						if(fx!=fy)
							fa[fy]=fx;
						a[x]+=(-2)*k+1;
						a[y]+=(-2)*k+1;
						v[x]=v[y]=1;
					}
					if(map[k][i][j]=='/' || map[k][i][j]=='X')
					{
						x=i*(m+1)+j+1;y=(i+1)*(m+1)+j;
						fx=zhao(x);fy=zhao(y);
						if(fx!=fy)
							fa[fy]=fx;
						a[x]+=(-2)*k+1;
						a[y]+=(-2)*k+1;
						v[x]=v[y]=1;
					}
				}
			}
		}
		for(i=0;i<(n+1)*(m+1);i++)
		{
			if(!v[i])continue;
			j=zhao(i);
			if(!u[j])u[j]=1,c[++c[0]]=j;
			b[j]+=abs(a[i]);
		}
		for(i=1;i<=c[0];i++)
		{
			if(b[c[i]]==0)ans++;
			else ans+=b[c[i]]/2;
		}
		printf("%d\n",ans);
	}
	return 0;
}

/*
//

//
*/


