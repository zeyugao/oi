#include<iostream>
#include<cstdio>
#include<queue>
#include<algorithm>
using namespace std;
int main ()
{
	int n;
	//为什么c++14用不了greater<int>
    priority_queue<int, vector<int>, greater<int> > Q;
    cin >> n;
    int x;
    while (n--) { cin >> x; Q.push(x);}
    int ans = 0;
	n--;
    while (n--) {
        int w1 = Q.top(); Q.pop();
        int w2 = Q.top(); Q.pop();
        ans += w1 + w2;
        Q.push(w1+w2);
    }
    cout << ans << endl;
    return 0;
}