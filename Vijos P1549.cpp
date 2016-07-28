
vijos1549中位数

//1-n的排列的话，就是已经保证了只有一个b，然后，可以对于每一个点记录f[i]为其前面数的前缀和（大于b为1，小于b则为-1，等于b为0），然后，sum[a][0]记录b所在位置前面到达-a的次数，sum[a][1]则记录到达a的次数，sum[0][0]记录达到0的次数。。。这样就可以o(n)求出结果了，详细见代码：

using namespace std;
const int MAXN=100000+10;
int num[MAXN],f[MAXN],sum[MAXN][2];
int main()
{
    int n,a,b,bri,ans=0;
    scanf("%d%d",&n,&b);   
    for(int i=1;i<=n;i++){
      scanf("%d",&num[i]);
      if(num[i]
      else if(num[i]>b) f[i]=f[i-1]+1;
      else if(num[i]==b){bri=i; f[i]=f[i-1];}
    }
// 等价于for(i;p...1) s[i]+=a[i]//num[i]>0 <0 =0
// for(i;p+1...N) s[i]+=a[i]//num[i]>0 <0 =0
//从p中间开始，找到p两边s[]数值和为0的值
    for(int i=bri-1;i>=0;i--){
      a=f[bri]-f[i];
      if(a<0) sum[-a][0]++;
      else if(a>0) sum[a][1]++;
      else sum[0][0]++;
    }
    for(int j=bri;j<=n;j++){
      a=f[j]-f[bri-1];
      if(a>0) ans+=sum[a][0];
      else if(a<0) ans+=sum[-a][1];
      else ans+=sum[0][0];
     }
cout<<ans<<endl;
return 0;
}

顾名思义,就是要<b的数个数=>b的数的个数 
b序列中的位置为p
如果a[i]>b 就定义 a[i]=1
如果a[i]<b 就定义 a[i]=-1
然后用f[j]=a[1]+a[2]+a[3]+...+a[j]

如果有f[i]=f[j] (i<=p-1,j>=p),就inc(ans)
输出答案 ans
