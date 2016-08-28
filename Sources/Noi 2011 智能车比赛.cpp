/*
就是求一个最短路，这条路肯定是从左到右的，我们可以用 DP 来求。 
我们先预处理出矩形之间的交点，显然智能车只能经过起点、终点和这些点。 
加上起点在终点左边（如果不是交换一下位置） 
然后 O(n2)DP ，在 DP 过程中记录一下当前点能够向后到达的点的斜率范围就可以了。 

dist[j]=min(dist[j],dist[i]+D(i,j))mink≤ki,j≤maxk
*/


#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define y1 myi
using namespace std;
#define MAXN 2000
int n,cnt,sx,sy,ex,ey,x1[MAXN+10],x2[MAXN+10],y1[MAXN+10],y2[MAXN+10];
double v,dist[MAXN*2+10];
void Read(int &x){
    static char c;
    bool f(0);
    while(c=getchar(),c!=EOF){
        if(c=='-')
            f=1;
        else if(c>='0'&&c<='9'){
            x=c-'0';
            while(c=getchar(),c>='0'&&c<='9')
                x=x*10+c-'0';
            ungetc(c,stdin);
            if(f)
                x=-x;
            return;
        }
    }
}
void read(){
    Read(n);
    for(int i=1;i<=n;i++)
        Read(x1[i]),Read(y1[i]),Read(x2[i]),Read(y2[i]);
    Read(sx),Read(sy),Read(ex),Read(ey);
    if(sx>ex)
        swap(sx,ex),swap(sy,ey);
    scanf("%lf",&v);
}
struct point{
    int x,y;
    inline point(){
    }
    inline point(int x,int y):x(x),y(y){
    }
}a[MAXN*2+10];
void prepare(){
    a[++cnt]=point(sx,sy);
    int t[4],i;
    for(i=1;i<n;i++){
        if(sx>x2[i])
            continue;
        if(ex<x2[i])
            break;
        t[1]=y1[i],t[2]=y2[i],t[3]=y1[i+1],t[0]=y2[i+1];
        sort(t,t+4);
		//取中间的两个点,一个车到x2的时候,肯定只能走允许的路径,画个图就懂了
        a[++cnt]=point(x2[i],t[1]);
        a[++cnt]=point(x2[i],t[2]);
    }
    a[++cnt]=point(ex,ey);
}
inline double sqr(double x){
    return x*x;
}
void solve(){
    int i,j;
    double mxk,mik,k;
    for(i=2;i<=cnt;i++)
        dist[i]=1e20;
    for(i=1;i<cnt;i++){
        mxk=1e20,mik=-1e20;
        for(j=i+1;j<=cnt&&mik<=mxk;j++)
            if(a[i].x==a[j].x)
                dist[j]=min(dist[j],dist[i]+abs(a[i].y-a[j].y));
            else{
                k=1.0*(a[j].y-a[i].y)/(a[j].x-a[i].x);
                if(mik<=k&&k<=mxk)
                    dist[j]=min(dist[j],dist[i]+sqrt(sqr(a[j].y-a[i].y)+sqr(a[j].x-a[i].x)));
				//上下点
                if(j&1)
                    mxk=min(mxk,k);
                else
                    mik=max(k,mik);
            }
    }
}
int main()
{
    read();
    prepare();
    solve();
    printf("%.10lf\n",dist[cnt]/v);
}