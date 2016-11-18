<<<<<<< HEAD
/*缁忓吀鐨勬爲褰㈠姩鎬佽鍒掗锛屾秹鍙婂埌浜嗗瀛愪箣闂寸殑鍒嗛厤闂锛岄渶瑕佺敤瀛╁瓙鍏勫紵琛ㄧず娉曟潵瀹炵幇銆�

棣栧厛锛屽垽鏂湁瑙ｇ殑鏉′欢鏄疢-1<=N-K銆傜敱浜�2<=M<=N锛屽綋M=2鏃讹紝鐩稿綋浜庢妸鎵�鏈夎妭鐐规煋涓婁笉鍚岄鑹诧紝涓ょ棰滆壊鐩� 鍚岀殑杈硅琚畻涓婃潈鍊硷紝姹傛潈鍊兼渶灏忕殑鏂规銆傚亣瀹氣�滃ぇ澶粹�濊鍚冪殑鑺傜偣涓洪粦鑹茶妭鐐癸紝鍏朵綑涓虹櫧鑹茶妭鐐广�傛垜浠渶瑕佽�冭檻鎵�鏈夌殑涓ょ棰滆壊鐩稿悓鐨勮竟銆傚鏋淢>2锛屽垯 鍙渶瑕佽�冭檻涓ょ閮芥槸榛戣壊鐨勮竟銆傚洜涓哄綋鍓╀綑棰滆壊澶氫簬1鏃讹紝涓�瀹氬彲浠ユ壘鍒颁竴绉嶆柟妗堬紝浣垮緱鈥滃皬澶粹�濅笉浼氬悶涓嬫爲鏋濄��

瀹氫箟i.son涓篿鐨勭涓�涓瀛愶紝i.brother涓篿鐨勫厔寮熻妭鐐癸紝i.cost涓篿鍚戝叾鐖朵翰杩炴帴鐨勮竟鐨勬潈鍊笺��

鐘舵�佸畾涔�

F[i][j][k]涓轰互i涓烘牴鐨勫瓙鏍戝強浠ュ叾鍙宠竟鐨勫厔寮熶负鏍圭殑瀛愭爲涓紝鏈塲涓妭鐐硅鏌撻粦锛屼笖i鐨勭埗浜茶妭鐐圭殑棰滆壊涓簁(1涓洪粦鑹诧紝0涓哄叾瀹�)鏃剁殑鏈�灏忚垂鐢�

鐘舵�佽浆绉绘柟绋�

F[i][j][k]=Min
{
    F[i.son][j'][0] + F[i.brother][j-j'][k] + D(0,k)  i.cost,
    F[i.son][j'][1] + F[i.brother][j-j'-1][k] + D(1,k)  i.cost,
}
鍏朵腑 D(a,b)琛ㄧず涓ょ棰滆壊涓篴,b涔嬮棿鐨勮竟鏄惁瑕佽鍚冩帀锛屽叿浣撳畾涔変负
D(a,b) = 
{
    1 | a=b=1
    1 | a=b=0 涓� M=2
    0 | 鍏跺畠鎯呭喌
}
杈圭晫鏉′欢
鑺傜偣0琛ㄧず涓�涓櫄鎷熺殑绌鸿妭鐐�

F[0][0][k] = 0 (k=0,1)

F[0][j][k] = 鏃犵┓澶� (j>0 k=0,1)

鐩爣鐘舵��

F[鑺傜偣1.son][K-1][1]

 * Problem: NOI2002 dragon
 * Author: Guo Jiabao
 * Time: 2009.5.18 14:02
 * State: Solved
 * Memo: 鏍戝舰鍔ㄦ�佽鍒� 瀛╁瓙鍏勫紵鍒嗛厤闂
*/

