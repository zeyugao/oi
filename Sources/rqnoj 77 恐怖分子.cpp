//http://www.cppblog.com/xiongnanbin/articles/78183.html
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
long c[51][51],flow[51][51],queue[51],pre[51],n,ans,sumflow;
bool visit[51];
long find_minflow(long x,long y)
{
    if (x>y) return y;
    else return x;
}
void change_flow(long sink)
{
    long minflow,i;
    minflow=0xfffffff;
    i=sink;
    while (i!=1)
    {
        minflow=find_minflow(minflow,flow[pre[i]][i]);
        i=pre[i];
    }
    sumflow+=minflow;
    i=sink;
    while (i!=1)
    {
        flow[pre[i]][i]-=minflow;
       // flow[i][pre[i]]+=minflow;
        i=pre[i];
    }
}
void find_flow(long sink)
{
    long head,tail,start,i;
    for (i=1;i<=n;i++)
    {
        pre[i]=0;
        visit[i]=false;
    }
    head=tail=1;visit[1]=true;
    queue[head]=1;
    while (head<=tail)
    {
        start=queue[head];
        for (i=1;i<=n;i++)
          if (!visit[i] && flow[start][i]>0)
          {
              visit[i]=true;
              tail++;
              queue[tail]=i;
              pre[i]=start;
          }
        head++;
    }
}
int main()
{
    scanf("%d\n",&n);
    char cc;
    for (int i=1;i<=n;i++)
    {
        for (int j=1;j<=n;j++)
        {
            scanf("%c",&cc);
            c[i][j]=cc-'0';
        }
        getchar();
    }
    ans=0x7fffffff;
    long k,i;
    for (i=2;i<=n;i++)
    {
        k=i;sumflow=0;
        memcpy(flow,c,sizeof(long)*(51*51));
        for (;;)
        {
            find_flow(k);
            if (!visit[k]) break;
            change_flow(k);
        }
        if (sumflow<ans) ans=sumflow;
    }
    printf("%d\n",ans);
    return 0;
}