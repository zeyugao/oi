/*只有空白块位于指定块的四方向上，指定块才可以移动。所以，我们可以记(x1,y1,dir)表示指定块在(x1,y1)，空白块在指定块的dir方向（0表示上，1表示下什么的......）的状态。这样状态只有4nm个。
接下来我们考虑各个状态之间的连边。首先，空白块和指定块可以交换位置，这两个状态连边的边权为1；其次，假定空白块在指定块上方，空白块可以通过若干步移动来到空白块下/左/右方。这些状态连边的边权我们可以通过BFS计算出来。
这样就构造出了一张图，先把空白块移动到目标块旁边，之后向目标状态（空白块可以位于指定块的四个方向）做最短路即可。用spfa复杂度为O(qknm)，可以通过100%的数据。*/
//总体来说,大神做得出来
#include <stdio.h>
#include <string.h>
#define QLEN 4000
int n,m,qq;
int e[20010][3],p[4010],tot = 0,ans;
int q[1010][2],dis[35][35],sq[4010],sdis[4010],head,tail;
short vis[4010],map[35][35],dir[4][2] = {-1,0,1,0,0,-1,0,1}; //???? 
int min(int a,int b)
{
    return a<b?a:b;
}
void adde(int sn,int fn,int val)  //?? ?xy????? 
{
    e[++tot][0] = fn; e[tot][1] = val; e[tot][2] = p[sn]; p[sn] = tot;
}
void bfs(int si,int sj,int bi,int bj,int id)
{
    int i,j,k,ii,jj;
    memset(dis,0,sizeof(dis));
    head = 1; tail = 2;
    q[1][0] = si; q[1][1] = sj; dis[si][sj] = 1;
    while(head != tail)
    {
        i = q[head][0]; j = q[head++][1];
        for(k=0;k<4;k++)
        {
            ii = i+dir[k][0]; jj = j+dir[k][1];
            if(!map[ii][jj] || (ii==bi&&jj==bj) || dis[ii][jj]) continue;
            dis[ii][jj] = dis[i][j]+1;
            q[tail][0] = ii; q[tail++][1] = jj;
        }
    }
    if(id == 4) return;
    for(k=0;k<4;k++)
    {
		//bi,bj为指定点
		//i,j为目标点
        i = bi+dir[k][0]; j = bj+dir[k][1];
        if((i == si && j == sj) || !dis[i][j]) continue;
		//历遍所有位置,得到某一个状态到周围状态的距离
		//这里的边是指定块不动，空白块围绕着它四周转的dis
        adde(bi*30*4+bj*4+id,bi*30*4+bj*4+k,dis[i][j]-1);
    }
	//就是这条边,让指定方块位置能够改变的边
	//这条边记录了空白块与 某一个块交换位置，相当于这两个状态的变化的dis
    adde(bi*30*4+bj*4+id,si*30*4+sj*4+(id^1),1);
}
void spfa(int si,int sj)
{
    int i,sn,fn,val;
    memset(sdis,60,sizeof(sdis));
    head = 1; tail = 1;
    for(i=0;i<4;i++)
    {
        if(!dis[si+dir[i][0]][sj+dir[i][1]]) continue;
        sn = si*30*4+sj*4+i;
        sq[tail++] = sn; sdis[sn] = dis[si+dir[i][0]][sj+dir[i][1]]-1; vis[sn] = 1;
    }
    while(head != tail)
    {
        sn = sq[head++];
        for(i=p[sn];i;i=e[i][2])
        {
			//在前面加入了一条不同的边,那条边让指定位置的方块发生移动,在这里获取到指定位置方块移动后状态所需要的最小哦dis
            fn = e[i][0]; val = e[i][1];
            if(sdis[fn]<=sdis[sn]+val) continue;
            sdis[fn] = sdis[sn]+val;
            if(vis[fn]) continue;
            vis[fn] = 1; sq[tail++] = fn;
            if(tail>QLEN) tail = 1;
        }
        vis[sn] = 0;
        if(head>QLEN) head = 1;
    }
}
int main()
{
    int i,j,bi,bj,si,sj,fi,fj;
    scanf("%d%d%d",&n,&m,&qq);
    for(i=1;i<=n;i++) for(j=1;j<=m;j++) scanf("%hd",&map[i][j]);
    for(i=1;i<=n;i++) for(j=1;j<=m;j++)
    {
        if(!map[i][j]) continue;
		//空白块为(i-1,j)，被围绕的块为(i,j)，空白块到被围绕的块的周围的点，或者被围绕的块与空白块交换
        if(map[i-1][j]) bfs(i-1,j,i,j,0);
        if(map[i+1][j]) bfs(i+1,j,i,j,1);
        if(map[i][j-1]) bfs(i,j-1,i,j,2);
        if(map[i][j+1]) bfs(i,j+1,i,j,3);
    }
    while(qq--)
    {
        scanf("%d%d%d%d%d%d",&bi,&bj,&si,&sj,&fi,&fj);
        if(si == fi && sj == fj) { printf("0\n"); continue;}
        bfs(bi,bj,si,sj,4); spfa(si,sj); ans = 999999;
        for(i=0;i<4;i++) ans = min(ans,sdis[fi*30*4+fj*4+i]);
        if(ans<999999) printf("%d\n",ans);
        else printf("-1\n");
    }
    return 0;
}