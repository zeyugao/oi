#include <cstdio>
#include <cstring>
using namespace std;

int n, m;

bool examine(long long x, long long y) {
	if (!(1 <= x && x <= n && 1 <= y && y <= n)) {
		return false;
	}
	
	printf("examine %d %d\n", (int) x, (int) y);
	fflush(stdout);
	char response[16];
	scanf("%s", response);
	return (strcmp(response, "true") == 0);
}
long long findBorder(long long x, long long y, long long dx, long long dy) {
	long long s = 1;
	
	while (examine(x + s * dx, y + s * dy)) {
		s *= 2;
	}
	
	long long left = s / 2;
	long long right = s;
	
	while (left < right) {
		long long mid = (left + right + 1) / 2;
		
		if (examine(x + mid * dx, y + mid * dy)) {
			left = mid;
		}
		else {
			right = mid - 1;
		}
	}
	
	return left;
}
int main() {
	int x, y;
	scanf("%d%d%d", &n, &x, &y);
	x -= findBorder(x, y, -1, 0);
	y -= findBorder(x, y, 0, -1);
	m = findBorder(x, y, 1, 0) + 1;
	
	while (examine(x - m * 2, y)) {
		x -= m * 2;
	}
	
	while (examine(x, y - m * 2)) {
		y -= m * 2;
	}
	
	if (examine(x - m, y - m)) {
		x -= m, y -= m;
	}
	
	x += m * 2 + m / 2;
	y += m * 2 + m / 2;
	printf("solution %d %d\n", x, y);
	fflush(stdout);
	return 0;
}
