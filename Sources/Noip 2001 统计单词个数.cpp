//思路一样，都是预处理+dp，字符串的问题，经典啦， 感觉很多问题都是用这种方法来思考的
//感觉用string 加O2优化会不会好一点，对于只能使用一次开头的问题，我用的是used数组，应该也是可以的 
//这里用的是枚举开头避免重复，他定义的vis好像都没有用到

 

#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
char dic[10][200],s[300];
int v[300][300],p,k,n,vis[300],f[300][60];

bool find(int l,int r,int t){
    int len=strlen(dic[t]);
    for(int i=l;i<=r-len+1;i++){
        bool flag=true;
        //if(vis[i]) continue;
        for(int j=0;j<len;j++){
            if(s[i+j]!=dic[t][j]) flag=false; 
        }
        if(flag) v[l][r]++;
    }
    return false;
}

int main(){
    scanf("%d%d",&p,&k);
    for(int i=1;i<=p;i++){
        char t[20];
        scanf("%s",t);
        for(int j=(i-1)*20+1;j<=i*20;j++) s[j]=t[(j-1)%20];
    }
    scanf("%d",&n);
    for(int i=1;i<=n;i++) {
        scanf("%s",dic[i]);
        for(int j=1;j<i;j++) if(!strcmp(dic[i],dic[j])) i--,n--;

    }
    //预处理v[i][j]表示[i,j]区间中有多少个单词
    for(int i=1;i<=20*p;i++)
        for(int j=i;j<=20*p;j++){
            memset(vis,0,sizeof(vis));
            for(int t=1;t<=n;t++) 
                if(find(i,j,t)) v[i][j]++;
        }
//    for(int i=1;i<=20*p;i++){
//        for(int j=1;j<=20*p;j++)printf("%d ",v[i][j]);
//        printf("\n");
//    }
//        

    //dp过程 定义f[i][j]表示前i个字符 分成j个部分的个数 则f[i][j]=max(f[i][j],f[k][j-1]+v[k+1][i]) 0<=k<=i-1;
    for(int j=1;j<=k;j++)
        for(int i=1;i<=20*p;i++)
            for(int t=j-1;t<i;t++)//这里要从j-1开始 否则会漏 
                f[i][j]=max(f[i][j],f[t][j-1]+v[t+1][i]);
    printf("%d",f[20*p][k]);
    return 0;
}
