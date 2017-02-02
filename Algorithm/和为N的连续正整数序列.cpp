/*假定有k个连续的正整数和为N，其中连续序列的第一个数为x，则有x+(x+1)+(x+2)+...+(x+k-1) = N。
从而可以求得x = (N - k*(k-1)/2)  /  k。当x的值小于等于0时，则说明已经没有正整数序列的和为N了，
此时循环退出。初始化k=2，表示2个连续的正整数和为N，则可以求出x的值，并判断从x开始是否存在2个
连续正整数和为N，若不存在则k++，继续循环。*/
bool find_sequence(int N) 
{
	bool has = false;
	int k = 2, x, m ;  //k为连续序列的数目，x为起始的值，m用于判断是否有满足条件的值。
	while (true) { 
		x = (N - k*(k-1)/2) / k;  //求出k个连续正整数和为N的起始值x
		m = (N - k*(k-1)/2) % k; //m用于判断是否有满足条件的连续正整数值
		if (x <= 0) break;    //退出条件，如果x<=0，则循环退出。
		if (!m) {             //m为0，表示找到了连续子序列和为N。
			has = true;
			output(x, k);
		}
		k++;
	}
	return has;
}

void output(int x, int k) 
{
	for (int i=0; i<k; i++) {
		cout << x++ << " ";
	}
	cout << endl;
}

