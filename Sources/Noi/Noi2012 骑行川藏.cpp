#include<map>
#include<cmath>
#include<queue>
#include<cstdio>
#include<vector>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#define inf 1000000000
#define ll long long
#define eps 1e-12
using namespace std;
int n;
double E;
double s[10005],k[10005],v[10005],x[10005];
double cal(double ld)
{
	double tot=0;
	for(int i=1;i<=n;i++)
	{
		double l=max(0.0,v[i]),r=inf;
		while(r-l>eps)
		{
			double mid=(l+r)/2;
			if(2*ld*k[i]*mid*mid*(mid-v[i])>1)
				r=mid;
			else l=mid;
		}
		x[i]=l;
		tot+=k[i]*s[i]*(x[i]-v[i])*(x[i]-v[i]);
	}
	return tot;
}
int main()
{
	scanf("%d%lf",&n,&E);
	for(int i=1;i<=n;i++)
		scanf("%lf%lf%lf",&s[i],&k[i],&v[i]);
	double l=0,r=inf;
	while(r-l>eps)
	{
		double mid=(l+r)/2;
		if(cal(mid)>=E)l=mid;
		else r=mid;
	}
	double ans=0;
	for(int i=1;i<=n;i++)
		ans+=s[i]/x[i];
	printf("%.10lf\n",ans);
	return 0;
}


include<stdio.h>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstdio>
#define rep(i,n) for(int i=0;i<n;i++)
using namespace std;
#define ll long long
const int maxn=10010;
int N;
double E,s[maxn],v[maxn],k[maxn],maxv[maxn],tem[maxn];
double solve(double a,double b,double c,double d,double l,double r){
  double mid;
  while(l+0.000000000001<r){
   mid=(l+r)/2.0;
   double ans=a*mid*mid*mid+b*mid*mid+d;
   if (ans>0.0)l=mid;
   else r=mid;
 }
 return (l+r)/2.0;
}
void file(){
 freopen("bicycling.in","r",stdin);
 freopen("bicycling.out","w",stdout);
}
int main()
{
 //file();
 scanf("%d%lf",&N,&E);double low=0;
 rep(i,N){
  double t;
  scanf("%lf%lf%lf",&s[i],&k[i],&v[i]);
  if (s[i]>0)
   maxv[i]=sqrt(E/(k[i]*s[i]))+v[i],
   t=-(1.0/(2*k[i]*maxv[i]*maxv[i]*(maxv[i]-v[i])));
  else 
   maxv[i]=s[i];
  low=min(low,t);
 }
 //rep(i,N)printf("maxv %.8lf\n",maxv[i]);
 double left=-1000,right=low,mid,sum;
 rep(zz,60)
 {
  mid=(left+right)/2.0;sum=0.0;
  rep(i,N){
  double a=2.0*k[i]*mid;
  tem[i]=solve(a,-a*v[i],0,1.0,max(v[i],0.000001),maxv[i]);
  sum+=k[i]*s[i]*(tem[i]-v[i])*(tem[i]-v[i]);
 }
 if (sum>E) right=mid; else left=mid;
 //printf("\n ## %.10lf\n",sum);
 }
 long double ret;
 ret=0.0;
 rep(i,N)
  ret+=(long double)s[i]/(long double)tem[i];
 printf("%.10lf\n",(double)ret);
 return 0;
}


// 另 PDF中的常数优化
#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstdio>
#define rep(i,n) for(int i=0;i<n;i++)
using namespace std;
#define ll long long
const int maxn=10010;
int N;
double E,s[maxn],v[maxn],k[maxn],maxv[maxn],tem[maxn],minv[maxn];
double solve(double a,double b,double c,double d,double l,double r){
  double mid;
  while(l+0.0000001<r){
  mid=(l+r)/2.0;
  //printf("%.10lf %.10lf\n",l,r);
  double ans=a*mid*mid*mid+b*mid*mid+d;
   if (ans>0.0)l=mid;
   else r=mid;
  }
  return (l+r)/2.0;
}
void file(){
   freopen("bicycling.in","r",stdin);
   freopen("bicycling.out","w",stdout);
}
int main()
{
   //file();
   scanf("%d%lf",&N,&E);double low=0;
   rep(i,N){
   double t=0;
   scanf("%lf%lf%lf",&s[i],&k[i],&v[i]);
   if (s[i]>0)
   maxv[i]=sqrt(E/(k[i]*s[i]))+v[i],t=-(1.0/(2*k[i]*maxv[i]*maxv[i]*(maxv[i]-v[i])));
   else maxv[i]=v[i];
   minv[i]=max(0.000001,v[i]);
   low=min(low,t);
   }
   double left=-1,right=low,mid,sum;
   rep(zz,80)
   {
      mid=(left+right)/2.0;sum=0.0;
// 请不要用 while(left+0.0000000001<right) 那个的精度连样例都过不了
     rep(i,N){
     double a=2.0*k[i]*mid;
     tem[i]=solve(a,-a*v[i],0,1.0,minv[i],maxv[i]);
     sum+=k[i]*s[i]*(tem[i]-v[i])*(tem[i]-v[i]);//printf(" $$ %.10lf\n",sum);
     }
 //rep(i,N)printf("%.6lf ",tem[i]);
     if (sum>E){
         right=mid;
         rep(i,N)maxv[i]=tem[i];
        }
        else{
        left=mid;
        rep(i,N)minv[i]=tem[i];
       }
     if (fabs(sum-E)<0.00000001)break;
     //printf("\n ## %.10lf\n",sum);
     //printf("%.10lf\n",(double)clock()/CLOCKS_PER_SEC);
   }
   long double ret;
   ret=0.0;
   //printf("\n");
   rep(i,N)if (s[i]>0)ret+=(long double)s[i]/(long double)tem[i];
   printf("%.10lf\n",(double)ret);
   return 0;
}