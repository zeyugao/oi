#include <iostream>
#include <string>
#include <algorithm>
#include <cstdio>
#include <string.h>

using std::cout;
using std::cin;
using std::endl;
using std::string;

bool cmp(int a, int b) {
	return a > b;
}

int n;
int len[66] = {0};
int sum = 0;
bool visited[66] = {0};


int dfs(int min_len, int left_num, int left_len, int pos) {
	if (left_num == 0 && left_len == 0) { //所有的都拼完了
		return 1;
	}
	if (left_len == 0) {  //拼完了一个，需要从新再拼一个长度为min_len的东西了
		left_len = min_len;
		pos = 1;
	}
	for (int i = pos; i <= n; i++) {
		if (visited[i]) {
			continue;
		}
		if (len[i] > left_len) {
			continue;
		}
		visited[i] = true;
		if (dfs(min_len, left_num - 1, left_len - len[i], i + 1)) {
			return 1;
		}
		visited[i] = false;
		//现在无法做到，以后也一定无法做到
		if (left_len == len[i] || left_len ==  min_len) {
			break;
		}
		while (len[i] == len[i + 1]) {
			i++;
		}
	}
	return 0;
}
int main() {
	//std::ios_base::sync_with_stdio(false);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		int read_temp;
		//cin>>read_temp;
		scanf("%d", &read_temp);
		if (read_temp > 50) {
			n--;
			i--;
			continue;
		}
		len[i] = read_temp;
		sum += read_temp;
	}
	std::sort(len + 1, len + n + 1, cmp);
	int min_len = 0;
	for (min_len = 1; min_len <= sum; min_len++) {
		if (sum % min_len != 0) { //无法通过n个min_len长度的分块结合为目标长度
			continue;
		}
		memset(visited, 0, sizeof(visited));
		if (dfs(min_len, n, min_len, 1)) {
			break;
		}
	}
	cout << min_len;
	return 0;
}