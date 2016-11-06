/*hash解法复杂度ON：
这个优化很绝！首先先要推出一个性质：假如某个序列男生和女生的人数相差相等的，那么这个序列是一个合法的序列。
//在某一个位置的高度差如果是Δh，那么如果从这个位置开始男女生增加相同的人数，到序列的末尾时，高度差一定还会是Δh
//设一开始到某个位置有男生a人，女生b人，那么高度差就是a-b，如果从这个位置开始，男女生的人数相同，那么就说明男女生都增加了x人，(a+x)-(b+x)=a-b=Δh
例如样例：
9
0 1 0 0 0 1 1 0 0
 
先预处理出两种人的一维数组：
man:011112333

won:112344456
won是女孩，man是男孩
 
 
算出它们的高度差：
-1 0 -1 -2 -3 -2 -1 -2 -3
 
自己分析比较这三者的关系，我就不讲了。
 
注意，这里的高度差不能取绝对值！
 
推得这个规律后，就可以进行hash了。首先在高度差中从1到N扫一遍，记下每个差的所在位置。然后再从高度差数组中倒着扫一遍，找出最后一个差的位置。两者减一减，求最大值（这里就是计数了）输出即可。
*/
#include "stdafx.h"
using namespace std;
int n,man[100005],woman[100005],newa[100005];
template
  struct Array {
    T data[UBound-LBound+1];
    T& operator[](int i) {return data[i-LBound];}
};

Array  hash;

int main()
{   
   scanf("%d",&n); 
   newa[0]=man[0]=woman[0]=0;
   for(int i=1;i<=n;i++){
      int x;
      scanf("%d",&x);
      woman[i]=woman[i-1],man[i]=man[i-1];
      if(!x) woman[i]=woman[i-1]+1;
      else man[i]=man[i-1]+1;
      newa[i]=man[i]-woman[i];
   }
   int ans=0;
   for(int i=-n;i<=n;i++)
    hash[i]=-1;
   for(int i=0;i<=n;i++){
      if(hash[newa[i]]==-1)  hash[newa[i]]=i;
      else ans=max(ans,i-hash[newa[i]]);
   }
   cout<<ans<<endl;
   //system("pause");
   return 0;
}



#include<cstdio>
#include<map>
#include<vector>
using namespace std;

int n,ans=0;
vector<int> s;
map<int,int> look_up;

int main()
{
    scanf("%d",&n);
    s.push_back(0);
    for(int i=1;i<=n;i++)
    {
        int k;
        scanf("%d",&k);
        if(k) s.push_back(s[i-1]+1);
            else s.push_back(s[i-1]-1);
    }
    for(int i=0;i<=n;i++)
    {
        if(look_up.count(s[i])) ans=max(ans,i-look_up[s[i]]);
            else look_up[s[i]]=i;
    }
    printf("%d\n",ans);
    return 0;
}
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N = 1000000+10;
int Ans,n,s[N],p[N*2];
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i){
        scanf("%d",&s[i]);
        if(s[i]) s[i]=s[i-1]+1;
        else s[i]=s[i-1]-1;
    }
    memset(p,-1,sizeof(p));
    for(int i=0;i<=n;++i){
        if(p[s[i]+n]!=-1){
            Ans = max(Ans,i-p[s[i]+n]);
        }else{
            p[s[i]+n]=i;
        }
    }
    printf("%d\n",Ans);
    return 0;
}