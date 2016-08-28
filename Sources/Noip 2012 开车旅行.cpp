//倍增大法
//set默认递增序列
/*
升序排列的容器：
lower_bound返回一个迭代器，指向键值>= key的第一个元素。
upper_bound返回一个迭代器，指向键值<=key的最后一个元素的后一个元素。

降序排列的容器：
lower_bound 返回一个迭代器，指向键值<= key的第一个元素。
upper_bound返回一个迭代器，指向键值>=key的最后一个元素的后一个元素。
*/ 
/*先预处理出每个城市的最近与次近，可以用C++STL的set。
然后令g[i][j]为从i点走2^j个轮回（注意是轮回，不是步）后的位置，f[i][j][0]为从i点走2^j个轮回后A走过的距离，f[i][j][1]为从i点走2^j个轮回后B走过的距离。
那么很容易推出：
g[i][j]=g[g[i][j-1]][j-1];
f[i][j][0]=f[i][j-1][0]+f[g[i][j-1]][j-1][0];
f[i][j][1]=f[i][j-1][0]+f[g[i][j-1]][j-1][1];*/

#include<bits/stdc++.h>
using namespace std;
const int maxn=100000+10;
typedef long long LL;
struct City
{
	int h,num;
	bool operator < (const City rhs) const
	{
		return h<rhs.h;
	}
}h[maxn];
set<City> S;
set<City>::iterator it;
int n,x0,m,next[maxn][2],dist[maxn][2],g[maxn][21];
LL f[maxn][21][2];
inline void update(City x,City y)
{
	if(!next[x.num][0])
	{
		next[x.num][0]=y.num;
		dist[x.num][0]=abs(x.h-y.h);
	}
	else if(abs(x.h-y.h)<dist[x.num][0]||(abs(x.h-y.h)==dist[x.num][0]&&y.h<h[next[x.num][0]].h))
	{
		next[x.num][1]=next[x.num][0];
		dist[x.num][1]=dist[x.num][0];
		next[x.num][0]=y.num;
		dist[x.num][0]=abs(x.h-y.h);
	}
	else if(abs(x.h-y.h)<dist[x.num][1]||(abs(x.h-y.h)==dist[x.num][1]&&y.h<h[next[x.num][1]].h))
	{
		next[x.num][1]=y.num;
		dist[x.num][1]=abs(x.h-y.h);
	}
	else if(!next[x.num][1])
	{
		next[x.num][1]=y.num;
		dist[x.num][1]=abs(x.h-y.h);
	}
	return;
}
inline void query(int s,int x,LL& dista,LL& distb)
{
	for(int i=20;i>=0;i--)
		if(f[s][i][0]+f[s][i][1]<=x&&g[s][i])
		{
			dista+=f[s][i][0];
			distb+=f[s][i][1];
			x-=f[s][i][0]+f[s][i][1];
			s=g[s][i];
		}
	if(next[s][1]&&dist[s][1]<=x)
		dista+=dist[s][1];
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&h[i].h);
		h[i].num=i;
	}
	for(int i=n;i;i--)
	{
		S.insert(h[i]);
		it=S.find(h[i]);
		if(it!=S.begin())
		{
			it--;
			update(h[i],*it);
			if(it!=S.begin())
			{
				it--;
				update(h[i],*it);
				it++;
			}
			it++;
		}
		if((++it)!=S.end())
		{
			update(h[i],*it);
			if((++it)!=S.end())
				update(h[i],*it);
			it--;
		}
		it--;
	}
	for(int i=1;i<=n;i++)
	{
		g[i][0]=next[next[i][1]][0];
		f[i][0][0]=dist[i][1];
		f[i][0][1]=dist[next[i][1]][0];
	}
	for(int j=1;j<=20;j++)
		for(int i=1;i<=n;i++)
		{
			g[i][j]=g[g[i][j-1]][j-1];
			f[i][j][0]=f[i][j-1][0]+f[g[i][j-1]][j-1][0];
			f[i][j][1]=f[i][j-1][1]+f[g[i][j-1]][j-1][1];
		}
	scanf("%d",&x0);
	int s0=0;
	LL a=1e15,b=0;
	for(int i=1;i<=n;i++)
	{
		LL dista=0,distb=0;
		query(i,x0,dista,distb);
		if(distb&&(!s0||a*distb>b*dista))
		{
			s0=i;
			a=dista;
			b=distb;
		}
	}
	printf("%d\n",s0);
	scanf("%d",&m);
	while(m--)
	{
		int s,x;
		scanf("%d%d",&s,&x);
		LL dista=0,distb=0;
		query(s,x,dista,distb);
		printf("%lld %lld\n",dista,distb);
	}
	return 0;
}




////////////////////////
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
#include <set>
#include <map>
#include <cmath>

#define MAXN 100005
#define MAXP 18
#define LL long long
#define INF 5000000000LL

using namespace std;

struct data //保存城市数据
{
    LL dec;
    LL h; //城市编号、高度
}city[5];

map<LL,int>hash; //建立高度映射城市编号的哈希表
set<LL>bst; //平衡二叉树，找每个城市的最小和次小差值的城市

