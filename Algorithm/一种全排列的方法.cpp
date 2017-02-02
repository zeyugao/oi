#include "stdafx.h"
#define N 10000  
int a[N], x, y, n;
int f(int x, int y) {
	int b;
	b = y - x;
	x = 1 - b;
	if (x <= 0)
		x += n;
	return a[x];
}
int main() {
	std::cin >> n;
	if (n<2 || n>N) exit(0);
	for (x = 1; x <= n; x++)
		std::cin >> a[x];
	for (x = 1; x <= n; x++)
		std::cout << a[x] << " ";
	std::cout << std::endl;
	for (y = 2; y <= n; y++) {
		for (x = 1; x <= n; x++)
			std::cout << f(x, y) << " ";   
		std::cout << std::endl;
	}
	system("pause");
	return 0;
}