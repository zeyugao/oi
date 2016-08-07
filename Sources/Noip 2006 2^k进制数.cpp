/*
2^k进制数
*/

/*
http://blog.tomtung.com/2007/09/noip06-digital/
那么问题其实就等同于：取N个数（对应于2k2k进制数中的N位），第1个数num[1]（对应于最高位）取值范围为[1,a0]，
其余第2~N个数num[i]取值范围都为[1,2^K)。现从其中第i(1<=i<N-1)个数num[i]开始取数，一直取到最后一个数 num[N]，
要求对于任意的 j>i 满足 num[j-1]<num[j]。问取数方案的总数。这就是很基础的组合数学问题了。
*/


/*
http://blog.sina.com.cn/s/blog_4c396f4301000bp6.html
 题目中的那个从另一角度分析就已经蕴含了这个题的基本思路。就以题目的例子为例，长度为7位的01字串按3位一段就这样分：0 000 000。其中除了首段，每段都小于(111)2，也即小于2k，而首段自然是小于2w%k（对于w%k为0时也成立）了。
    如果首段为0，则当这个2k进制数位数分别为2、3、...、[n/k]时，如果用b_max表示2k，对应的解的个数分别为C[b_max-1][2]、C[b_max-1][3]、...、C[b_max-1][n/k]（C[i][j]表示从i个数里选j个构成一组组合）。
    如果首段不为0，设首段为x，则解就有c[b_max-x-1][n/k]个。
    这样，求解的个数就搞定了，剩下的活就是高精了。求组合数可以用这个公式：C[n][m]=C[n-1][m-1]+C[n-1][m]，这样高精就只用加法了。
*/
/*http://www.yniverse.net/noip2006-2knum/

*/
#include <fstream>
#include <iostream>
using namespace std;
int c[512][512][100];
void plus1(int*,int*,int*);
void plus2(int*,int*);
int main() {
    //ifstream fin ("digital.in");
    //ofstream fout ("digital.out");
    int k,n,b_max,h_max,ans[201]={0};
    /*fin*/cin >> k >> n;
    b_max=1<<k;
    h_max=1<<(n%k);
    c[0][0][0]=c[0][0][1]=1;
    for (int i=1;i<b_max;i++) for (int j=0;j<=i;j++) {
        if (j==0) c[i][j][0]=c[i][j][1]=1;
        else plus1(c[i-1][j],c[i-1][j-1],c[i][j]);
    }
    for (int i=2;i<=n/k && i<b_max;i++) plus2(ans,c[b_max-1][i]);
    for (int i=1;i<h_max && n/k+i<b_max;i++) plus2(ans,c[b_max-i-1][n/k]);
    for (int i=ans[0];i>=1;i--) fout << ans[i];
    /*fout*/cout << endl;
    //fin.close();
    //fout.close();
    return 0;
}
void plus1(int x[],int y[],int z[]) {
    z[0]=max(x[0],y[0]);
    for (int i=1;i<=z[0];i++) {
        z[i]+=x[i]+y[i];
        z[i+1]+=z[i]/10;
        z[i]%=10;
    }
    if (z[z[0]+1]!=0) z[0]++;
}
void plus2(int x[],int y[]) {
    x[0]=max(x[0],y[0]);
    for (int i=1;i<=x[0];i++) {
        x[i]+=y[i];
        x[i+1]+=x[i]/10;
        x[i]%=10;
    }
    if (x[x[0]+1]!=0) x[0]++;
}
