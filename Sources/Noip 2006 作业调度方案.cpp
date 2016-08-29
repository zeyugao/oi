//My thought:
//一开始我也认为就是不断地“压入”作业，如果该台机器在有空位（符合条件）就挤入
//感觉也是挺水的
//但一开始的题目中“另一方面，在安排后面的操作时，不能改动前面已安排的操作的工作状态。”理解不对，导致否定了自己的想法，认为不能简单地用这种方法来做，exploded!
//比如说我有一个工件A和一个工件B，A要求机器1先工作2h，再在机器2工作1h，工件B需要在机器2上工作3h，
//如果没有那句话，我在机器2[2,3]区间插入第2道工序，再看工件B时，我可以把第2道工序往后移1割单位，在机器2的[0,3]插入工件B，最终只需要4h，
//但如果不允许改前面，所以不允许这样的方案，只能在[2,3]的区间后面再找时间，就是[3,6]插入工件B，总共所需时间为6h，这才是钦点的答案，没有扯到dp
//还是想复杂了

#include<stdio.h>

int n,m, order[500], machine[21][21], time[21][21];
//          顺序  i工件j工序使用机械       时间 
int now[21],    end_[21],    has_used_t[21][500], ans=0;
//工件现工序号  现结束时间  i机器j时间是否被占用 

int shu_ru()
{
	int i,j;
	scanf("%d%d",&m,&n);
	for(i=1;i<=m*n;i++)
		   scanf("%d",&order[i]);
	for(i=1;i<=n;i++)
	  	for(j=1;j<=m;j++)
		   	scanf("%d",&machine[i][j]);
	for(i=1;i<=n;i++)
	  	for(j=1;j<=m;j++)
			    scanf("%d",&time[i][j]);
}
int check(int x,int bg,int ed)
{
    int i;
   	for(i=bg;i<=ed;i++)
	    	if(has_used_t[x][i]) return 0;
	     return 1;
}
int main()
{
    int i,j,l;
	   shu_ru();
   	for(i=1;i<=m*n;i++)           //工序 
   	{
		    int x=order[i];               //提取工件 
		    int y=machine[x][++now[x]];   //提取加工机器 
		    int z=time[x][now[x]];        //提取所需时间 
		
		    for(j=end_[x];;j++)
			       if(check(y,j,j+z-1))      //可插入?
		       	{
			         	for(l=0;l<z;l++)       //记录时段已使用 
					           has_used_t[y][j+l]=1;
			         if(j+z>ans) ans=j+z;    //更改总时间 
				             end_[x]=j+z;       //更改x结束时间 
			        	break; 
			      }
	}
	printf("%d",ans);
	return 0;
}