/*
这个题目的关键就是整个无向图其实就是一棵树
那么和同一个父亲节点相连的子节点之间的距离必定是2
然后每个编号的节点都可以看作父亲节点，子节点就可以用邻接表存储了，不必担心爆内存
然后找最大联合权值其实就是找一个父亲节点连的所有子节点里面最大和第二大的权值然后就能产生最大联合权值
总联合权值=∑每个父亲节点的总联合权值
而每个父亲节点的总联合权值=W10+W1W2+(W1+W2)W3+(W1+W2+W3)W4+...+(W1+...+Wn-1)Wn
这样在遍历所有子节点的时候，可以一边找最大和第二大的权值，一边逐层求和算总权值，边加边取余以防爆int
W_total+=((∑W1+...Wn-1)%10007)Wn*2%10007
这样需要遍历每个父亲节点，并遍历接下来的子节点，由于边数=节点数-1，所以应该比较快的
*/ 

include<cstdio>
int n,path[400001][2],index[200001],w[200001];
int main()
{
int i,j,a,b,k,sum,max_1,max_2,max_t=0,w_t=0;
freopen("link10.in","r",stdin);
scanf("%d",&n);
for(i=1;i<n*2-1;i+=2)
{
    scanf("%d%d",&a,&b);    //以邻接表读入无向图 (用数组实现啦） 

    path[i][0]=b;
    path[i][1]=index[a];
    index[a]=i;

    path[i+1][0]=a;
    path[i+1][1]=index[b];
    index[b]=i+1;
}

for(i=1;i<=n;i++)    scanf("%d",&w[i]);    //读入每个点的权值 

for(i=1;i<=n;i++)                        //开始遍历每个父亲节点 
{
    a=index[i];                            //初始化 
    sum=0;        //子节点权值累加 
    max_1=0;    //子节点中最大的权值 
    max_2=0;    //子节点中第二大的权值 

	while(path[a][0])                    //遍历与每个父亲节点相连的所有子节点 
	{    
		b=w[path[a][0]];                //读取当前子节点的权值 

		if(b>max_1)    max_1 = b;                    //搜索子节点最大和第二大的权值 
		else         max_2 = max_2>b ? max_2:b;

		w_t+=(sum%10007)*b*2%10007;        //Sum乘以当前子节点权值再乘2并取余10007 
		w_t%=10007;        
		sum+=b;                            //对之前遍历的子节点权值进行累加求和 

		a=path[a][1];                    //跳转到下一个子节点 
	}

    k=max_1*max_2;                        //得到当前父亲节点的最大联合权值并比较全局最大联合权值 
    	max_t=max_t>k ? max_t:k;
	}

	printf("%d %d",max_t,w_t);                //输出结果 
	return 0;
}
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cctype>
 
using namespace std;
 
const int maxn = 200009;
const int MOD = 10007;
 
int N, w[maxn], mx[maxn], cnt[maxn], ans = 0, tot = 0;
 
inline int read() {
    char c = getchar();
    int ret = 0;
    for(; !isdigit(c); c = getchar());
    for(; isdigit(c); c = getchar())
        ret = ret * 10 + c - '0';
    return ret;
}
 
struct edge {
    int to;
    edge* next;
} E[maxn << 1], *pt = E, *head[maxn];
 
inline void add(int u, int v) {
    pt->to = v; pt->next = head[u]; head[u] = pt++;
}
inline void addedge(int u, int v) {
    add(u, v); add(v, u);
}
 
void init() {
    scanf("%d", &N);
    for(int i = 1; i < N; i++) {
        int u = read() - 1, v = read() - 1;
        addedge(u, v);
    }
    for(int i = 0; i < N; i++) scanf("%d", w + i);
}
 
void dfs(int x, int fa = -1) {
    mx[x] = cnt[x] = 0;
    for(edge* e = head[x]; e; e = e->next) if(e->to != fa) {
        dfs(e->to, x);
        //
        ans = max(ans, w[x] * mx[e->to]);
        ans = max(ans, w[e->to] * mx[x]);
        tot = (tot + w[x] * cnt[e->to] + w[e->to] * cnt[x]) % MOD;
        (cnt[x] += w[e->to]) %= MOD;
        mx[x] = max(mx[x], w[e->to]);
    }
}
 
int main() {
     
    init();
    dfs(0);
    printf("%d %d\n", ans, tot * 2 % MOD);
     
    return 0;
}
