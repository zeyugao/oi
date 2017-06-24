#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define M 110
using namespace std;
typedef long long ll;
const int prime[] = { 10007, 11261, 14843, 19997, 21893 };
int n, m, stack[1001001], top;
ll a[M][5], f[21893][5];
inline ll F(int x, int j) {
	int i;
	ll re = 0;
	for (i = n; ~i; i--)
		//秦九韶计算
	{
		re = (re * x + a[i][j]) % prime[j];
	}
	return re;
}
inline void Input(int x) {
	static char s[10100];
	int i, j;
	bool flag = false;
	scanf("%s", s + 1);
	for (i = 1; s[i]; i++) {
		if (s[i] == '-') {
			flag = true;
		}
		else
			for (j = 0; j < 5; j++)
				//计算每个质数所对应的a%prime，a为多项式的系数
			{
				a[x][j] = ((a[x][j] << 1) + (a[x][j] << 3)/*a[x][i]*10*/ + s[i] - '0') % prime[j];
			}
	}
	if (flag)
		for (j = 0; j < 5; j++)
			//负数的模需要
		{
			a[x][j] = prime[j] - a[x][j];
		}
}
int main() {
	int i, j;
	cin >> n >> m;
	for (i = 0; i <= n; i++) {
		Input(i);
	}
	
	for (j = 0; j < 5; j++)
		for (i = 0; i < prime[j]; i++)
			//计算1~prime的值
		{
			f[i][j] = F(i, j);
		}
	for (i = 1; i <= m; i++) {
		//在取所有的质数的模下函数值是否为0
		for (j = 0; j < 5; j++)
			if (f[i % prime[j]][j]) {
				break;
			}
		if (j == 5) {
			stack[++top] = i;
		}
	}
	cout << top << endl;
	for (i = 1; i <= top; i++) {
		printf("%d\n", stack[i]);
	}
}


///*!============看不懂=========!*/
//看懂了，还是因为上面的看懂了，才知道什么意思
#define REP(i,a,b) for(int i=(a);i<=(b);i++)
#define PER(i,a,b) for(int i=(a);i>=(b);i--)
#define RVC(i,S) for(int i=0;i<(S).size();i++)
#define RAL(i,u) for(int i=fr[u];i!=-1;i=e[i].next)
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;

template<class T> inline
void read(T &num) {
	bool start = false, neg = false;
	char c;
	num = 0;
	while ((c = getchar()) != EOF) {
		if (c == '-') { start = neg = true; }
		else if (c >= '0' && c <= '9') {
			start = true;
			num = num * 10 + c - '0';
		}
		else if (start) { break; }
	}
	if (neg) { num = -num; }
}
/*============ Header Template ============*/

const int maxn = (int)(1e6) + 5;
const int mo[] = { 10079, 20011, 30047, 30133, 23339, 17093 };
int a[maxn][10];
bool ban[maxn];
char s[maxn];
int n, m;

inline void input(int x) {
	scanf("%s", s + 1);
	int n = strlen(s + 1), neg = 0, st = 1;
	if (s[1] == '-') { neg = 1, st = 2; }
	REP(i, st, n) REP(k, 0, 5)
	a[x][k] = (a[x][k] * 10 + s[i] - '0') % mo[k];
	
	if (neg) { REP(k, 0, 5) a[x][k] = (mo[k] - a[x][k]) % mo[k]; }
}

bool check(LL x, int p) {
	LL c = 0;
	PER(i, n, 1)
	//
	c = (c * x + a[i][p]) % mo[p];
	return c == 0;
}

int main() {
	int cnt = 0;
	read(n); read(m); n++;
	REP(i, 1, n) input(i);
	REP(k, 0, 5) {
		int mx = min(mo[k] - 1, m);
		REP(i, 1, mx) {
			if (!check(i, k)) {
				ban[i] = 1;
				for (int j = i + mo[k]; j <= m; j += mo[k]) { ban[j] = 1; }
			}
		}
	}
	REP(i, 1, m) if (!ban[i]) { cnt++; }
	printf("%d\n", cnt);
	REP(i, 1, m) if (!ban[i]) { printf("%d\n", i); }
	return 0;
}