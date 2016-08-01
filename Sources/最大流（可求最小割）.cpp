//From http://www.acmerblog.com/ford-fulkerson-6135.html
/*
比较常见的是Ford-Fulkerson解法。该方法依赖于三种重要思想：残留网络，增广路径和割。详细的介绍可以参考：

http://blog.csdn.net/smartxxyx/article/details/9293665

该算法可以简单的描述如下：

1) 初始化flow为0

2）While (存在从s到t的增广路径，设其流量为path-flow)

flow += path-flow;

更新残留网络;

3) return flow
*/
import java.util.LinkedList;
import java.util.Queue;

public class MinFlow {
	public static int V = 6;

	/**
	 * 
	 * @param rGraph 残留网络
	 * @param s 源点
	 * @param t 终点
	 * @param path 路径
	 * @return 是否可以在rGraph中找到一条从 s 到 t 的路径
	 */
	public static boolean hasPath(int rGraph[][], int s, int t, int path[]) {
		boolean visited[] = new boolean[V];
		Queue<Integer> queue = new LinkedList<Integer>();
		queue.add(s);
		visited[s] = true;
		//标准的BFS算法
		while(queue.size() > 0){
			int top = queue.poll();
			for(int i=0; i<V; i++){
				if(!visited[i] && rGraph[top][i] > 0){
					queue.add(i);
					visited[i] = true;
					path[i] = top;
				}

			}
		}
		return visited[t] == true;
	}

	/**
	 * 
	 * @param graph 有向图的矩阵表示
	 * @param s 源点
	 * @param t 终点
	 * @return 最大流量
	 */
	private static int maxFlow(int[][] graph,int s, int t) {
		int rGraph[][] = new int[V][V];
		for(int i=0; i<V; i++)
			for(int j=0; j<V; j++)
				rGraph[i][j] = graph[i][j];

		int maxFlow = 0;

		int path[] = new int[V];
		while(hasPath(rGraph, s, t, path)){
			int min_flow = Integer.MAX_VALUE;

			//更新路径中的每条边,找到最小的流量
			for(int v=t; v != s; v=path[v]){
				int u = path[v];
				min_flow = Math.min(min_flow, rGraph[u][v]);
			}

			//更新路径中的每条边
			for(int v=t; v != s; v=path[v]){
				int u = path[v];
				rGraph[u][v] -= min_flow;
				rGraph[v][u] += min_flow;
			}
			maxFlow += min_flow;
		}

		return maxFlow;
	}

	public static void main(String[] args) {
		//创建例子中的有向图
		int graph[][] = { { 0, 16, 13, 0, 0, 0 }, 
				{ 0, 0, 10, 12, 0, 0 },
				{ 0, 4, 0, 0, 14, 0 },
				{ 0, 0, 9, 0, 0, 20 },
				{ 0, 0, 0, 7, 0, 4 },
				{ 0, 0, 0, 0, 0, 0 } };
		V = graph.length;
		int flow = maxFlow(graph, 0, 5);
		System.out.println("The maximum possible flow is :" + flow);
	}
}