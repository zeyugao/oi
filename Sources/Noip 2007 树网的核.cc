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
int single_diameter_side_len[301];
int num_node_on_chosen_diameter;

bool node_on_diameter[301];

std::vector<int> graph[301];
//读入数据
void Read() {
	//std::ios_base::sync_with_stdio(false);
	
	cin >> n_node_num >> core_len_max;
	
	memset(dis_node, 0xf, sizeof(dis_node));
	
	for (register int i = 2; i <= n_node_num; i++) {
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
		dis_node[i][i] = 0;
	}
	//Floyd的顺序要注意，中继点在最外层
	for (register int k = 1; k <= n_node_num; k++) {
		for (register int i = 1; i <= n_node_num; i++) {
			for (register int j = 1; j <= n_node_num; j++) {
				//printf("calculating dis between %d,%d,dis:%d,%d:%d,dis:%d,%d:%d\n",i,j,i,k,dis_node[i][k],k,j,dis_node[k][j]);
				if (dis_node[i][j] > dis_node[i][k] + dis_node[k][j]) {
				
					dis_node[i][j] = dis_node[i][k] + dis_node[k][j];
					//printf("update dis %d <-> %d : %d\n",i,j,dis_node[i][j]);
				}
			}
		}
	}
}
//获取最长的两点间距离，也就是直径长度
void GetDiameter() {
	diameter_len = -1;
	for (register int i = 1; i <= n_node_num; i++) {
		for (register int j = 1; j <= n_node_num; j++) {
			if (dis_node[i][j] > diameter_len) {
				diameter_len = dis_node[i][j];
				//printf("update diameter: %d ,between %d,%d\n",diameter_len,i,j);
			}
		}
	}
	//printf("dismater: %d\n",diameter_len);
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
	for (register int i = 1; i <= n_node_num; i++) {
		for (register int j = 1; j <= n_node_num; j++) {
			if (dis_node[i][j] == diameter_len) {//找到一条直径的两个段点
				begin_node = i;
				end_node = j;
				memset(visited_for_dfs_mark_node, 0, sizeof(visited_for_dfs_mark_node));
				visited_for_dfs_mark_node[begin_node] = true;
				random_choose_node_as_begin = i;
				DfsMarkNode(begin_node);
			}
		}
	}
	
	return random_choose_node_as_begin;
}

bool visited_for_get_queue[301] = {0};

//获取一条直径上的所有的点
void GetQueue(int current_node) {
	for (std::vector<int>::iterator it = graph[current_node].begin();
			it != graph[current_node].end();
			it++) {
		if (!visited_for_get_queue[*it] &&	// 没有经过
				node_on_diameter[*it]		   //在直径上
		   ) {
			single_diameter_side_len[num_node_on_chosen_diameter++] = dis_node[current_node][*it]; //记录当前在直径上的点到下一个点的距离，并按顺序排列
			visited_for_get_queue[current_node] = true;
			GetQueue(*it);
			break;//找到一个直径即可
		}
	}
}

int GetAns() {
	int current_node = 1;
	int last_node = 1;
	int current_side_len = 0;
	int side_len_behind = 0;
	int ans = 0xfffff;
	while (single_diameter_side_len[current_node]) {
		current_side_len +=  single_diameter_side_len[current_node++];
		//printf("current calculating side long: %d, side long summary: %d\n",single_diameter_side_len[current_node-1],current_side_len);
		while (current_side_len > core_len_max) { //超过了限制
		
			current_side_len -= single_diameter_side_len[last_node];
			side_len_behind += single_diameter_side_len[last_node++];
			
			//printf("too long, delete, current long: %d, side behind: %d\n",current_side_len,side_len_behind);
		}
		//printf("\ncurrent side no: %d, side behind: %d, side ahead: %d\n",current_node-1,side_len_behind,diameter_len - current_side_len - side_len_behind);
		ans = (std::min)(ans, (std::max)(side_len_behind, diameter_len - current_side_len - side_len_behind));
	}
	return ans;
}
int main() {

	Read();
	
	Floyd();
	
	GetDiameter();
	
	int random_choose_node_as_begin = MarkNode();
	
	num_node_on_chosen_diameter = 1;
	GetQueue(random_choose_node_as_begin);
	
	std::cout << GetAns();
	return 0;
}

