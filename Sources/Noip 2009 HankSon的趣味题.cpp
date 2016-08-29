/*
1． x 和 a0 的最大公约数是 a1； 
2． x 和b0 的最小公倍数是 b1。 


1.gcd(x,a0)=a1  => gcd(x/a1,a0/a1)=1
2.//x*b0/gcd(x,b0)=b1 => ①x*(b0/gcd(x,b0))=b1
  //                     ②gcd(x,b1/b0)=1
  //有点奇怪
  //
  My opinion: x*b0/gcd(x,b0)=b1 => gcd(b1/x,b1/b0)=1;
  
  
         由上可知，x一定为b1的一个约数，那么直接从1到sqrt(b1)进行枚举，找到x，并判断是否符合要求即可。
*/
//这一个看懂了？！ 
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
int ans;
int gcd(int a,int b)
{
    return b==0?a:gcd(b,a%b);
}
int main()
{
    int T,i,j,a0,a1,b0,b1;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d%d",&a0,&a1,&b0,&b1);
        //len=sqrt(b1+0.5);
        ans=0;
        for(i=1;i*i<=b1;i++)
        {
            if(b1%i==0){
                if(i%a1==0&&(gcd(i/a1,a0/a1)==1)&&(gcd(b1/b0,b1/i)==1))
                  ans++;
                j=b1/i;
                // 这里应该是：
				//由于只循环到√n，导致有部分没有枚举到，j=b1/i应该要证明，时间复杂度O((√n)logn) 
				//如果循环到n，就不用这条语句，时间复杂度O(nlogn) 超时了 
                if(j%a1!=0||i==j) continue;
                if((gcd(j/a1,a0/a1)==1)&&(gcd(b1/b0,b1/j)==1))
                  ans++;
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}

//这一个程序没看太懂 
#include<cstdio>
#include<cmath>
using namespace std;

int gcd(int x,int y)
{
  int t;
  while(x%y)t=x%y,x=y,y=t;
  return y;
}

int main()
{
  int a0,a1,b0,b1;
  int i,j,k,n,x,y,z,sum;
  scanf("%d",&n);
  for(i=1;i<=n;i++)
    {
      scanf("%d%d%d%d",&a0,&a1,&b0,&b1);
	  x=a0/a1,y=b1/b0,z=(int)sqrt(b1*1.0);
	  for(sum=0,j=1;j<=z;j++)if(b1%j==0)
	    {
	      if(j%a1==0 && gcd(j/a1,x)==1 && gcd(b1/j,y)==1)sum++;
	      
	      if((b1/j)%a1==0 && gcd((b1/j)/a1,x)==1 && gcd(j,y)==1)sum++;
	    }
	  if(z*z==b1 && z%a1==0 && gcd(z/a1,x)==1 && gcd(z,y)==1)sum--;  
	  printf("%d\n",sum);		
    }
  return 0;
}
