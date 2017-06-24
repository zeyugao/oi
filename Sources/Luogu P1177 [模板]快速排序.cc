#include <algorithm>
#include <iostream>
using namespace std;
int main() {
	int64_t num[1000001] = { 0 };
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> num[i];
	}
	sort(num, num + n);
	for (int i = 0; i < n - 1; i++) {
		cout << num[i] << " ";
		
	}
	cout << num[n - 1];
	return 0;
}