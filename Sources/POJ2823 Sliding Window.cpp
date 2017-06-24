/*First
source:http://baike.baidu.com/view/3771451.htm#2_3
这个是典型的固定k区间的单调队列。套用的本质思想是，如求最小值： 考虑这样的一个问题，在某个区间当中如果存在某两个元素A,B，满足A的下标小于B的下标，A的值大于B的值，那么A这个数就可以删掉，不再考虑。求最大值反之。
具体的操作是：从加入第k个数开始，每插入做一次队列单调性更新：
删队尾[单调性]，入队，删队首[下标范围k以内]，输出队首[即最值]。*/
//当A>B时，但如果B比A更晚进来，必定会在A前面出去，这就说明，只要B在，A就不可能会是最小值，就可以放心地删除A


//Second
//感觉这个好理解一点
//source:http://blog.csdn.net/acvay/article/details/46772771
/*队尾单调入队(入队元素大于队尾元素时直接入队  否则队尾出队直到队尾元素小于入队元素或者队列为空)  队首队尾都可以出队
求最小值时 先判断队首元素是否在滑窗之内  不在队首就出队  然后队首元素就是滑窗中的最小值了   求最大值用单减队列就行了*/
#include <cstdio>
using namespace std;
const int N = 1e6 + 5;
int a[N], q[N], t[N];
int front, rear, n, k;

#define NOTMONO (!op && a[i] < q[rear - 1]) || (op && a[i] > q[rear - 1])
//op = 0 时单增队列  op = 1 时单减队列
void getMonoQueue(int op) {
	front = rear = 0;
	for (int i = 0; i < n; ++i) {
		//维护单调队列，神奇的二合一方法
		while (rear > front && (NOTMONO)) { --rear; }
		
		//记录滑窗滑到i点的时间
		t[rear] = i;
		q[rear++] = a[i];
		
		
		//保证队首元素在滑窗之内
		//由于单调队列的性质，如果是单增队列，头部就是最大值
		//出队也很容易，一直出队，又由于只是循环到i，保证队列中的元素的位置一定会小于window的右边框
		while (t[front] <= i - k) { ++front; }
		
		//i>=k-1，从0开始计数
		if (i > k - 2) {
			printf("%d%c", q[front], i == n - 1 ? '\n' : ' ');
		}
	}
}

int main() {
	while (~scanf("%d%d", &n, &k)) {
		for (int i = 0; i < n; ++i) {
			scanf("%d", &a[i]);
		}
		getMonoQueue(0); //单增队列维护最小值
		getMonoQueue(1); //单减队列维护最大值
	}
	
	return 0;
}
//Third
/*
Source:http://blog.csdn.net/kenden23/article/details/37598147

1 如何入列，保存数据 -- 最小单调队列的时候， 所有数都入列一次，在新的数据准备入列的时候，增加判断，如果当前数值小于队尾数值，那么队尾数值就出列。空队列的时候直接入列。
2 保存的数列是什么样的？
举例吧： 1 3 -1 -3 5 3 6 7
构建最小单调队列
第一个数值1的时候，空队列，那么入列，得到： 1
第二个数值3， 因为大于1；那么1不用出列，直接入列，得到： 1 3
第三个数值-1，因为小于3，故此3出列，-1入列，继续判断-1小于1，故此1也出列，剩下队列得到： -1
以此类推……
根据实际情况，本题需要的是K大小端中的最小和最大值，那么就可以记录上各个数值的下标，加以判断。即下标不在需要的判断范围之内的就出来，不过这次是从队列头出列。因为去掉这些下标不合要求的数值之后，队列的头数值依然是最小值，故此是当前答案。*/

#include<cstdio>
const int MAX_N = 1000001;

int N, K;
int arr[MAX_N];
int qu[MAX_N];
int index[MAX_N];
int ans[MAX_N];

void getMins() {
	int tail = 0, head = 1;	//初始化tail<head表示为空列
	for (int i = 1; i < K; i++) {	//初始化单调队列
		while (tail >= head && qu[tail] >= arr[i]) { tail--; }
		qu[++tail] = arr[i];		//记录可能的答案值
		index[tail] = i;	//记录额外需要判断的信息
	}
	for (int i = K; i <= N; i++) {
		while (tail >= head && qu[tail] >= arr[i]) { tail--; } //不符合条件出列
		qu[++tail] = arr[i];
		index[tail] = i;
		while (index[head] <= i - K) { head++; }
		ans[i - K] = qu[head];	//ans从下标0开始记录
	}
}

void getMaxs() {
	int tail = 0, head = 1;
	for (int i = 1; i < K; i++) {	//初始化单调队列
		while (tail >= head && qu[tail] <= arr[i]) { tail--; }
		qu[++tail] = arr[i];
		index[tail] = i;
	}
	for (int i = K; i <= N; i++) {
		while (tail >= head && qu[tail] <= arr[i]) { tail--; } //不符合条件出列
		qu[++tail] = arr[i];
		index[tail] = i;
		while (index[head] <= i - K) { head++; }
		ans[i - K] = qu[head];	//ans从下标0开始记录
	}
}

int main() {
	while (~scanf("%d %d", &N, &K)) {
		for (int i = 1; i <= N; i++) { scanf("%d", &arr[i]); }
		getMins();
		for (int i = 0; i <= N - K; i++) { printf("%d ", ans[i]); }
		putchar('\n');
		getMaxs();
		for (int i = 0; i <= N - K; i++) { printf("%d ", ans[i]); }
		putchar('\n');
	}
	return 0;
}