//随机化乱搞BFS。随机了300*100次，每次每层随机删一个 看看最后答案

//随机化大法？
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cmath>
using namespace std;
const int N=505,M=N*N;
int list[M],head[N],nxt[M],tot;
void add(int a,int b)
{
    tot++;
	//第tot个点是b
    list[tot]=b;
	nxt[tot]=head[a];
    head[a]=tot;
}
int vis[N],n,p,fa[N];
void dfs(int v)
{
    vis[v]=1;
    for(int i=head[v];i;i=nxt[i])
    {
        int u=list[i];
        if(!vis[u])
        {
            fa[u]=v;
            dfs(u);
			//这里是dfs生成一棵树，题目中的i j可能是在上面做父，也可能是在下面做子
        }
    }
}
int f[N];
int bfs()
{
    queue<int>q;int ans=0;
    q.push(1);vis[1]=1;
    memset(vis,0,sizeof vis);
    int cnt=0;
    while(1)
    {
        if(q.empty())//下一层了
        {
			//cnt=0说明在上一层的元素历遍完了，没有下一层的儿子
			//cnt=1说明下一层只有一个元素，直接剪掉就可以了，
            if(cnt<=1)return ans;
            int c=rand()%cnt+1;//选了一个
            for(int i=1;i<=cnt;i++)
            if(c!=i)q.push(f[i]);
            cnt=0;
        }
        int v=q.front();ans++;q.pop();
        for(int i=head[v];i;i=nxt[i])
        {
            int u=list[i];
			//因为是两向的，需要保证head与nxt引出的需要是儿子而不是父亲
            if(fa[v]!=u&&!vis[u])f[++cnt]=u,vis[u]=1;
        }
    }
}

int main()
{
    srand(88888);
    scanf("%d%d",&n,&p);
    for(int i=1;i<=p;i++)
    {
        int a,b;scanf("%d%d",&a,&b);
        add(a,b),add(b,a);
    }
    dfs(1);
    int ans=0x3f3f3f3f;
    for(int i=1;i<=100*100;i++)
		ans=min(ans,bfs());
    cout<<ans<<endl;
}