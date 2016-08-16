int main()
{
    int n;
    int T;
    while(scanf("%d", &T)!=EOF)
    {
        if(T == 0) break;
        while(T--)
        {
            scanf("%d", &n);
            int r = (int)sqrt(1.0 * n);
            int sum = 0;
            if(r * r == n)
            {
                sum++;
                r--;
            }
            for(int i = 1; i <= r; i++)
            if(n % i == 0)
            {
				//n%i==0时，约数有两个：i and n/i
                sum += 2;
            }
            printf("%d\n", sum);
        }
    }
    return 0;
}

//http://blog.csdn.net/u013011841/article/details/38870585
/*
n=Σpi^ei

那么对于这道题，我们首先找出小于等于√n的所有素数，然后求出对应的指数，然后应用约数个数定理求得约数的个数。那到这里还没有完，
在√n的右边可能还有一个素数，我们判断右边是否还有素数？有的话总的约数个数为2*Σ(ei+1)

，这是因为该素数可以跟√n左边的任何一个相乘成为约数，因此约数翻倍；如果没有的话约数个数就是Σ(ei+1)*/
#include<stdio.h>
void main(){
    int N,n,i,s,r;
    while(scanf("%d",&N) != EOF){
        while(N--){
            scanf("%d",&n);
            s = 1;
            for (i = 2; i * i <= n; i++) {
                r = 0;
                while (n % i == 0) {
                    r++;
                    n /= i;
					//求出其中一个p^e
					//p=i,e=r;
				}
                if (r > 0) {
                    r++;
                    s *= r;
                }
            }
            if (n > 1)
                s *= 2;
            printf("%d\n", s);
        }
    }
}