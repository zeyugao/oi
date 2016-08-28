#include <iostream>
#include <cstdio>
using namespace std;
int n,h,mx=-1,down=0,last=-1,ans=0;
int max(int a,int b){
    return a>b?a:b;
}
int main(int argc, const char * argv[]) {
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&h);
        if(down==1&&h>last) ans+=mx-last,mx=-1;
        mx=max(mx,h);
        if(i==n-1) ans+=mx;
        if(h<last) down=1;
        last=h;
    }
    cout<<ans;
    return 0;
}