#define MAXN 5200
int m,//行
n,//列
left[MAXN], right[MAXN], up[MAXN], down[MAXN],
col[MAXN],	//元素的列
sum[301],	//某一列的1的个数
ans[301],	//记录答案，根据depth记录
row[17];	//行头指针

void Remove(int c) {
	//删除顶端节点
	left[right[c]] = left[c];
	right[left[c]] = right[c];

	for (int i = down[c]; i != c; i = down[i]) {
		for (int j = right[i]; j != i; j = right[j]) {
			down[up[j]] = down[j];
			up[down[j]] = up[j];
			sum[col[j]]--;
		}
	}
}

void Resume(int c) {
	//顺序相反
	for (int i = up[c]; i != c; i = up[i]) {
		for (int j = left[i]; j != i; j = left[j]) {
			down[up[j]] = j;
			up[down[j]] = j;
			sum[col[j]]++;
		}
	}
	right[left[c]] = c;
	left[right[c]] = c;
}
bool Dancing(int depth) {
	if (right[0] == 0) {
		return true;//矩阵为空，被删完了
	}
	int min = 20, chosen_col;
	for (int i = right[0]; i != 0; i = right[i]) {
		if (sum[i] < min) {
			min = sum[i];
			chosen_col = i;
		}
	}

	Remove(chosen_col);

	for (int i = down[chosen_col]; i != chosen_col; i = down[i]) {
		ans[depth] = i;
		for (int j = right[i]; j != i; j = right[j]) {
			Remove(col[j]);
		}

		if (Dancing(depth + 1)) {
			return true;
		}

		for (int j = left[i]; j != i; j = left[j]) {
			Resume(col[j]);
		}
	}
	Resume(chosen_col);
}
void Init() {
	//初始化列头指针
	for (int i = 1; i <= n; i++) {
		left[i] = i - 1;
		right[i] = i + 1;
		down[i] = i;
		up[i] = i;
		col[i] = i;
	}
	left[0] = n;
	right[0] = 1;
	right[n] = 0;

	memset(row, -1, sizeof(row));
	memset(sum, 0, sizeof(sum));

	int current_set_node = n + 1, read_temp;

	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			std::cin >> read_temp;

			if (!read_temp) {
				continue;
			}

			if (row[i] == -1) {//为每一行的第一个非零元素
				row[i] = right[current_set_node] = left[current_set_node] = current_set_node;
			}
			else {
				//在还未更新left[row[i]]时，left[row[i]]一直是当前行最右一个元素（除新添加的元素外），因此，必须最后更新
				left[current_set_node] = left[row[i]];//取出在还未添加这个元素时行指针的左边元素，就是这行的最右元素
				right[current_set_node] = row[i];

				right[left[row[i]]] = current_set_node;//同样取出最右元素，设置它的右元素为当前元素
				left[row[i]] = current_set_node;//设置当列的最右元素为当前设置的元素
			}
			//在还未更新up[j]时，up[j]一直是当前列最下一个元素（除新添加的元素外），因此，必须最后更新
			up[current_set_node] = up[j];//j是第一行元素的
			down[current_set_node] = j;
			down[up[j]] = j;
			up[j] = current_set_node;

			col[current_set_node] = j;//设置当前节点属于哪一列
			sum[j]++;
			current_set_node++;//设置下一个节点
		}
	}
}