int to[MAXN][MAXP]; //to[i][j]=城市i经过2^j个轮回后到达的城市编号，这里一个轮回是指a和b各开一次车后的
int h[MAXN]; //每个城市的高度
int n;
LL va[MAXN][MAXP];
LL vb[MAXN][MAXP];
int fa[MAXN];
int fb[MAXN];
LL a[MAXN],b[MAXN];
//va[i][j]=从城市i出发，A经过2^j步走的距离
//vb[i][j]=从城市i出发，B经过2^j步走的距离
//a[i][j]=从城市i出发，A经过2^j步走到的城市
//b[i][j]=从城市i出发，B经过2^j步走到的城市

bool operator<(data a,data b)
{
    if(a.dec!=b.dec) return a.dec<b.dec;
    return a.h<b.h;
}

void preWork() //用平衡二叉树预处理得到每个城市的最小和次小差值的城市
{
    for(int i=n;i>=1;i--) //由于车子只能从之前的城市移动到后面的城市，所以得倒着找前驱后继
    {
        bst.insert(h[i]);
		/*	找到最接近h(i)的两个元素
			lower返回大于等于的第个数,再自减得到最大的小于的数
			upper返回小于等于的最后一个元素的后一个元素----返回大于它的数

			用这种方法是为了取的不等于的数*/
        city[1].h=*--bst.lower_bound(h[i]),city[2].h=*bst.upper_bound(h[i]);
        if(city[1].h>-INF)
			//存在比h(i)更小的数,找到第二小的数
			city[3].h=*--bst.lower_bound(city[1].h);
        else city[3].h=-INF;
		
		//同上一条笔记
        if(city[2].h<INF) city[4].h=*bst.upper_bound(city[2].h);
        else city[4].h=INF;
        for(int k=1;k<=4;k++)
			//相对高度
            city[k].dec=abs(city[k].h-h[i]);
		
		//根据比较函数,会优先选择相对高度更小的,如果相对高度相同,会让海拔更低的放在前面
        sort(city+1,city+5); //排序
		
		//根据题目分别把第二的给a,第一的给b
        a[i]=city[2].dec;
        fa[i]=hash[city[2].h];
        b[i]=city[1].dec;
        fb[i]=hash[city[1].h];
        for(int j=0;j<=16;j++)
        {
            if(j==0) //一个轮回
            {
                if(fa[i])
                {
                    va[i][0]=a[i];
                    to[i][0]=fa[i];
                }
            }
            else if(j==1) //2^1=2个轮回
			/*	一个轮回—a或b开一次车?
				但仅有这个解释能理解&说通*/
            {
                if(fb[fa[i]])
                {
                    va[i][1]=a[i];
                    vb[i][1]=b[fa[i]];
                    to[i][1]=fb[fa[i]];
                }
            }
            else if(to[to[i][j-1]][j-1]) //2^x,x>1，倍增来求答案
            {
                va[i][j]=va[i][j-1]+va[to[i][j-1]][j-1];
                vb[i][j]=vb[i][j-1]+vb[to[i][j-1]][j-1];
                to[i][j]=to[to[i][j-1]][j-1];
            }
            else break;
        }
    }
}

double cal1(int x,int val) //起点为x，总距离为val，得到的a开车距离/b开车距离的值
{
    int t1=0,t2=0; //t1=a走的距离，t2=b走的距离
    for(int i=16;i>=0;i--)
    {
        if(to[x][i]&&t1+va[x][i]+t2+vb[x][i]<=val)
        {
            t1+=va[x][i]; //更新a、b走过的距离
            t2+=vb[x][i];
            x=to[x][i]; //更新走到的城市
        }
    }
    if(t2==0) return INF;
    return (double)t1/(double)t2; //返回a走的距离/b走的距离的比值
}

void cal2(int x,int val) //起点为x，总距离为val,输出aheb走过的距离
{
    int t1=0,t2=0;
    for(int i=16;i>=0;i--)
        if(to[x][i]&&t1+va[x][i]+t2+vb[x][i]<=val)
        {
            t1+=va[x][i];
            t2+=vb[x][i];
            x=to[x][i];
        }
    printf("%d %d\n",t1,t2);
}

void solve1() //回答第一问
{
    double minDiv=1e60; //最小比值
    int ans; //最小比值取得的时候的起点下标
    int x0;
    scanf("%d",&x0);
    for(int i=1;i<=n;i++)
    {
        double nowDiv=cal1(i,x0);
        if(nowDiv<minDiv||(nowDiv==minDiv&&h[i]>h[ans])) //注意||后面的条件，若两个比值相同但是当前的高度高一些，则取当前的
        {
            minDiv=nowDiv;
            ans=i;
        }
    }
    printf("%d\n",ans);
}

void solve2() //回答第二问
{
    int m;
    scanf("%d",&m);
    for(int i=1;i<=m;i++)
    {
        int s,x;
        scanf("%d%d",&s,&x);
        cal2(s,x);
    }
}

int main()
{
    scanf("%d",&n);
    bst.insert(-INF);
    bst.insert(INF);
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",&h[i]);
        hash[h[i]]=i; //标记该高度对应的城市编号
    }
    preWork(); //预处理
    solve1(); //回答第一问
    solve2(); //回答第二问
    return 0;
}
