#include<iostream>
#include<cmath>
#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include<string>
#include<cstring>
#define LL long long
using namespace std;
int x[1000005],y[1000005],d[1000005],s[1000005],a[1000005];
int n,m;
int check(int q){
    memset(s,0,sizeof(s));
    for(int i = 1;i <= q;i++){
        s[x[i]] += d[i];
        s[y[i]+1] -= d[i];
    }
    int tot = 0;
    for(int i = 1;i <= n;i++){
        tot += s[i];
        if(tot > a[i])
           return 0;
    }
    return 1;
}
int main(){
    freopen("classroom.in","r",stdin);
    //freopen(" classroom.out","w",stdout);
    scanf("%d%d",&n,&m);
    for(int i = 1;i <= n;i++)
       scanf("%d",&a[i]);
    for(int i = 1;i <= m;i++)
       scanf("%d%d%d",&d[i],&x[i],&y[i]);
    int l = 1,r = m,ans = 0,mid;
    while(l <= r){
         mid = (l + r) >> 1;
         if(check(mid) == 0){
            ans = mid;
            r = mid-1;
    }
         else l = mid+1;
    }
    if(ans != 0)
       printf("-1\n%d",ans);
    else printf("0");
    return 0;
}


#include<iostream>
#include<cstdio>
using namespace std;

const int INF = 1000000000;
const int maxn = 1000000 + 10;

struct Book {
    int d, s, t;
    Book (int d = 0, int s = 0, int t = 0) : d(d), s(s), t(t) {}
};

int n, m;
int r[maxn], bor[maxn], ret[maxn];
Book books[maxn];

bool check (int mid) {
    for (int i = 1; i <= n; i++) bor[i] = ret[i] = 0;
    for (int i = 1; i <= mid; i++) {
        bor[books[i].s] += books[i].d;
        ret[books[i].t] += books[i].d;
    }
    int room = 0;
    for (int i = 1; i <= n; i++) {
        room += bor[i];
        if (room > r[i]) return false;
        room -= ret[i];
    }
    return true;
}

int main () 
{
//    freopen("in.txt", "r", stdin);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) scanf("%d", &r[i]);
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d", &books[i].d, &books[i].s, &books[i].t);

    int L = 0, R = m;
    while (L < R) {
        int M = L + (R-L+1)/2;
        if (check(M)) L = M; else R = M-1;
    }
    if (L == m) cout << "0\n";
    else cout << "-1\n" << L+1 << "\n";
    return 0;
}

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
inline int read() {
    int x=0,f=1; char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-')f=-1; ch=getchar();}
    while(ch>='0'&&ch<='9') {x=x*10+ch-'0'; ch=getchar();}
    return x*f;
}
struct APP {
    int d, s, t;
}a[1000005];
int n, m;
int r[1000005];
LL c[1000005];

void Input() {
    n=read(); m=read();
    for(int i=1; i<=n; i++) r[i] = read();
    for(int i=1; i<=m; i++) {
        a[i].d = read();
        a[i].s = read();
        a[i].t = read();
    }
}

bool OK(int bd) {
    memset(c, 0, sizeof(c));
    for(int i=1; i<=bd; i++) {
        c[a[i].s] += (LL)a[i].d;
        c[a[i].t+1] -= (LL)a[i].d;
    }
    for(int i=1; i<=n; i++) {
        c[i] += c[i-1];
        if(c[i] > r[i]) return false;
    }
    return true;
}

void Solve() {
    int l=1, r=m;
    while(l <= r) {
        int mid = (l+r) >> 1;
        if(OK(mid)) l = mid + 1;
        else r = mid - 1;
    }
    printf("-1\n%d", l);
}

int main() {
    Input();
    if(OK(m)) printf("0");
    else Solve();
    return 0;
}


#include <cstdio>
#include <cstdlib>
#include <cstring>
#define L(a) (a<<1)
#define R(a) (a<<1|1)
using namespace std;
inline int min(int a,int b) { return a<b?a:b; }
inline int max(int a,int b) { return a>b?a:b; }
inline int read() {
    int x=0,f=1; char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-')f=-1; ch=getchar();}
    while(ch>='0'&&ch<='9') {x=x*10+ch-'0'; ch=getchar();}
    return x*f;
}
struct Node {
    int Le, Re;
    int Min;
    int Lazy;
}s[4000005];
int n, m, cnt=0;
bool flag=true;

void Build_tree(int p, int l, int r) {
    s[p].Le = l; s[p].Re = r;
    s[p].Lazy = 0;
    if(l == r) {
        s[p].Min = read();
        return;
    }
    int mid = (l + r) >> 1;
    Build_tree(L(p), l, mid);
    Build_tree(R(p), mid+1, r);
    s[p].Min = min(s[L(p)].Min, s[R(p)].Min);
}

void Pushdown(int p) {
    if(s[p].Le == s[p].Re || s[p].Lazy == 0) return;
    s[L(p)].Lazy += s[p].Lazy;
    s[R(p)].Lazy += s[p].Lazy;
    s[L(p)].Min -= s[p].Lazy;
    s[R(p)].Min -= s[p].Lazy;
    s[p].Lazy = 0;
    s[p].Min = min(s[L(p)].Min, s[R(p)].Min);
}

void Modify(int p, int l, int r, int d) {
    Pushdown(p);
    if(s[p].Le==l && s[p].Re==r) {
        s[p].Lazy += d;
        s[p].Min -= d;
        if(s[p].Min < 0) flag = false;
        return;
    }
    int mid = (s[p].Le + s[p].Re) >> 1;
    if(r <= mid) Modify(L(p), l, r, d);
    else if(l > mid) Modify(R(p), l, r, d);
    else {
        Modify(L(p), l, mid, d);
        Modify(R(p), mid+1, r, d);
    }
    s[p].Min = min(s[L(p)].Min, s[R(p)].Min);
}

int main() {
    n=read(); m=read();
    Build_tree(1, 1, n);
    while((++cnt) <= m) {
        int _d=read(), _l=read(), _r=read();
        Modify(1, _l, _r, _d);
        if(!flag) break;
    }
    if(flag) printf("0");
    else printf("-1\n%d", cnt);
}