#include <iostream>
#include <cstring>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#define KMOD 666623333
#define KMAXNUM 1000000 + 5

int prime[1000000];
bool is_not_prime[KMAXNUM] = { 0 };
int pt = 1;
void GetPrime() {

	is_not_prime[1] = 1;
	for (int i = 2; i <= KMAXNUM; i++) {
		if (!is_not_prime[i]) {	//是非质数
			prime[pt++] = i;	//就加入prime数组
			if (i <= 1000) {
				for (int j = i * i; j <= KMAXNUM; j += i) {
					is_not_prime[j] = true;
				}
			}
		}
	}
}

//Summary:
//	不通过朴素的欧拉函数算法进行计算，这样绝对LTE
//	先预处理到sqrt(10e12)=10e6的质数
//	以每个数直接用prime[i]进行找因子，减少大量的运算
int main() {
	GetPrime();
	/*for (int i = 1; i < pt; i++) {
		std::cout << prime[i] << " ";
	}*/
	unsigned long long l, r, num[KMAXNUM], phi[KMAXNUM];
	std::cin >> l >> r;
	for (int i = 0; i <= r - l; i++) {
		phi[i] = i + l; //i+l的欧拉函数值
		num[i] = i + l;	//记录第i个数的数值
	}
	
	for (int i = 1; i < pt; i++) {
		long long num_div = l / prime[i] * prime[i];	//再找绝对能被这个质数整除的数，保证这个质数一定是这个大数的质因子
		if (num_div < l) {
			num_div += prime[i];
		}
		for (; num_div <= r; num_div += prime[i]) {		//num_div+=prime[i]是找出所有含有prime[i]的因数的数值
			phi[num_div - l] = phi[num_div - l] / prime[i] * (prime[i] - 1);	//欧拉函数中，找到了一个质因数的(1-1/(prime[i])
			num[num_div - l] /= prime[i];
			while (num[num_div - l] % prime[i] == 0) {	//将num[num_div-l]这个数的prime[i]的因子全部除去
				num[num_div - l] /= prime[i];
			}
		}
	}
	//至此，所有的[l,r]区间中的数都被分解了因数
	//为什么？
	//所有的数都可以被分解多个质数的乘积，如果这是一个大质数，质数表并没有覆盖，那么它会在下面的再次判断中被解决掉
	
	int ans = 0;
	
	//Question:要是某个数是两个大质数相乘怎么办？又没办法被质数表中的质数分解
	//范围决定了，这里可以覆盖到的10e6是否为质数，数据范围小于10e12，两个相乘，必定会有数小于等于10e6，可被质数表覆盖
	for (int i = 0; i <= r - l; i++) {
		if (num[i] > 1) {
			phi[i] = phi[i] / num[i] * (num[i] - 1);	//应对质数表中未覆盖到的数值
		}
		ans = (ans + (i + l) - phi[i]) % KMOD;
	}
	std::cout << ans << std::endl;
	return 0;
}