#include <iostream>

using namespace std;

int main() {

    int N, m;
    int c[30], v[30];
    cin >> N >> m;
    for (int i = 0,p; i < m; i++) {
        cin >> c[i] >> p; 
        v[i] = c[i] * p;
    }
    long long dp[30010] = { 0 };
    for (int i = 0; i < m; i++) {
        for (int V = N; V >= c[i]; V--) {
            dp[V] = max(dp[V - c[i]] + v[i], dp[V]);
        }
    }
    cout << dp[N] << endl;
    return 0;
}