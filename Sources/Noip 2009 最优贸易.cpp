/*典型的双向Spfa问题 
最优：在最便宜的地方买入，在最贵的地方卖出。 
因此第一遍正向Spfa找到价格最低的地点，即在该处买入；第二遍反向Spfa找到价格最高的地点，即为卖出点。 
ans=max{max_cost[i]-min_cost[i]};*/



//我能通过spfa从n->i，说明我一定能从i到i~n的最大值中，
//能1->i,说明也能从1走到i~n的最小值并且能够继续走到i 
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
int n,m;
int a[100001],Max[100001],Min[100001];
int q[1000001],h,t;
bool v[100001];
vector<int> edge[100001],edge1[100001];
int main()
{
    //freopen("trade.in","r",stdin);
    //freopen("trade.out","w",stdout);
    scanf("%d %d",&n,&m);
    for (int i =1;i <= n;i ++) scanf("%d",&a[i]);
    for (int i = 1;i <= m;i ++)
    {
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        edge[x].push_back(y);
        if (z > 1) edge[y].push_back(x);
        edge1[y].push_back(x);
        if (z > 1) edge1[x].push_back(y);
    }
    memset(Min,63,sizeof(Min));
    Min[1] = a[1];
    q[1] = 1;
    v[1] = true;
    h = 0,t = 1;
    while (h < t)
    {
        if (h != 0) v[q[h]] = false;
        h ++;
        for (int i = 0;i < edge[q[h]].size();i++)
            if (Min[edge[q[h]][i]] > min(a[edge[q[h]][i]],Min[q[h]]))
            {
                Min[edge[q[h]][i]] = min(a[edge[q[h]][i]],Min[q[h]]);
                if (!v[edge[q[h]][i]]) 
                {
                    q[++t] = edge[q[h]][i];
                    v[edge[q[h]][i]] = true;
                }
            }
    }
    memset(v,0,sizeof(v));
    Max[n] = a[n];
    q[1] = n;
    v[n] = true;
    h = 0,t = 1;
    while (h < t)
    {
        if (h != 0) v[q[h]] = false;
        h ++;
        for (int i = 0;i < edge1[q[h]].size();i++)
            if (Max[edge1[q[h]][i]] < max(a[edge1[q[h]][i]],Max[q[h]]))
            {
                Max[edge1[q[h]][i]] = max(a[edge1[q[h]][i]],Max[q[h]]);
                if (!v[edge1[q[h]][i]]) 
                {
                    q[++t] = edge1[q[h]][i];
                    v[edge1[q[h]][i]] = true;
                }
            }
    }
    int ans = 0;
    for (int i = 1;i <= n;i ++)
    {
        //printf("%d %d\n",Max[i],Min[i]);
        ans = max(ans,Max[i] - Min[i]);
    }
    cout << ans;
}
