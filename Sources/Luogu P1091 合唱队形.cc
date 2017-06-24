#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>

using std::cin;
using std::endl;
using std::cout;

int n;
int T[110] = {0};
int dp_left[110] = {0};
int dp_right[110] = {0};
int main() {
	cin >> n;
	
	for (int i = 1; i <= n; i++) {
		cin >> T[i];
	}
	dp_left[1] = 1;
	for (int i = 2; i <= n; i++) {
		dp_left[i] = 1;
		for (int j = i - 1; j >= 1; j--) {
			if (T[i] > T[j]) {
				dp_left[i] = (std::max)(dp_left[i], dp_left[j] + 1);
			}
		}
	}
	dp_right[n] = 1;
	for (int i = n - 1; i >= 1; i--) {
		//开始之前要进行初始化
		//每个位置都可以从当前位置出发，有至少一个最长长度
		dp_right[i] = 1;
		for (int j = i + 1; j <= n; j++) {
			if (T[i] > T[j]) {
				dp_right[i] = (std::max)(dp_right[i], dp_right[j] + 1);
			}
		}
	}
	int ans = 1;
	for (int i = 1; i <= n; i++) {
		ans = (std::max)(ans, (dp_left[i] + dp_right[i]));
	}
	
	cout << n - ans + 1 << endl;
	return 0;
}
