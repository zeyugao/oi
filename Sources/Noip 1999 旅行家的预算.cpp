//Copyright (C) 2017 Elsanna
//License:GPL
//Author:Elsanna

#include <string.h>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <iomanip>
using namespace std;

//Summary:
//	在开始前，进行判断，能不能到达最近的加油站，如果不行，No solution
//	在当前节点开始往后搜索，如果后面的节点没有比当前结点的单价便宜的，就在当前结点加满油，到达能到达的最便宜的节点那
//		如果有比当前结点便宜的，那么就在当前结点加有加到刚刚好能到那个油站
//			要求到里离当前结点最近的，比当前结点便宜的
int main() {
	//Init
	
	//
	double distance_tmp, capacity, dis_per_liter, price[101];
	int n_station;
	cin >> distance_tmp >> capacity >> dis_per_liter >> price[0] >> n_station;
	double distance[101];
	distance[0] = 0;
	distance[n_station + 1] = distance_tmp;
	
	for (int i = 1; i <= n_station; i++) {
		cin >> distance[i] >> price[i];
	}
	double usage = 0.0;
	
	//left_oil_capacity放错位置进行初始化了
	double left_oil_capacity = 0.0;
	
	for (int current_pos = 0; current_pos <= n_station;) {
	
		//最近的站台都到不了
		if (capacity * dis_per_liter < distance[current_pos + 1] - distance[current_pos]) {
			cout << "No Solution" << endl;
			return 0;
		}
		double min_price_forward = 0xffff;
		
		int min_price_forward_station = current_pos + 1;
		bool found_less_price = false;
		for (int next_pos = current_pos + 1; next_pos <= n_station + 1; next_pos++) {
			//保证能到下一个节点，否则就跳出
			if (capacity * dis_per_liter < distance[next_pos] - distance[current_pos]) {
				break;
			}
			
			//更新最近更便宜的节点
			if (price[next_pos] < min_price_forward) {
				min_price_forward = price[next_pos];
				min_price_forward_station = next_pos;
				//如果有比当前结点便宜的或者相等的
				if (price[next_pos] <= price[current_pos]) {
					//加到刚刚好即可
					usage += ((distance[next_pos] - distance[current_pos]) / dis_per_liter - left_oil_capacity) * price[current_pos];
					left_oil_capacity = 0;
					
					//到更便宜的节点那
					
					//found_less_price便于判断是否找到了更少油价的节点
					found_less_price = true;
					current_pos = next_pos;
					break;
				}
			}
			if (next_pos == n_station + 1) {
				//未来节点没有一个比当前结点便宜的
				//并且终点可以直接到达
				//那么直接加到刚刚够到达的容量即可
				if (min_price_forward > price[current_pos]) {
					//这一部分要用等宽字体来看
					//↓使用费用                 两点距离↓                                       减去还留下的油↓            单价↓
					usage += ((distance[next_pos] - distance[current_pos]) / dis_per_liter - left_oil_capacity) * price[current_pos];
					//到达终点
					
					cout << setiosflags(ios::fixed) << setprecision(2) << usage << endl;
					//system("pause");
					return 0;
				}
			}
		}
		if (found_less_price) { continue; }
		
		
		//对于没有的比当前结点便宜的，就加满，到最便宜的下一个节点
		usage += (capacity - left_oil_capacity) * price[current_pos];
		left_oil_capacity = capacity - (distance[min_price_forward_station] - distance[current_pos]) / dis_per_liter;
		
		
		current_pos = min_price_forward_station;
	}
	cout << setiosflags(ios::fixed) << setprecision(2) << usage << endl;
	
	return 0;
}


#ifndef _DEBUG
#pragma GCC optimize(3)
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <memory>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <queue>
#include <cstring>
#include <fstream>
#include <cmath>
#include <Windows.h>
#include <set>
using namespace std;
#endif // _DEBUG
struct station {
	double dis, price;
};
bool cmp(station a, station b) {
	return a.dis < b.dis;
}
//Coded by myself
//从当前加油站往后找，如果最近的加油站距离大于d2*c 输出-1
//如果找到了比当前加油站油价更低的或相同的，则加刚好能到达该加油站的油
//否则，则加满油到相对油价最低的加油站
int main() {
	double d1, c, d2, p, sum = 0, left = 0;
	station all[106] = { 0 };
	memset(all, 0, sizeof(all));
	int n, j, local = 0;
	scanf_s("%lf%lf%lf%lf", &d1, &c, &d2, &p);
	scanf_s("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf_s("%lf%lf", &all[i].dis, &all[i].price);
	}
	all[0].dis = 0; all[n + 1].dis = d1;
	all[0].price = p; all[n + 1].price = 1000000.0;
	sort(all, all + n + 1, cmp);
	double max_dis = c * d2, min_price;
	for (int i = 0; i <= n;) {
		min_price = 10000000.0;
		if (all[i + 1].dis - all[i].dis > max_dis) { printf_s("-1"); return 0; }
		local = i + 1;
		for (j = i + 1; j <= n + 1; j++) {
			if (all[j].dis - all[i].dis > max_dis) { break; }
			if (min_price > all[j].price) {
				min_price = all[j].price;
				local = j;
			}
			if (j == n + 1) {
				if (min_price > all[i].price) {
					sum += (((all[j].dis - all[i].dis) / d2) - left) * all[i].price;
					left = 0;
					goto end;
				}
			}
		}
		if (min_price > all[i].price) {
			sum += (c - left) * all[i].price;
			left = c - (all[local].dis - all[i].dis) / d2;
		}
		else {
			sum += (((all[local].dis - all[i].dis) / d2) - left) * all[i].price;
			left = 0;
		}
		i = local;
	}
end:
	printf_s("%.2lf\n", sum);
	return 0;
}