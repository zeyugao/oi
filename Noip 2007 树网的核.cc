#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <vector>

using std::cin;
using std::endl;
using std::cout;

int n_node_num;
int core_len_max;
int dis_node[301][301];
int diameter_len;
int single_diameter_node[301];

bool node_on_diameter[301];

std::vector<int> graph[301];
//读入数据
void Read() {
	cin >> n_node_num >> core_len_max;

	memset(dis_node, 127, sizeof(dis_node));

	for (int i = 1; i <= n_node_num; i++) {
		int node_first, node_second, nodes_dis;
		cin >> node_first >> node_second >> nodes_dis;

		//记录接邻节点
		graph[node_first].push_back(node_second);
		graph[node_second].push_back(node_first);

		//记录距离
		dis_node[node_first][node_second] = nodes_dis;
		dis_node[node_second][node_first] = nodes_dis;
	}
}
//Floyd两点间最短距离
void Floyd() {
	for (int i = 1; i <= n_node_num; i++) {
		for (int j = 1; j <= n_node_num; j++) {
			for (int k = 1; k <= n_node_num; k++) {
				if (dis_node[i][j] > dis_node[i][k] + dis_node[k][j]) {
					dis_node[i][j] = dis_node[i][k] + dis_node[k][j];
				}
			}
		}
	}
}
//获取最长的两点间距离，也就是直径长度
void GetDiameter() {
	for (int i = 1; i <= n_node_num; i++) {
		for (int j = 1; j <= n_node_num; j++) {
			diameter_len = (std::max)(dis_node[i][j], diameter_len);
		}
	}
}

int begin_node, end_node;
int visited_for_dfs_mark_node[301] = { 0 };
bool DfsMarkNode(int current) {
	if (current == end_node) {
		node_on_diameter[current] = true;
		return true;
	}
	for (std::vector<int>::iterator it = graph[current].begin();
		it != graph[current].end();
		it++) {
		if (visited_for_dfs_mark_node[*it]) {
			continue;
		}
		visited_for_dfs_mark_node[*it] = true;
		if (DfsMarkNode(*it)) {
			node_on_diameter[current] = true;//回溯，记录经过的节点
			return true;
		}
	}
}

//标记在直径上的点
int MarkNode() {
	int random_choose_node_as_begin;
	for (int i = 1; i <= n_node_num; i++) {
		for (int j = 1; j < n_node_num; j++) {
			if (dis_node[i][j] == diameter_len) {//找到一条直径的两个段点
				begin_node = i; end_node = j;
				memset(visited_for_dfs_mark_node, 0, sizeof(visited_for_dfs_mark_node));
				visited_for_dfs_mark_node[begin_node] = true;
				random_choose_node_as_begin = i;
				DfsMarkNode(begin_node);
			}
		}
	}
	return random_choose_node_as_begin;
}

//获取一条直径上的点
void GetQueue(int begin_node) {
	int current_node = begin_node;
	while()
}

int main() {

	Read();

	Floyd();

	GetDiameter();

	int random_choose_node_as_begin = MarkNode();

	GetQueue(random_choose_node_as_begin);

	return 0;
}