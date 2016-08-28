/*令Xi+1=(a*Xi+c)%m，求Xn%g
水题。。。我们令x矩阵为
a 0
c 1
自乘n次，然后计算(aX0+c)%m%g即可

此题要写快速乘
*/

#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
typedef unsigned long long ll;
struct Martrix{
	ll martrix[2][2];
}x,ans;
ll m,a,c,x0,n,g;

/*发现普通的乘法会爆long long,怎么办？
可以用快速乘，类似快速幂，速度比快速幂多一个log 
比如说是a*b，我们设f(i)=a*i 
那么把b拆一下,f(b)=f(b/2) * 2+a *(b mod 2)*/
ll ksc(ll X,ll Y)
{
	ll re=0;
	while(Y)
	{
		if(Y&1) re+=X,re=(re>m?re-m:re);
		X+=X,X=(X>m?X-m:X);
		Y>>=1;
	}
	return re;
}
void operator *= (Martrix &x,Martrix y)
{
	int i,j,k;
	Martrix z;
	memset(&z,0,sizeof z);
	for(i=0;i<2;i++)
		for(j=0;j<2;j++)
			for(k=0;k<2;k++)
				z.martrix[i][j]+=ksc(x.martrix[i][k],y.martrix[k][j]),z.martrix[i][j]=(z.martrix[i][j]>m?z.martrix[i][j]-m:z.martrix[i][j]);
	x=z;
}
void ksm()
{
	ans.martrix[0][0]=ans.martrix[1][1]=1;
	ans.martrix[1][0]=ans.martrix[0][1]=0;
	while(n)
	{
		if(n&1) ans*=x;
		x*=x;
		n>>=1;
	}
}
int main()
{
	
	freopen("random.in","r",stdin);
	freopen("random.out","w",stdout);
	
	cin>>m>>a>>c>>x0>>n>>g;
	x.martrix[0][0]=a%m;
	x.martrix[0][1]=0;
	x.martrix[1][0]=c%m;
	x.martrix[1][1]=1;
	ksm();
	ll xn=ksc(ans.martrix[0][0],x0)+ans.martrix[1][0];
	xn%=m;
	xn%=g;
	cout<<xn<<endl;
	return 0;
}
