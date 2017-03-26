#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>

using std::cin;
using std::endl;
using std::cout;

int days_current_month[] = {
	0,	//占位符
	31,28,31,30,31,30,31,31,30,31,30,31
};
int days_before_this_month[13] = { 0 };

struct Order {
	int begin;
	int end;
	int type;
};

Order order[20010];
int k;	//要求第k优值
int t;	//客户身份
int r;	//预定请求个数
void ParseDate(const char str[], int& ret_day) {
	int month = 0, pos = 0;
	while (str[pos] != '/') {
		month = month * 10 + str[pos++] - '0';
	}
	pos++;
	int day = 0;
	while (str[pos] != '\0') {
		day = day * 10 + str[pos++] - '0';
	}
	ret_day = days_before_this_month[month] + day;
}
void ReadData() {
	int y;
	cin >> k >> t >> y >> r;
	if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)) {
		days_current_month[2]++;
	}
	for (int i = 1; i <= 12; i++) {
		days_before_this_month[i] = days_before_this_month[i - 1] + days_current_month[i - 1];
	}
	for (int i = 1; i <= r; i++) {

		//scanf_s("%s*%s%s", begin_day_str, leave_day_str);

		for (int j = 1; j <= 3; j++) {
			std::string begin_day_str;
			std::string nothing_str;
			std::string leave_day_str;
			cin >> begin_day_str >> nothing_str >> leave_day_str >> order[i].type;
			int begin_day;
			int leave_day;
			ParseDate(begin_day_str.c_str(), begin_day);
			ParseDate(leave_day_str.c_str(), leave_day);
			order[i].begin = begin_day;
			order[i].end = leave_day;
		}
	}
}


int main() {

	ReadData();
	return 0;
}
