//My thought:
//一开始我也认为就是不断地“压入”作业，如果该台机器在有空位（符合条件）就挤入
//感觉也是挺水的
//但一开始的题目中“另一方面，在安排后面的操作时，不能改动前面已安排的操作的工作状态。”理解不对，导致否定了自己的想法，认为不能简单地用这种方法来做，exploded!
//比如说我有一个工件A和一个工件B，A要求机器1先工作2h，再在机器2工作1h，工件B需要在机器2上工作3h，
//如果没有那句话，我在机器2[2,3]区间插入第2道工序，再看工件B时，我可以把第2道工序往后移1割单位，在机器2的[0,3]插入工件B，最终只需要4h，
//但如果不允许改前面，所以不允许这样的方案，只能在[2,3]的区间后面再找时间，就是[3,6]插入工件B，总共所需时间为6h，这才是钦点的答案，没有扯到dp
//还是想复杂了

#include<stdio.h>
#define N 30
int CPU[N][N]={0};		//定义机器并初始化为未工作状态

typedef struct workprice
{
	int count;			//工件计数器，计算工件加工到了第几步
	int machine[N];		//工件x(1-n)第y(1-m)步使用的机器编号
	int time[N];		//工件x(1-n)第y(1-m)步使用的时间
	int endtime;		//工件上次结束时的时间
}Work;

//判断该段时间是机器否有空，参数为(机器编号， 开始时间， 结束时间)
int OK(int Mnum, int begin, int end)
{
	int i;
	for(i=begin; i<=end; i++)
		if(CPU[Mnum][i])
			return 1;
	return 0;
}

int main()
{
	Work G[N];									//定义工件
	int train[361];								//定义队列记录给定顺序

	int m, n, i, j, begin, machnum, step, time, ans=0;

	scanf("%d %d", &m, &n);
	for(i=1; i<=n; i++)							//初始化结构体变量的计数器和结束时间
	{	G[i].count=0;	G[i].endtime=1;	}

	for(i=1; i<=m*n; i++)						//输入给定安排顺序
		scanf("%d", &train[i]);

	for(i=1; i<=n; i++)
		for(j=1; j<=m; j++)						//输入第i个工件第j步使用的机器编号
			scanf("%d", &G[i].machine[j]);

	for(i=1; i<=n; i++)	
		for(j=1; j<=m; j++)						//输入第i个工件第j步需要花费的时间
			scanf("%d", &G[i].time[j]);

//核心代码
	for(i=1; i<=m*n; i++)
	{
		step = ++G[train[i]].count;				//找到工件加工到了第几步
		begin = G[train[i]].endtime;			//找到该工件上次的结束时间记录为本次开始时间
		machnum = G[train[i]].machine[step];	//找到加工该工件第step步需要的机器号
		time = G[train[i]].time[step];			//找到加工该工件第step步需要的时间

		//找出实际能够开始的时间（即机器有足够长的时间能够完成加工该步骤的任务）
		while(OK(machnum, begin, begin+time-1))		begin++;

		for(j=begin; j<begin+time; j++)			//将该段时间标记为已经使用
			CPU[machnum][j]=1;

		ans = ans>(begin+time-1)?ans:(begin+time-1);	//取机器运行时间的最大值作为结果

		G[train[i]].endtime=begin+time;			//刷新该工件的结束时间
	}
	printf("%d\n", ans);
	return 0;
}