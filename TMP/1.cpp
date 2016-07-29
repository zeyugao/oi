int sel[20];
int num[20];
int n;
int t;
int res;
void a(int _k, int _r, int _i) {

	if (_k > n)return;
	for (int i = _i; i <= n; i++) {
		if (_r + num[i] == t) { res++; }
		else {
			a(_k + 1, _r + num[i], i + 1);
		}
	}
}
void a_do() {
	res = 0;
	cin >> n >> t;

	for (int i = 0; i <= n; i++) {
		sel[i] = 0;
		num[i] = 0;
	}
	for (int i = 1; i <= n; i++) {
		cin >> num[i];
	}
	sort(num, num + n + 1);
	a(1, 0, 1);
	cout << res;
}