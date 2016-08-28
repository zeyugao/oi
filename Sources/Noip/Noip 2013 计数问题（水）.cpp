int main() {
	int n, x, ans=0, t;
	scanf_s("%d%d", &n, &x);
	for (int i = 1; i <= n;i++) {
		t = i;
		while (t) {
			if (t % 10 == x) 
				ans++;
			t /= 10;
		}
	}
	printf_s("%d", ans);
	system("pause");
	return 0;
}