<<<<<<< HEAD
/*ç»å…¸çš„æ ‘å½¢åŠ¨æ€è§„åˆ’é¢˜ï¼Œæ¶‰åŠåˆ°äº†å­©å­ä¹‹é—´çš„åˆ†é…é—®é¢˜ï¼Œéœ€è¦ç”¨å­©å­å…„å¼Ÿè¡¨ç¤ºæ³•æ¥å®ç°ã€‚

é¦–å…ˆï¼Œåˆ¤æ–­æœ‰è§£çš„æ¡ä»¶æ˜¯M-1<=N-Kã€‚ç”±äº2<=M<=Nï¼Œå½“M=2æ—¶ï¼Œç›¸å½“äºæŠŠæ‰€æœ‰èŠ‚ç‚¹æŸ“ä¸Šä¸åŒé¢œè‰²ï¼Œä¸¤ç«¯é¢œè‰²ç›¸ åŒçš„è¾¹è¦è¢«ç®—ä¸Šæƒå€¼ï¼Œæ±‚æƒå€¼æœ€å°çš„æ–¹æ¡ˆã€‚å‡å®šâ€œå¤§å¤´â€è¦åƒçš„èŠ‚ç‚¹ä¸ºé»‘è‰²èŠ‚ç‚¹ï¼Œå…¶ä½™ä¸ºç™½è‰²èŠ‚ç‚¹ã€‚æˆ‘ä»¬éœ€è¦è€ƒè™‘æ‰€æœ‰çš„ä¸¤ç«¯é¢œè‰²ç›¸åŒçš„è¾¹ã€‚å¦‚æœM>2ï¼Œåˆ™ åªéœ€è¦è€ƒè™‘ä¸¤ç«¯éƒ½æ˜¯é»‘è‰²çš„è¾¹ã€‚å› ä¸ºå½“å‰©ä½™é¢œè‰²å¤šäº1æ—¶ï¼Œä¸€å®šå¯ä»¥æ‰¾åˆ°ä¸€ç§æ–¹æ¡ˆï¼Œä½¿å¾—â€œå°å¤´â€ä¸ä¼šåä¸‹æ ‘æã€‚

å®šä¹‰i.sonä¸ºiçš„ç¬¬ä¸€ä¸ªå­©å­ï¼Œi.brotherä¸ºiçš„å…„å¼ŸèŠ‚ç‚¹ï¼Œi.costä¸ºiå‘å…¶çˆ¶äº²è¿æ¥çš„è¾¹çš„æƒå€¼ã€‚

çŠ¶æ€å®šä¹‰

F[i][j][k]ä¸ºä»¥iä¸ºæ ¹çš„å­æ ‘åŠä»¥å…¶å³è¾¹çš„å…„å¼Ÿä¸ºæ ¹çš„å­æ ‘ä¸­ï¼Œæœ‰jä¸ªèŠ‚ç‚¹è¢«æŸ“é»‘ï¼Œä¸”içš„çˆ¶äº²èŠ‚ç‚¹çš„é¢œè‰²ä¸ºk(1ä¸ºé»‘è‰²ï¼Œ0ä¸ºå…¶å®ƒ)æ—¶çš„æœ€å°è´¹ç”¨

çŠ¶æ€è½¬ç§»æ–¹ç¨‹

F[i][j][k]=Min
{
    F[i.son][j'][0] + F[i.brother][j-j'][k] + D(0,k)  i.cost,
    F[i.son][j'][1] + F[i.brother][j-j'-1][k] + D(1,k)  i.cost,
}
å…¶ä¸­ D(a,b)è¡¨ç¤ºä¸¤ç«¯é¢œè‰²ä¸ºa,bä¹‹é—´çš„è¾¹æ˜¯å¦è¦è¢«åƒæ‰ï¼Œå…·ä½“å®šä¹‰ä¸º
D(a,b) = 
{
    1 | a=b=1
    1 | a=b=0 ä¸” M=2
    0 | å…¶å®ƒæƒ…å†µ
}
è¾¹ç•Œæ¡ä»¶
èŠ‚ç‚¹0è¡¨ç¤ºä¸€ä¸ªè™šæ‹Ÿçš„ç©ºèŠ‚ç‚¹

F[0][0][k] = 0 (k=0,1)

F[0][j][k] = æ— ç©·å¤§ (j>0 k=0,1)

ç›®æ ‡çŠ¶æ€

F[èŠ‚ç‚¹1.son][K-1][1]

 * Problem: NOI2002 dragon
 * Author: Guo Jiabao
 * Time: 2009.5.18 14:02
 * State: Solved
 * Memo: æ ‘å½¢åŠ¨æ€è§„åˆ’ å­©å­å…„å¼Ÿåˆ†é…é—®é¢˜
*/