//鏍戝舰dp澶ф硶
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
const int MAXN=301,INF=0x7FFFFFF;
using namespace std;
struct edge
{
    edge *next;
    int t,c;
}*V[MAXN],ES[MAXN*2];
struct node
{
    int son,brother,cost;
}T[MAXN];
int N,M,K,EC,Ans,Stack[MAXN];
bool vis[MAXN];
int F[MAXN][MAXN][2];
inline void addedge(int a,int b,int c)
{
	//杩欓噷杩欐牱鍋�,鍙互鐩存帴鐢╒[a].next
    ES[++EC].next = V[a];
    V[a]=ES+EC; V[a]->t=b; V[a]->c=c;
    ES[++EC].next = V[b];
    V[b]=ES+EC; V[b]->t=a; V[b]->c=c;
}
void maketree()
{
    int i,j,Stop;
    Stack[Stop=1]=1;
    while (Stop)
    {
        i=Stack[Stop--];
        vis[i]=true;
        for (edge *e=V[i];e;e=e->next)
        {
            j=e->t;
            if (!vis[j])
            {
                T[j].brother=T[i].son;
                T[j].cost=e->c;
                T[i].son=j;
                Stack[++Stop]=j;
            }
        }
    }
}
void init()
{
    int i,a,b,c;
    freopen("dragon.in","r",stdin);
    freopen("dragon.out","w",stdout);
    scanf("%d%d%d",&N,&M,&K);
    for (i=1;i<N;i++)
    {
        scanf("%d%d%d",&a,&b,&c);
        addedge(a,b,c);
    }
    maketree();
    memset(F,-1,sizeof(F));
}
inline int D(int a,int b)
{
    return ((a==1 && b==1)||(a==0 && b==0 && M==2));
}
int DP(int i,int j,int k)
{
    if (F[i][j][k]==-1)
    {
        int a,v,rs=INF;
        for (a=0;a<=j;a++)
        {
            v = DP(T[i].son,a,0) + DP(T[i].brother,j-a,k) + D(0,k) * T[i].cost;
            if (v<rs) rs=v;
            if (a<j)
            {
                v = DP(T[i].son,a,1) + DP(T[i].brother,j-a-1,k) + D(1,k) * T[i].cost;
                if (v<rs) rs=v;
            }
        }
        F[i][j][k]=rs;

    }
    return F[i][j][k];
}
void solve()
{
    if (M-1 <= N-K)
    {
        F[0][0][0]=F[0][0][1]=0;
        for (int i=1;i<=K;i++)
            F[0][i][0]=F[0][i][1]=INF;
        Ans=DP(T[1].son,K-1,1);
    }
    else
        Ans=-1;
}
int main()
{
    init();
    solve();
    printf("%d\n",Ans);
    return 0;
}
=======
/*经典的树形动态规划题，涉及到了孩子之间的分配问题，需要用孩子兄弟表示法来实现。

首先，判断有解的条件是M-1<=N-K。由于2<=M<=N，当M=2时，相当于把所有节点染上不同颜色，两端颜色相 同的边要被算上权值，求权值最小的方案。假定“大头”要吃的节点为黑色节点，其余为白色节点。我们需要考虑所有的两端颜色相同的边。如果M>2，则 只需要考虑两端都是黑色的边。因为当剩余颜色多于1时，一定可以找到一种方案，使得“小头”不会吞下树枝。

定义i.son为i的第一个孩子，i.brother为i的兄弟节点，i.cost为i向其父亲连接的边的权值。

状态定义

F[i][j][k]为以i为根的子树及以其右边的兄弟为根的子树中，有j个节点被染黑，且i的父亲节点的颜色为k(1为黑色，0为其它)时的最小费用

状态转移方程

F[i][j][k]=Min
{
    F[i.son][j'][0] + F[i.brother][j-j'][k] + D(0,k)  i.cost,
    F[i.son][j'][1] + F[i.brother][j-j'-1][k] + D(1,k)  i.cost,
}
其中 D(a,b)表示两端颜色为a,b之间的边是否要被吃掉，具体定义为
D(a,b) = 
{
    1 | a=b=1
    1 | a=b=0 且 M=2
    0 | 其它情况
}
边界条件
节点0表示一个虚拟的空节点

F[0][0][k] = 0 (k=0,1)

F[0][j][k] = 无穷大 (j>0 k=0,1)

目标状态

F[节点1.son][K-1][1]

 * Problem: NOI2002 dragon
 * Author: Guo Jiabao
 * Time: 2009.5.18 14:02
 * State: Solved
 * Memo: 树形动态规划 孩子兄弟分配问题
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
const int MAXN=301,INF=0x7FFFFFF;
using namespace std;
struct edge
{
    edge *next;
    int t,c;
}*V[MAXN],ES[MAXN*2];

struct node
{
    int son,brother,cost;
}T[MAXN];
int N,M,K,EC,Ans,Stack[MAXN];
bool vis[MAXN];
int F[MAXN][MAXN][2];
inline void addedge(int a,int b,int c)
{
    ES[++EC].next = V[a];
    V[a]=ES+EC; V[a]->t=b; V[a]->c=c;
    ES[++EC].next = V[b];
    V[b]=ES+EC; V[b]->t=a; V[b]->c=c;
}
void maketree()
{
    int i,j,Stop;
    Stack[Stop=1]=1;
    while (Stop)
    {
        i=Stack[Stop--];
        vis[i]=true;
        for (edge *e=V[i];e;e=e->next)
        {
            j=e->t;
            if (!vis[j])
            {
                T[j].brother=T[i].son;
                T[j].cost=e->c;
                T[i].son=j;
                Stack[++Stop]=j;
            }
        }
    }
}
void init()
{
    int i,a,b,c;
    freopen("dragon.in","r",stdin);
    freopen("dragon.out","w",stdout);
    scanf("%d%d%d",&N,&M,&K);
    for (i=1;i<N;i++)
    {
        scanf("%d%d%d",&a,&b,&c);
        addedge(a,b,c);
    }
    maketree();
    memset(F,-1,sizeof(F));
}
inline int D(int a,int b)
{
    return ((a==1 && b==1)||(a==0 && b==0 && M==2));
}
int DP(int i,int j,int k)
{
    if (F[i][j][k]==-1)
    {
        int a,v,rs=INF;
        for (a=0;a<=j;a++)
        {
            v = DP(T[i].son,a,0) + DP(T[i].brother,j-a,k) + D(0,k) * T[i].cost;
            if (v<rs) rs=v;
            if (a<j)
            {
                v = DP(T[i].son,a,1) + DP(T[i].brother,j-a-1,k) + D(1,k) * T[i].cost;
                if (v<rs) rs=v;
            }
        }
        F[i][j][k]=rs;

    }
    return F[i][j][k];
}
void solve()
{
    if (M-1 <= N-K)
    {
        F[0][0][0]=F[0][0][1]=0;
        for (int i=1;i<=K;i++)
            F[0][i][0]=F[0][i][1]=INF;
        Ans=DP(T[1].son,K-1,1);
    }
    else
        Ans=-1;
}
int main()
{
    init();
    solve();
    printf("%d\n",Ans);
    return 0;
}
>>>>>>> origin/master
