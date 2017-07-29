#include <iostream>
#include <algorithm>
#include <string.h>
#include <cstdio>

using std::cout;
using std::cin;
using std::endl;

int a, b, n;
int matrix[1001][1001] = { 0 };

int r_max[1001][1001], r_min[1001][1001];
int c_max[1001][1001], c_min[1001][1001];

int q[1001],p[1001];

//Summary:
//	求两次单调队列
//	第一次找出每一行的以j为首位置的最大值和最小值
//	第二次在最大值最小值矩阵跑单调队列

int main() {
	cin >> a >> b >> n;

	for (int i = 1; i <= a; i++) {
		for (int j = 1; j <= b; j++) {
			cin >> matrix[i][j];
		}
	}
	int tail;
	int head;
	for (int current_row = 1; current_row <= a; current_row++) {
		tail = 0;
		head = 1;
		memset(q, 0, sizeof(q));
		memset(p, 0, sizeof(p));

		for (int i = 1; i <= b; i++) {
			while (head <= tail&&q[tail] <= matrix[current_row][i]) {
				tail--;
			}
			q[++tail] = matrix[current_row][i];
			p[tail] = i;
			while (p[head] <= i - n) {
				head++;
			}
			if (i >= n) {
				r_max[current_row][i] = q[head];
				//printf("r_max[%d][%d] = %d\n", current_row, i, r_max[current_row][i]);
			}
		}
		tail = 0;
		head = 1;
		memset(q, 0, sizeof(q));
		memset(p, 0, sizeof(p));
		for (int i = 1; i <= b; i++) {
			while (head <= tail&&q[tail] >= matrix[current_row][i]) {
				tail--;
			}
			q[++tail] = matrix[current_row][i];
			p[tail] = i;
			while (p[head] <= i - n) {
				head++;
			}
			if (i >= n) {
				r_min[current_row][i] = q[head];
				//printf("r_min[%d][%d] = %d\n", current_row, i, r_min[current_row][i]);
			}
		}
	}
	/*
	cout << endl;
	for (int i = 1; i <= a; i++) {
		for (int j = n; j <= b; j++) {
			cout << r_max[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 1; i <= a; i++) {
		for (int j = n; j <= b; j++) {
			cout << r_min[i][j] << " ";
		}
		cout << endl;
	}*/
	for (int current_col = n; current_col <= b; current_col++) {
		tail = 0;
		head = 1;
		memset(q, 0, sizeof(q));
		memset(p, 0, sizeof(p));
		for (int i = 1; i <= a; i++) {
			while (head <= tail&&q[tail] <= r_max[i][current_col]) {
				tail--;
			}
			q[++tail] = r_max[i][current_col];
			p[tail] = i;
			while (p[head] <= i - n) {
				head++;
			}
			if (i >= n) {
				c_max[i][current_col] = q[head];
			}
		}
		tail = 0;
		head = 1;
		memset(q, 0, sizeof(q));
		memset(p, 0, sizeof(p));
		for (int i = 1; i <= a; i++) {
			while (head <= tail&&q[tail] >= r_min[i][current_col]) {
				tail--;
			}
			q[++tail] = r_min[i][current_col];
			p[tail] = i;
			while (p[head] <= i - n) {
				head++;
			}
			if (i >= n) {
				c_min[i][current_col] = q[head];
			}
		}
	}
	/*cout << endl;
	for (int i = n; i <= a; i++) {
		for (int j = n; j <= b; j++) {
			cout << c_max[i][j] << " ";
		}
		cout << endl;
	}
	for (int i = n; i <= a; i++) {
		for (int j = n; j <= b; j++) {
			cout << c_min[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;*/
	int ans = 1000000000;
	for (int i = n; i <= a; i++) {
		for (int j = n; j <= b; j++) {
			ans = (std::min)(ans, c_max[i][j] - c_min[i][j]);
		}
	}
	cout << ans;
	//system("pause");
	return 0;
}