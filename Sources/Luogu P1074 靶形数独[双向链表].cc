#include <iostream>
#include <string>
#include <cstdio>
#include <algorithm>
#include <cstring>

#define MAXROW 729    //9*81
#define MAXCOL 324    //81*4
#define MAXNUM MAXROW*MAXCOL
int left[MAXNUM], right[MAXNUM], up[MAXNUM], down[MAXNUM];
int row[MAXNUM];    //一个Node属于第几行            //数组大小开错了，写入到其他数组内存了，检查有没有开小数组，没发现#define的写错了。。
int col[MAXNUM];    //一个Node属于第几列
int row_head[MAXROW + 1];    //行头指针
int col_sum[MAXCOL + 1];    //列求和
int ans[81];    //搜索结果
int final_ans[81];
int sudoku_map[9][9];
bool rect_map[MAXROW][MAXCOL] = { 0 };
const int score_map[81] = {
	6, 6, 6, 6, 6, 6, 6, 6, 6,
	6, 7, 7, 7, 7, 7, 7, 7, 6,
	6, 7, 8, 8, 8, 8, 8, 7, 6,
	6, 7, 8, 9, 9, 9, 8, 7, 6,
	6, 7, 8, 9, 10, 9, 8, 7, 6,
	6, 7, 8, 9, 9, 9, 8, 7, 6,
	6, 7, 8, 8, 8, 8, 8, 7, 6,
	6, 7, 7, 7, 7, 7, 7, 7, 6,
	6, 6, 6, 6, 6, 6, 6, 6, 6
};
int ans_output = -1;
//int ans_count = 0;
void set_rect(int r, int c, int k) {//(r,c) <- k
	int row = 9 * (9 * r + c) + k;
	
	rect_map[row][9 * r + c] = true;    //1~81个格子有没有数字
	rect_map[row][81 + 9 * r + k] = true;    //1~9行有没有1~9
	rect_map[row][162 + 9 * c + k] = true;    //1~9列有没有1~9
	rect_map[row][243 + 9 * (3 * (r / 3) + c / 3) + k] = true;    //9个格子有没有1~9
}
//用不同的可能的棋盘结果进行填充
void ConstructRect() {
	memset(rect_map, 0, sizeof(rect_map));
	for (int i = 0; i < 81; i++) {
		int r = i / 9;
		int c = i % 9;
		if (sudoku_map[r][c] == 0) {//未配置的数独数字
			for (int j = 0; j < 9; j++) {
				set_rect(r, c, j);
			}
		}
		else {
			set_rect(r, c, sudoku_map[r][c] - 1);//从0开始
		}
	}
}

void Remove(int c) {
	//移除头指针
	left[right[c]] = left[c];
	right[left[c]] = right[c];
	
	for (int i = down[c]; i != c; i = down[i]) {//从上往下删
		for (int j = right[i]; j != i; j = right[j]) {//从左往右删
			down[up[j]] = down[j];
			up[down[j]] = up[j];
			col_sum[col[j]]--;
		}
	}
}
void Resume(int c) {
	for (int i = up[c]; i != c; i = up[i]) {
		for (int j = left[i]; j != i; j = left[j]) {
			down[up[j]] = j;
			up[down[j]] = j;
			col_sum[col[j]]++;
		}
	}
	right[left[c]] = c;
	left[right[c]] = c;
}

int GetScore() {
	int ret_ans = 0;
	
	for (int i = 0; i < 81; i++) {
		ret_ans += final_ans[i] * score_map[i];
	}
	return ret_ans;
}

//bool Dancing(int depth) {
void Dancing(int depth) {
	if (right[0] == 0) {
		//for (int i = 0; i < depth; i++) {
		
		//    //row从1开始计数，而rect_map的纵坐标从0开始计数，而这要相互转化row得要-1(s)
		//    final_ans[(row[ans[i]] - 1) / 9] = (row[ans[i]] - 1) % 9 + 1;
		//}
		
		//return true;
		
		//std::cout << std::endl;
		for (int i = 0; i < depth; i++) {
			final_ans[(row[ans[i]] - 1) / 9] = (row[ans[i]] - 1) % 9 + 1;
		}
		//for (int i = 0; i < 81; i++) {
		//    if (i % 9 == 0) {
		//        std::cout << std::endl;
		//    }
		//    std::cout << final_ans[i] << " ";
		//}
		ans_output = std::max(ans_output, GetScore());
		//std::cout << std::endl << GetScore() << std::endl;
		return;
	}
	int min_sum = 1000, chosen_col;
	for (int i = right[0]; i != 0; i = right[i]) {
		if (col_sum[i] < min_sum) {
			chosen_col = i;
			min_sum = col_sum[i];
		}
	}
	
	Remove(chosen_col);
	
	for (int i = down[chosen_col]; i != chosen_col; i = down[i]) {
	
		ans[depth] = i;
		
		for (int j = right[i]; j != i; j = right[j]) {
			Remove(col[j]);
		}
		
		/*if (Dancing(depth + 1)) {
		    return true;
		}*/
		Dancing(depth + 1);
		
		for (int j = left[i]; j != i; j = left[j]) {
			Resume(col[j]);
		}
	}
	Resume(chosen_col);
	//return false;
}

//建立双向链表
void Init() {
	//行头指针
	for (int i = 1; i <= MAXCOL; i++) {
		up[i] = i;
		down[i] = i;
		left[i] = i - 1;
		right[i] = i + 1;
		col[i] = i;
	}
	left[0] = MAXCOL;
	right[0] = 1;
	right[MAXCOL] = 0;
	
	memset(row_head, -1, sizeof(row_head));
	memset(col_sum, 0, sizeof(col_sum));
	
	int current_set_node = MAXCOL + 1;
	for (int i = 1; i <= MAXROW; i++) {
		for (int j = 1; j <= MAXCOL; j++) {
			if (!rect_map[i - 1][j - 1]) {//这里判断的得要是构建了的大数组
				continue;
			}
			if (row_head[i] == -1) {
				row_head[i] = right[current_set_node] = left[current_set_node] = current_set_node;
			}
			else {
				//left[row_head[i]]最右
				
				left[current_set_node] = left[row_head[i]];
				right[current_set_node] = row_head[i];
				
				right[left[row_head[i]]] = current_set_node;
				left[row_head[i]] = current_set_node;
			}
			//up[j]最下
			
			up[current_set_node] = up[j];
			down[current_set_node] = j;
			
			down[up[j]] = current_set_node;
			up[j] = current_set_node;
			
			col[current_set_node] = j;
			row[current_set_node] = i;
			
			col_sum[j]++;
			current_set_node++;
		}
	}
}

int main() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			std::cin >> sudoku_map[i][j];
		}
	}
	
	ConstructRect();
	
	Init();
	
	Dancing(0);
	
	/*for (int i = 0; i < 81; i++) {
	    std::cout << final_ans[i] << " ";
	    if (i % 9 == 8) {
	        std::cout << std::endl;
	    }
	}*/
	std::cout << ans_output << std::endl;
	return 0;
}