#ifndef _DEBUG

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
using namespace std;
#endif // _DEBUG

int main() {
    int m, s, t;
    scanf("%d%d%d", &m, &s, &t);
    int a=0, b=0,i;
    for (i = 1; i <= t; i++) {
        a += 17;
        if (m >= 10) { b += 60; m -= 10; }
        else { m += 4; }
        if (a < b)a = b;
        if (a > s) { printf("Yes\n%d\n", i); return 0; }

    }
    if(a>s) { printf("Yes\n%d\n", i); return 0; }else { printf("No\n%d\n", a); return 0; }

    return 0;
}