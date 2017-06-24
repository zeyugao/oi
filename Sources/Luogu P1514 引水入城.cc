
#include <iostream>
//#include <Windows.h>
#include <algorithm>
#include <string.h>

using std::cout;
using std::cin;
using std::endl;

struct City {
	int left, right;
} city[510] = { 0 };

int M, N;
int height[510][510] = { 0 };

bool visited[510][510];
bool link[510][510] = { 0 };
bool check[510] = { 0 };

int dp[510] = { 0 };
void dfs(int x, int y) {
	visited[x][y] = true;
	
	if (y + 1 <= M && height[x][y] > height[x][y + 1] && !visited[x][y + 1]) {
		dfs(x, y + 1);
	}
	if (x + 1 <= N && height[x][y] > height[x + 1][y] && !visited[x + 1][y]) {
		dfs(x + 1, y);
	}
	if (x - 1 >= 1 && height[x][y] > height[x - 1][y] && !visited[x - 1][y]) {
		dfs(x - 1, y);
	}
	if (y - 1 >= 1 && height[x][y] > height[x][y - 1] && !visited[x][y - 1]) {
		dfs(x, y - 1);
	}
}

int main() {
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			int temp;
			cin >> temp;
			height[i][j] = temp;
			//cin >> height[i][j];
		}
	}
	
	for (int i = 1; i <= M; i++) {
		if (height[1][i] >= height[1][i + 1] &&
				height[1][i] >= height[1][i - 1]) {
				
			memset(visited, 0, sizeof(visited));
			
			dfs(1, i);
			
			for (int j = 1; j <= M; j++) {
				link[i][j] = visited[N][j];
				check[j] = check[j] || visited[N][j];
			}
		}
	}
	int count = M;
	for (int i = 1; i <= M; i++) {
		if (check[i]) {
			count--;
		}
	}
	if (count) {
		cout << "0" << endl << count;
		return 0;
	}
	
	memset(city, -1, sizeof(city));
	//获取开头的每个城市所能够到达的范围
	for (int i = 1; i <= M; i++) {
		if (height[1][i] >= height[1][i + 1] &&
				height[1][i] >= height[1][i - 1]) {
			int begin = 1;
			for (; begin <= M; begin++) {
				if (link[i][begin]) {
					break;
				}
			}
			city[i].left = begin;
			
			int end = begin + 1;
			
			for (; end <= M; end++) {
				if (!link[i][end]) {
					break;
				}
			}
			end--;
			city[i].right = end;
		}
	}
	for (int i = 1; i <= M; i++) {
		//printf("#%d left:%d right:%d\n", i, city[i].left, city[i].right);
	}
	memset(dp, 0x127, sizeof(dp));
	dp[0] = 0;
	for (int i = 1; i <= M; i++) {
		for (int j = 1; j <= M; j++) {
			if (city[j].left <= i && city[j].right >= i) {
				dp[i] = (std::min)(dp[i], dp[city[j].left - 1] + 1);
			}
		}
	}
	cout << "1" << endl;
	cout << dp[M];
	
	//system("pause");
	return 0;
}

