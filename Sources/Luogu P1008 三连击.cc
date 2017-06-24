#include <string.h>
#include <algorithm>
#include <iostream>
#include <cstdio>
using namespace std;
//Copyright (C) 2017 Elsanna
//License:GPL
//Author:Elsanna
//Summary:
//	Super water


void ParseNumber(int num, int num_array[]) {
	while (num) {
		num_array[num % 10]++;
		num /= 10;
	}
}

bool CheckNumber(int a, int b, int c) {
	int num_array[10] = { 0 };
	ParseNumber(a, num_array);
	ParseNumber(b, num_array);
	ParseNumber(c, num_array);
	for (int i = 1; i < 10; i++) {
		if (num_array[i] != 1) {
			return false;
		}
	}
	return true;
}
int main() {

	for (int i = 100; i <= 999; i++) {
		if (i * 3 >= 1000) { break; }
		
		if (CheckNumber(i, 2 * i, 3 * i)) {
			printf("%d %d %d\r\n", i, 2 * i, 3 * i);
		}
	}
	return 0;
}