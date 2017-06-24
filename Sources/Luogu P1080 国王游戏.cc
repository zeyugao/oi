//Copyright (C) 2017 Elsanna
//License:GPL
//Author:Elsanna

#include <string.h>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <iomanip>
using namespace std;
#define BASE 10000

class BigNum {
  public:
	int num_array[5001];
	int len;
	BigNum() {
		memset(num_array, 0, sizeof(num_array));
		len = 1;
	}
	BigNum(long num) {
		memset(num_array, 0, sizeof(num_array));
		len = 1;
		while (num) {
			num_array[len++] = num % BASE;
			num /= BASE;
		}
		if (num == 0) {
			len--;
		}
		else {
			num_array[len] = num;
		}
	}
	//BigNum operator*(BigNum b) {
	//    if (b.len == 0 && b.num_array[1] == 0)return 0;
	//    BigNum c;
	//    c.len = b.len + len;
	//    for (int i = 1; i <= len; i++) {
	//        for (int j = 1; j <= b.len; j++) {
	//            c.num_array[i + j - 1] += num_array[i] * b.num_array[j];
	//            c.num_array[i + j] += c.num_array[i + j - 1] / BASE;
	//            c.num_array[i + j - 1] %= BASE;
	//        }
	//    }
	//    //Clean up
	//    while (c.num_array[c.len] == 0 && c.len > 1) {
	//        c.len--;
	//    }
	//    return c;
	//}
	//BigNum operator+(BigNum b) {
	//    BigNum c;
	//    c.len = max(len, b.len);
	//    for (int i = 1; i <= c.len; i++) {
	//        c.num_array[i] += num_array[i] + b.num_array[i];
	//        c.num_array[i + 1] += c.num_array[i] / BASE;
	//        c.num_array[i + 1] %= BASE;
	//    }
	//    while (c.num_array[c.len + 1]) {
	//        c.len++;
	//    }
	//    return c;
	//}
	//inline int bsearch(BigNum b, BigNum m) {
	//    int L = 0, R = BASE - 1, x;
	//    //这个函数就不缩行了
	//    while (1) {
	//        x = (L + R) >> 1;
	
	//        //这里是b*x<=m，如果不满足，就说明x大了
	//        if (!(m < b*x)) {
	//            //这里是m<b*(x+1)，如果不满足，就说明x小了
	//            if (m < b*(x + 1)) {
	//                return x;
	//            }
	//            else {
	//                L = x;
	//            }
	//        }
	//        else {
	//            R = x;
	//        }
	//    }
	//}
	//BigNum operator-(BigNum b) {
	//    if (*this < b) {
	//        //交换
	//        auto t = *this;
	//        *this = b;
	//        b = t;
	//    }
	//    BigNum c;
	//    c.len = len;
	//    for (int i = 1; i <= len; i++) {
	//        c.num_array[i] = num_array[i] - b.num_array[i];
	//        if (c.num_array[i] < 0) {
	//            c.num_array[i] += BASE;
	//            c.num_array[i + 1]--;
	//        }
	//    }
	//    while (c.num_array[c.len] == 0 && c.len > 1) {
	//        c.len--;
	//    }
	//    return c;
	//}
	//BigNum operator/(BigNum b) {
	//    BigNum c = *this;
	//    BigNum m;
	//    for (int i = c.len; i >= 1; i--) {
	//        m = m*BASE + num_array[i];
	//        if (i == 4) {
	//            int i = 0;
	//        }
	//        //找到最大的x能使bx<=m
	//        //即上商
	//        c.num_array[i] = bsearch(b, m);
	//        m = m - b*c.num_array[i];
	//    }
	//    while (c.num_array[c.len] == 0 && c.len > 1) {
	//        c.len--;
	//    }
	//    return c;
	//}
	BigNum operator*(long b) {
		BigNum c;
		c.len = len;
		long left = 0;
		for (int i = 1; i <= len; i++) {
			c.num_array[i] = num_array[i] * b + left;
			left = c.num_array[i] / BASE;
			c.num_array[i] %= BASE;
		}
		while (left != 0) {
			c.len++;
			c.num_array[c.len] += left;
			left = c.num_array[c.len] / BASE;
			c.num_array[c.len] %= BASE;
		}
		return c;
	}
	BigNum operator/(long b) {
		BigNum c;
		c.len = len;
		long left = 0;
		for (int i = len; i >= 1; i--) {
			left = left * BASE + num_array[i];
			c.num_array[i] = left / b;
			left %= b;
		}
		while (c.num_array[c.len] == 0) {
			c.len--;
		}
		return c;
	}
	bool operator<(BigNum b) {
		if (b.len != len) {
			return len < b.len;
		}
		for (int i = len; i >= 1; i--) {
			if (num_array[i] != b.num_array[i]) {
				return num_array[i] < b.num_array[i];
			}
		}
		return false;
	}
	friend ostream &operator<<(ostream &out, BigNum b) {
		out << b.num_array[b.len];
		for (int i = b.len - 1; i >= 1; i--) {
			out.width(4);
			out.fill('0');
			out << b.num_array[i];
		}
		return out;
	}
	friend istream &operator >> (istream &in, BigNum &b) {
		int num_tmp;
		in >> num_tmp;
		b = num_tmp;
		return in;
	}
};
struct Minister {
	long left_hand, right_hand, hand_xx;
} minister[1010];

bool compare_func(Minister a, Minister b) {
	return a.hand_xx < b.hand_xx;
}
int main() {

	long n, right_king, left_king;
	cin >> n >> left_king >> right_king;
	
	for (int i = 1; i <= n; i++) {
		cin >> minister[i].left_hand >> minister[i].right_hand;
		minister[i].hand_xx = minister[i].left_hand * minister[i].right_hand;
	}
	sort(minister + 1, minister + n + 1, compare_func);
	
	BigNum max_price = 0, last_people_price = 0, now_people_price;
	
	BigNum front_left_muli_price;
	front_left_muli_price = left_king;
	
	for (int i = 1; i <= n; i++) {
		now_people_price = front_left_muli_price / minister[i].right_hand;
		if (max_price < now_people_price) {
			max_price = now_people_price;
		}
		
		front_left_muli_price = front_left_muli_price * minister[i].left_hand;
		//cout << "No." << i << " " << now_people_price << " " << max_price << " " << front_left_muli_price << endl;
		//cout << minister[i].left_hand << " " << minister[i].right_hand << " " << minister[i].hand_xx << endl;
	}
	cout << max_price << endl;
	return 0;
}