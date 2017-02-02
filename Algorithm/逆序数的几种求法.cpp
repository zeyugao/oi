/*求一个数列的逆序数
逆序对：数列a[1],a[2],a[3]…中的任意两个数a[i],a[j] (i<j)，如果a[i]>a[j],那么我们就说这两个数构成了一个逆序对
逆序数：一个数列中逆序对的总数
如数列 3 5 4 8 2 6 9
(5,4)是一个逆序对，同样还有(3,2),(5,2),(4,2)等等
那么如何求得一个数列的逆序数呢？
方法1：一个一个的数
最简单也是最容易想到的方法就是，对于数列中的每一个数a[i]，遍历数列中的数a[j](其中j<i),若a[i]<a[j],则逆序数加1，这样就能统计出该数列的逆序数总和
该方法的时间复杂度为O(n^2)，具体过程就不细说了
方法2：归并的思想
有一种排序的方法是归并排序，归并排序的主要思想是将整个序列分成两部分，分别递归将这两部分排好序之后，再和并为一个有序的序列，核心代码如下
*/
MergeSort(int first,int last)
{
	if(first == last)
		return;
	int med = (first + last) / 2;
	MergeSort(first, med);
	MergeSort(med + 1, last);
	Merge(first, last);
}
/*
在合并的过程中是将两个相邻并且有序的序列合并成一个有序序列，如以下两个有序序列
Seq1：3  4  5
Seq2：2  6  8  9
合并成一个有序序:
Seq：2  3  4  5  6  8  9
对于序列seq1中的某个数a[i],序列seq2中的某个数a[j]，如果a[i]<a[j],没有逆序数，如果a[i]>a[j]，那么逆序数为seq1中a[i]后边元素的个数(包括a[i])，即len1-i+1,
这样累加每次递归过程的逆序数，在完成整个递归过程之后，最后的累加和就是逆序的总数
实现代码如下：*/
const int LENGTH = 100;
int temp[LENGTH];  //额外的辅助数组

int count = 0;

void Merge(int * array, int first, int med, int last)
{
	int i = first, j = med + 1;
	int cur = 0;
	while (i <= med&&j <= last)
	{
		if (array[i] < array[j])
		{
			temp[cur++] = array[i++];
		}
		else
		{
			temp[cur++] = array[j++];
			count += med - i + 1 ;  //核心代码，逆序数增加
		}
	}
	while (i <= med)
	{
		temp[cur++] = array[i++];
	}
	while (j <= last)
	{
		temp[cur++] = array[j++];
	}
	for (int m = 0; m < cur; m++)
	{
		array[first++] = temp[m++];
	}
}
void MergeSort(int *array, int first, int last)
{
	if (first == last)
	{
		return;
	}
	int med = first + (last - first) / 2;
	MergeSort(array, first, med);
	MergeSort(array, med + 1, last);
	Merge(array, first, med, last);
}/*
 归并排序的复杂度为O(nlogn)，当然此方法的复杂度也为O(nlogn)
 方法3：用树状数组
 还是以刚才的序列
 3  5  4  8  2  6  9
 大体思路为：新建一个数组，将数组中每个元素置0
 0  0  0  0  0  0  0
 取数列中最大的元素，将该元素所在位置置1
 0  0  0  0  0  0  1
 统计该位置前放置元素的个数，为0
 接着放第二大元素8，将第四个位置置1
 0  0  0  1  0  0  1
 统计该位置前放置元素的个数，为0
 继续放第三大元素6，将第六个位置置1
 0  0  0  1  0  1  1
 统计该位置前放置元素的个数，为1
 …
 …
 这样直到把最小元素放完，累加每次放元素是该元素前边已放元素的个数，这样就算出总的逆序数来了
 在统计和计算每次放某个元素时，该元素前边已放元素的个数时如果一个一个地数，那么一趟复杂度为O(n),总共操作n趟，复杂度为O(n^2)，和第一种方法的复杂度一样了，那我们为什么还用这么复杂的方法
 当然，在每次统计的过程中用树状数组可以把每一趟计数个数的复杂度降为O(logn)，这样整个复杂度就变为O(nlogn)

 树状数组是一种很好的数据结构，这有一篇专门描述树状数组的文章
 将序列中的每个数按照从大到小的顺序插入到树状数组中，给当前插入节点及其父节点的个数加1，然后统计该节点下边及右边放置元素的个数
 /////////从大到小很容易理解,就是说我一个元素放了进去,要找的是在该元素前面且大于它的元素,我从大到小插入,可以保证在一个新的元素放入后,所有在它前面的一定是大于它的,直接统计个数即可
 具体代码如下：*/
 //用树状数组求逆序数
const int Length = 8;
struct Node
{
	int data;
	int pos;
};
int LowBit(int num)
{
	//根据wiki,return num&(-num)亦可
	return num&(num ^ (num - 1));
}
//自定义排序方法
int cmp(const void * num1, const void * num2)
{
	return ((Node*)num2)->data - ((Node *)num1)->data;
}
//统计pos节点下方及右方节点元素的个数
int sum(int *TreeArray, int pos)
{
	int result = 0;
	while (pos)
	{
		result += TreeArray[pos];
		pos -= LowBit(pos);
	}
	return result;
}
//使pos位置的节点及其父节点的元素个数加1
void INC(int *TreeArray, int pos)
{
	while (pos < Length)
	{
		TreeArray[pos]++;
		pos += LowBit(pos);
	}
}
void insertNum(int *TreeArray, Node * seq, int &reverseNum)
{
	for (int i = 1; i < Length; i++)
	{
		reverseNum += sum(TreeArray, seq[i].pos);  //累加逆序数
		INC(TreeArray, seq[i].pos);    //将该节点及父节点的数加1
	}
}
int main(int argc, char* argv[])
{
	int array[] = { 3,5,4,8,2,6,9 };
	Node seq[Length];
	int TreeArray[Length];
	memset(TreeArray, 0, sizeof(TreeArray));
	for (int i = 1; i < Length + 1; i++)
	{
		seq[i].data = array[i - 1];
		seq[i].pos = i;
	}
	//从大到小排序
	qsort(seq + 1, Length - 1, sizeof(Node), cmp);
	int reverseNum = 0;
	//边插入边计数
	insertNum(TreeArray, seq, reverseNum);
	cout << reverseNum << endl;
	return 0;
}