//æ ‘å½¢dpå¤§æ³•
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
	//è¿™é‡Œè¿™æ ·åš,å¯ä»¥ç›´æ¥ç”¨V[a].next
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
/*¾­µäµÄÊ÷ĞÎ¶¯Ì¬¹æ»®Ìâ£¬Éæ¼°µ½ÁËº¢×ÓÖ®¼äµÄ·ÖÅäÎÊÌâ£¬ĞèÒªÓÃº¢×ÓĞÖµÜ±íÊ¾·¨À´ÊµÏÖ¡£

Ê×ÏÈ£¬ÅĞ¶ÏÓĞ½âµÄÌõ¼şÊÇM-1<=N-K¡£ÓÉÓÚ2<=M<=N£¬µ±M=2Ê±£¬Ïàµ±ÓÚ°ÑËùÓĞ½ÚµãÈ¾ÉÏ²»Í¬ÑÕÉ«£¬Á½¶ËÑÕÉ«Ïà Í¬µÄ±ßÒª±»ËãÉÏÈ¨Öµ£¬ÇóÈ¨Öµ×îĞ¡µÄ·½°¸¡£¼Ù¶¨¡°´óÍ·¡±Òª³ÔµÄ½ÚµãÎªºÚÉ«½Úµã£¬ÆäÓàÎª°×É«½Úµã¡£ÎÒÃÇĞèÒª¿¼ÂÇËùÓĞµÄÁ½¶ËÑÕÉ«ÏàÍ¬µÄ±ß¡£Èç¹ûM>2£¬Ôò Ö»ĞèÒª¿¼ÂÇÁ½¶Ë¶¼ÊÇºÚÉ«µÄ±ß¡£ÒòÎªµ±Ê£ÓàÑÕÉ«¶àÓÚ1Ê±£¬Ò»¶¨¿ÉÒÔÕÒµ½Ò»ÖÖ·½°¸£¬Ê¹µÃ¡°Ğ¡Í·¡±²»»áÍÌÏÂÊ÷Ö¦¡£

¶¨Òåi.sonÎªiµÄµÚÒ»¸öº¢×Ó£¬i.brotherÎªiµÄĞÖµÜ½Úµã£¬i.costÎªiÏòÆä¸¸Ç×Á¬½ÓµÄ±ßµÄÈ¨Öµ¡£

×´Ì¬¶¨Òå

F[i][j][k]ÎªÒÔiÎª¸ùµÄ×ÓÊ÷¼°ÒÔÆäÓÒ±ßµÄĞÖµÜÎª¸ùµÄ×ÓÊ÷ÖĞ£¬ÓĞj¸ö½Úµã±»È¾ºÚ£¬ÇÒiµÄ¸¸Ç×½ÚµãµÄÑÕÉ«Îªk(1ÎªºÚÉ«£¬0ÎªÆäËü)Ê±µÄ×îĞ¡·ÑÓÃ

×´Ì¬×ªÒÆ·½³Ì

F[i][j][k]=Min
{
    F[i.son][j'][0] + F[i.brother][j-j'][k] + D(0,k)  i.cost,
    F[i.son][j'][1] + F[i.brother][j-j'-1][k] + D(1,k)  i.cost,
}
ÆäÖĞ D(a,b)±íÊ¾Á½¶ËÑÕÉ«Îªa,bÖ®¼äµÄ±ßÊÇ·ñÒª±»³Ôµô£¬¾ßÌå¶¨ÒåÎª
D(a,b) = 
{
    1 | a=b=1
    1 | a=b=0 ÇÒ M=2
    0 | ÆäËüÇé¿ö
}
±ß½çÌõ¼ş
½Úµã0±íÊ¾Ò»¸öĞéÄâµÄ¿Õ½Úµã

F[0][0][k] = 0 (k=0,1)

F[0][j][k] = ÎŞÇî´ó (j>0 k=0,1)

Ä¿±ê×´Ì¬

F[½Úµã1.son][K-1][1]

 * Problem: NOI2002 dragon
 * Author: Guo Jiabao
 * Time: 2009.5.18 14:02
 * State: Solved
 * Memo: Ê÷ĞÎ¶¯Ì¬¹æ»® º¢×ÓĞÖµÜ·ÖÅäÎÊÌâ
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
