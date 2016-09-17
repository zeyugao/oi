//1549的提升版。。。然而需要输入优化。。。
#include<cstdio>
#include<iostream>
#define MAXN 2005
#define LL long long 
using namespace std;

LL use[MAXN][MAXN];
int n,m;
LL ans=0;
LL h[MAXN];
int f[MAXN];
int num[MAXN][2][MAXN];
int q[MAXN][2];

inline LL ab(LL x){return x>0 ? x:-x;}

LL into(){
    char tmp=getchar();
    int re=0;
    while(tmp<'0'||tmp>'9')tmp=getchar();
    while(tmp>='0'&&tmp<='9')re=re*10+(tmp-'0'),tmp=getchar();
    return re;
}

int main(){
    n=into();m=into();
    int i,j,g;
    for(i=1;i<=n;i++)
        h[i]=into();
    int mid,t1,t2,tmp;
    for(i=1;i<=n;i++)
    {
        mid=h[i];
        q[0][0]=0;
        //同P1459
        for(j=1;j<=n;j++)
        {
            if(h[j]>mid)f[j]=f[j-1]+1;
            else    if(h[j]<mid)f[j]=f[j-1]-1;
            else    f[j]=f[j-1];   
            q[j][0]=q[j][1]=0;
        }
        //mid前多出的数，储存有这么多数，是正还是负
        for(j=0;j<i;j++)
        {
            tmp=f[i]-f[j];
            if(tmp>0)t1=tmp,t2=1;
            else if(tmp<0)t1=-tmp,t2=0;
            else  t1=0,t2=0;
            //储存，q[][]用于储存是第几个达到tmp的数，
            //num记录第q[][]个达到tmp的左值
            num[t1][t2][++q[t1][t2]]=j+1;   
        }
        for(j=i;j<=n;j++)
        {
            tmp=f[j]-f[i];
            if(tmp>0)t1=tmp,t2=0;
            else if(tmp<0)t1=-tmp,t2=1;
            else t1=0,t2=0;
            //大小顺序:num[,,]<mid<i
            //取出第g个达到tmp，并正负相反的数，将其作为左端点，右端点是i，
            for(g=1;g<=q[t1][t2];g++)
                use[num[t1][t2][g]][j]=mid;
        }
    }
    for(i=1;i<=m;i++)
    {
        t1=into();t2=into();
        if((t2-t1)%2==1)mid=use[t1][t2-1];
        else mid=use[t1][t2];
        for(j=t1;j<=t2;j++)
            ans+=ab(h[j]-mid);
    }
    printf("%lld\n",ans);
    return 0;
}
