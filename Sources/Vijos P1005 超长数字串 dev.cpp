//不想打了。。
//

//#ifndef _DEBUG
#pragma GCC optimize(2)

#include <codecvt>
#include <sstream>
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
#include <iterator>
#include <set>
#include <process.h>
#include <ctime>
#include <utility>
#include <cctype>
#include <bitset>
using namespace std;
#endif // _DEBUG
#include <iostream>
#include <cstdio>
#include <string>
//不想打高精度的后果
//两百位……
#define ull unsigned long long
string Target;

int GetLen(ull num) {
	int len = 1;
	while (num /= 10) {
		len++;
	}
	return len;
}
ull GetNum(int b, int e) {
	double t = 0;
	for (int i = e; i >= b; i--) {
		t = t * 10 + Target[i] - '0';
	}
	return t;
}

int main() {
	cin >> Target;
	int ans_pos = 0;
	ull ans_num = 0;
	for (int len = 1; len <= Target.size(); len++) {
		for (int start_pos = 0; start_pos < len; start_pos++) {
			int temp_pos = start_pos;
			ull temp_num_1, temp_num_2;
			bool exit = false;
			//比较start_pos前不足len长度的字符串
			if (start_pos > 0) {
				ull mod_ = 1;
				for (int i = 0; i <= start_pos; i++) {
					mod_ *= 10;
				}
				//好像是可行的
				temp_num_1 = GetNum(0, start_pos - 1);
				temp_num_2 = GetNum(start_pos, start_pos + len - 1);
				if (GetLen(temp_num_2 - 1) != GetLen(temp_num_2)) {
					for (int i = 0; i < start_pos; i++)
						if (Target[i] != '9') {
							exit = true; goto aaaa;
						}
					//ToDo
				}
			}
			
			ull last = 0;
			ull t_2;
			last = GetNum(temp_pos, temp_pos + len - 1);
			temp_pos += len;
			//主体部分比较
			while (temp_pos + len - 1 <= Target.size() && !exit) {
				//9，99，999……的情况
				if (GetLen(last) != GetLen(last + 1)) { len++; }
				t_2 = GetNum(temp_pos, temp_pos + len - 1);
				if (t_2 != last + 1) {
					exit = true;
				}
				else {
					last = t_2, temp_pos += len;
				}
			}
aaaa:
			if (exit) { continue; }
			
			//比较到temp_pos后，不足长度的字符串
			temp_num_2 = GetNum(temp_pos, Target.size() - 1);
			temp_num_1 = GetNum(temp_pos - len, temp_pos - 1) + 1;
			if (GetLen(temp_num_1 + 1) != GetLen(temp_num_1)) { len++; }
			int times = len - (Target.size() - temp_pos);/*Target.size() -1 - temp_pos +1*/
			while (times--) {
				temp_num_1 /= 10;
			}
			if (temp_num_1 + 1 == temp_num_2) {
				ans_num = GetNum(start_pos, start_pos + len - 1);
				ans_pos = start_pos;
				goto end;
			}
		}
	}
end:
	//获取ans_num这个数字在哪个位置
	return 0;
}