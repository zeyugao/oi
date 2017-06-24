#include <iostream>
#include <cstdlib>
#include <cstring>
#include <queue>

using namespace std;
int main() {

	priority_queue<int, vector<int>, greater<int>> water_tap;
	
	int people_need_water, n_people_num, m_water_tap_num;
	cin >> n_people_num >> m_water_tap_num;
	
	for (int i = 1; i <= m_water_tap_num; i++) {
		cin >> people_need_water;
		water_tap.push(people_need_water);
	}
	
	for (int i = 1; i <= n_people_num - m_water_tap_num; i++) {
		cin >> people_need_water;
		int current_min_mintue = water_tap.top();
		water_tap.pop();
		
		current_min_mintue += people_need_water;
		water_tap.push(current_min_mintue);
	}
	int ans = 0;
	while (!water_tap.empty()) {
		ans = water_tap.top();
		water_tap.pop();
	}
	cout << ans;
	return 0;
}