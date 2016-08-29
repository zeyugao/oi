#include <iostream>
using namespace std;

int main() {
	void * number = 0;
	if (sizeof(&number) == 4) {
		long long n, m;
		cin >> n >> m;
		if (n > m)n = m;
		long long tmp = 1, ans = 0;
		for (int i = 1; i <= n; i++) {
			tmp = (tmp*i) % m;
			ans = (tmp + ans) % m;
		}
		cout << ans << endl;
	}
	return 0;
}