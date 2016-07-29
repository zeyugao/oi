#include<cstdio>
#include<queue>
#define fo(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
struct nod{
    int v,d;
    bool operator <(const nod &a)const{
        return v<a.v;
    }
};
const int mn=100000+50;
priority_queue<nod> ri;
priority_queue<int> le;
int n,a[mn],s[mn],ans,md,t1,t2;
nod t;
int main(){
    scanf("%d",&n);
    fo(i,1,n)
        scanf("%d",&s[i]);
    fo(i,1,n)
        scanf("%d",&a[i]);
    fo(i,1,n){
        ri.push((nod){a[i]+(s[i]<<1),i});
    }
    ri.push((nod){0,n+1});
    le.push(0);
    int i=0;
    while (i<n){
        t=ri.top();
		//在ri（即最远推销点的右边）中挑出最大的
		//如果不满足在最远推销点右边的条件，就弹出
        if (t.d<=md){
            ri.pop();
            continue;
        }
		//此时相对增加值为a[i]+2(s[i]-s[mid])
        t1=t.v-(s[md]<<1);        
        t2=le.top();//
		
		//如果最远推销点往右移
        if (t1>t2){
            ri.pop();
            ans+=t1;
            fo(j,md+1,t.d-1)
				//将从原最远推销点到新最远推销点的全部压入le中，因为已经满足在最远推销点的左边的条件了
				//压入的只是疲劳值
                le.push(a[j]);
            md=t.d;//更新最远推销点
        }
        else{
			//否则
			//左边的剔除最大值，
            le.pop();
            ans+=t2;
        }
        printf("%d\n",ans);
        i++;
    }
    return 0;
}